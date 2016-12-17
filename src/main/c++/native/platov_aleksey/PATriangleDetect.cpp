//
// Created by dialight on 29.11.16.
//

#include <opencv/Utils.hpp>
#include "platov_aleksey/PATriangleDetect.hpp"

bool PATriangleDetect::triangleCompare(Point2i p, Point2i q, int area) {
    return abs(q.x - p.x) <= area &&
           abs(q.y - p.y) <= area;
}

Point2i PATriangleDetect::posTriangle(Line4i *t) {
    Point2i pos;
    for (int i = 0; i < 3; i++) {
        pos += t[i].p1;
        pos += t[i].p2;
    }
    pos /= 6;
    return pos;
}

void PATriangleDetect::showTriangles(Mat &frame, vector<PATriangle> const &triangles) {
    RNG rng(12345);
    for(auto const& tr : triangles) {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
        for (int j = 0; j < 3; j++) {
            Line4i const& l = tr.lines[j];
            cv::line(frame, l.p1, l.p2, color, 3, CV_AA);
        }
        cv::circle(frame, tr.cur_pos, 2, color, 1, LINE_AA);
    }
}

void PATriangleDetect::findTriangles(const vector<Line4i> &lines, int width, vector<PATriangle> &triangles) {
    int line_length = (int) lines.size();
    // Детектирование треугольников
    for (int i = 0; i < line_length; i++) {
        for (int j = i + 1; j < line_length; j++) {
            // выбор первых двух отрезков
            Line4i l1 = lines[i];
            Line4i l2 = lines[j];
            Line4i pl3 = testTriangle(l1, l2, area);

            if(!pl3.isEmpty()) {
                for (int k = j + 1; k < line_length; k++) {
                    Line4i l3 = lines[k];
                    if(linesCompare(l3, pl3)) {
                        bool bad = false;
                        PATriangle newTr(l1, l2, l3);
                        newTr.fst_pos = posTriangle(newTr.lines);
                        // сравнение с имеющимися треугольниками
                        for(auto &tr : triangles) {
                            if (triangleCompare(tr.cur_pos, newTr.fst_pos, 150)) {
                                tr.cur_pos = newTr.fst_pos;
                                bad = true;
                                break;
                            }
                        }

                        if (checkCloseBorderline(newTr.fst_pos, width)) {
                            bad = true;
                        }
                        // запоминание треугольника
                        if (!bad) {
                            newTr.cur_pos = newTr.fst_pos;
                            newTr.checked = false;

                            triangles.push_back(newTr);
                        }
                    }
                }
            }
        }
    }
}
