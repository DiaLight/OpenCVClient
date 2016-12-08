//
// Created by dialight on 29.11.16.
//

#include "platov_aleksey/TriangleDetect.hpp"

bool TriangleDetect::triangleCompare(Point2i p, Point2i q, int area) {
    return abs(q.x - p.x) <= area &&
           abs(q.y - p.y) <= area;
}

bool TriangleDetect::linesCompare(Line4i const &l1, Line4i const &l2) {
    if (pointsCompare(l1.p1, l2.p1) && pointsCompare(l1.p2, l2.p2)) return true;
    return pointsCompare(l1.p1, l2.p2) && pointsCompare(l1.p2, l2.p1);
}

bool TriangleDetect::pointsCompare(Point2i const &p1, Point2i const &p2) {
    return abs(p1.x - p2.x) <= area &&
           abs(p1.y - p2.y) <= area;
}

Point2i TriangleDetect::posTriangle(Line4i *t) {
    Point2i pos;
    for (int i = 0; i < 3; i++) {
        pos += t[i].p1;
        pos += t[i].p2;
    }
    pos /= 6;
    return pos;
}

Line4i TriangleDetect::testTriangle(Line4i l1, Line4i l2) {
    if(pointsCompare(l1.p1, l2.p1)) return Line4i(l1.p2, l2.p2);
    if(pointsCompare(l1.p1, l2.p2)) return Line4i(l1.p2, l2.p1);
    if(pointsCompare(l1.p2, l2.p1)) return Line4i(l1.p1, l2.p2);
    if(pointsCompare(l1.p2, l2.p2)) return Line4i(l1.p1, l2.p1);
    return Line4i(-1, -1, -1, -1);
}

void TriangleDetect::showTriangles(Mat &frame, vector<Triangle> const &triangles) {
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

void TriangleDetect::filterLines(const vector<Line4i> &lines, vector<Line4i> &filtered) {
    // отсеиваем "похожие" отрезки
    for(auto const& pline : lines) {
        bool found = false;
        for(auto const& l : filtered) {
            if (linesCompare(l, pline)) {
                found = true;
                break;
            }
        }
        if (!found) {
            filtered.push_back(pline);
        }
    }
}

void TriangleDetect::findTriangles(const vector<Line4i> &lines, int width, vector<Triangle> &triangles) {
    int line_length = (int) lines.size();
    // Детектирование треугольников
    for (int i = 0; i < line_length; i++) {
        for (int j = i + 1; j < line_length; j++) {
            // счетчики
            int k = 0;
            // выбор первых двух отрезков
            Line4i l1 = lines[i];
            Line4i l2 = lines[j];
            Line4i pl3 = testTriangle(l1, l2);

            if(pl3.p1.x > 0) {
                for (k = j + 1; k < line_length; k++) {
                    Line4i l3 = lines[k];
                    if(linesCompare(l3, pl3)) {
                        bool bad = false;
                        Triangle newTr(l1, l2, l3);
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
