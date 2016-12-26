//
// Created by dialight on 17.12.16.
//

#include <ilin_pavel/IPTriangleDetect.hpp>
#include <utils/MacroEnumString.hpp>
#include <opencv/Utils.hpp>
#include <opencv/OpenCVWrap.hpp>
#include <opencv/DrawUtils.hpp>

#define IPTriMacro(m) \
    m(SMOOTH, "Сглаживание") \
    m(GRAY, "Серые тона") \
    m(HARRIS, "Метод Харриса") \
    m(FILTER_CORNERS, "Фильтр точек") \
    m(ADAPTIVE_THRESHOLD, "Адаптивное пороговое преобразование") \
    m(CANNY, "Метод Кенни") \
    m(FIND_LINES, "Поиск линий") \
    m(FILTER_LINES, "Фильтр линий") \
    m(FIND_BORDERS, "Поиск границ") \
    m(FILTER_BORDERS, "Фильтр границ") \
    m(FIND_TRIANGLES, "Поиск треугольников") \
    m(FINAL, "Итог")
ENUM_STRING(IPTriMacro, IPTriStages)

//3.1415926535897932384626433832795 / 2
#define HALF_PI 1.5707963267948966192313216916398

Mat IPTriangleDetect::loop(Mat &frame) {

    int stage = props.getSelect("IPTriangle.stage", &IPTriStages::all, IPTriStages::FIND_BORDERS);

    CVWrap::gaussianBlur(frame, 7, 1.5);
    if(stage == IPTriStages::SMOOTH) return frame;

    cvtColor(frame, gray, COLOR_BGR2GRAY);
    if(stage == IPTriStages::GRAY) return gray;

    vector<Point2i> corners;
    CVWrap::harris(gray, corners);
    if(stage == IPTriStages::HARRIS) {
        DrawUtils::showPoints(frame, corners);
        stringstream ss;
        ss << "corners: " << corners.size();
        cv::putText(frame, ss.str(), Point2i(10, 22), FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
        return frame;
    }

    vector<Point2i> fcorners;
    Utils::filterPoints(corners, fcorners);
    if(stage == IPTriStages::FILTER_CORNERS) {
        DrawUtils::showPoints(frame, fcorners);
        stringstream ss;
        ss << "filtered corners: " << fcorners.size();
        cv::putText(frame, ss.str(), Point2i(10, 22), FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
        int i = 2;
        for(auto &p : fcorners) {
            stringstream ss2;
            ss2 << "[" << p.x << ", " << p.y << "]";
            cv::putText(frame, ss2.str(), Point2i(10, 22 * i++), FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
        }
        return frame;
    }

    CVWrap::adaptiveThreshold(gray);
    bitwise_not(gray, gray);
    if(stage == IPTriStages::ADAPTIVE_THRESHOLD) return gray;

    CVWrap::canny(gray);
    if(stage == IPTriStages::CANNY) return gray;

    vector<Line4i> lines;
    CVWrap::houghLines(gray, lines);
    if(stage == IPTriStages::FIND_LINES) {
        DrawUtils::showLines(frame, lines);
        stringstream ss;
        ss << "lines: " << lines.size();
        cv::putText(frame, ss.str(), Point2i(10, 22), FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
        return frame;
    }

    vector<Line4i> flines;
    Utils::filterLines(lines, flines);
    if(stage == IPTriStages::FILTER_LINES) {
        DrawUtils::showLines(frame, flines);
        stringstream ss;
        ss << "filtered lines: " << flines.size();
        cv::putText(frame, ss.str(), Point2i(10, 22), FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
        int i = 2;
        for(auto &l : flines) {
            cv::putText(frame, l.toString().c_str(), Point2i(10, 22 * i++), FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
        }
        return frame;
    }

    vector<Line4i> borders;
    findBorders(fcorners, flines, borders);
    if(stage == IPTriStages::FIND_BORDERS) {
        DrawUtils::showLines(frame, borders);
        stringstream ss;
        ss << "borders: " << borders.size();
        cv::putText(frame, ss.str(), Point2i(10, 22), FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
        int i = 2;
        for(auto &l : borders) {
            cv::putText(frame, l.toString().c_str(), Point2i(10, 22 * i++), FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
        }
        return frame;
    }

    vector<Line4i> fborders;
    Utils::filterLines(borders, fborders);
    if(stage == IPTriStages::FILTER_BORDERS) {
        DrawUtils::showLines(frame, fborders);
        stringstream ss;
        ss << "filtered borders: " << fborders.size();
        cv::putText(frame, ss.str(), Point2i(10, 22), FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
        int i = 2;
        for(auto &l : fborders) {
            cv::putText(frame, l.toString().c_str(), Point2i(10, 22 * i++), FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
        }
        return frame;
    }

    vector<Triangle12i> triangles;
    findTriangles(fborders, triangles);
    if(stage == IPTriStages::FIND_TRIANGLES) {
        DrawUtils::showTriangles(gray, triangles);
        return gray;
    }
    DrawUtils::showTriangles(frame, triangles);
    return frame;
}

namespace iptd1 {
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
}

void IPTriangleDetect::findBorders(const vector<Point2i> &corners, const vector<Line4i> &lines, vector<Line4i> &borders) {
    double cosrho = cos(CV_PI / 180 * 1); // отклонение 1 градус

    int corners_amount = (int) corners.size();
    // Детектирование треугольников
    for (int i = 0; i < corners_amount; i++) {
        for (int j = i + 1; j < corners_amount; j++) {
            Line4i l1(corners[i], corners[j]);
            for(auto const& l2 : lines) {
                float abscos = abs(iptd1::cosangle(l1, l2));
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
            Line4i pl3 = Utils::testTriangle(l1, l2);
            if(!pl3.isEmpty()) {
                for (int k = j + 1; k < borders_amount; k++) {
                    Line4i l3 = borders[k];
                    if(Utils::linesCompare(l3, pl3)) {
                        Triangle12i tr(l1, l2, l3);
                        triangles.push_back(tr);
                    }
                }
            }
        }
    }
}
