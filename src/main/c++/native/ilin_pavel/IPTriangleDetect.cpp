//
// Created by dialight on 17.12.16.
//

#include <opencv/Utils.hpp>
#include "ilin_pavel/IPTriangleDetect.hpp"

//3.1415926535897932384626433832795 / 2
#define HALF_PI 1.5707963267948966192313216916398

float angle1(Line4i l1, Line4i l2) {
    float dy1 = l1.p1.y - l1.p2.y;
    float dx1 = l1.p1.x - l1.p2.x;
    float angle1 = atan2(dy1, dx1);

    float dy2 = l2.p1.y - l2.p2.y;
    float dx2 = l2.p1.x - l2.p2.x;
    float angle2 = atan2(dy2, dx2);

    float angle = abs(angle1 - angle2);
    if(angle > CV_PI) {
//        cout << "PI " << angle << endl;
        angle -= CV_PI;
    }
    if(angle > HALF_PI) {
//        cout << "HALF PI " << angle << endl;
        angle = (float) (CV_PI - angle);
    }
    return angle;
}

float sqr(float x) {return x * x;}

float cosangle(Line4i l1, Line4i l2) {
    Point2i v1(l1.p2.x - l1.p1.x, l1.p2.y - l1.p1.y);
    Point2i v2(l2.p2.x - l2.p1.x, l2.p2.y - l2.p1.y);
    float scalar = (v1.x * v2.x) + (v1.y * v2.y);
    float mullen = sqrt((sqr(v1.x) + sqr(v1.y)) * ((sqr(v2.x) + sqr(v2.y))));
    return scalar / mullen;
}

void IPTriangleDetect::findBorders(const vector<Point2i> &corners, const vector<Line4i> &lines, vector<Line4i> &borders) {
    double cosrho = cos(CV_PI / 180 * 1); // отклонение 1 градус

    int corners_amount = (int) corners.size();
    // Детектирование треугольников
    for (int i = 0; i < corners_amount; i++) {
        for (int j = i + 1; j < corners_amount; j++) {
            Line4i l1(corners[i], corners[j]);
            for(auto const& l2 : lines) {
                float abscos = abs(cosangle(l1, l2));
                if(abscos > cosrho) {
                    borders.push_back(l1);
                }
            }
        }
    }
}

void IPTriangleDetect::findTriangles(const vector<Line4i> &borders, vector<Triangle12i> &triangles) {
    int borders_amount = (int) borders.size();
    // Детектирование треугольников
    for (int i = 0; i < borders_amount; i++) {
        for (int j = i + 1; j < borders_amount; j++) {
            Line4i l1 = borders[i];
            Line4i l2 = borders[j];
            Line4i pl3 = testTriangle(l1, l2);
            if(!pl3.isEmpty()) {
                for (int k = j + 1; k < borders_amount; k++) {
                    Line4i l3 = borders[k];
                    if(linesCompare(l3, pl3)) {
                        Triangle12i tr(l1, l2, l3);
                        triangles.push_back(tr);
                    }
                }
            }
        }
    }
}

void IPTriangleDetect::showTriangles(Mat &frame, const vector<Triangle12i> &triangles) {
    RNG rng(12345);
    for(auto const& tr : triangles) {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
        cv::line(frame, tr.l1.p1, tr.l1.p2, color, 3, LineTypes::LINE_AA);
        cv::line(frame, tr.l2.p1, tr.l2.p2, color, 3, LineTypes::LINE_AA);
        cv::line(frame, tr.l3.p1, tr.l3.p2, color, 3, LineTypes::LINE_AA);
    }
}
