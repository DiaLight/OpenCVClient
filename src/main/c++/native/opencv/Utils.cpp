//
// Created by dialight on 17.12.16.
//

#include "opencv/Utils.hpp"


bool linesCompare(Line4i const &l1, Line4i const &l2, int threshold) {
    if (pointsCompare(l1.p1, l2.p1, threshold) && pointsCompare(l1.p2, l2.p2, threshold)) return true;
    return pointsCompare(l1.p1, l2.p2, threshold) && pointsCompare(l1.p2, l2.p1, threshold);
}

bool pointsCompare(Point2i const &p1, Point2i const &p2, int threshold) {
    return abs(p1.x - p2.x) <= threshold &&
           abs(p1.y - p2.y) <= threshold;
}

void filterPoints(const vector<Point2i> &src, vector<Point2i> &dst, int threshold) {
    // отсеиваем "похожие" отрезки
    for(auto const& l1 : src) {
        bool found = false;
        for(auto const& l2 : dst) {
            if (pointsCompare(l1, l2, threshold)) {
                found = true;
                break;
            }
        }
        if (!found) {
            dst.push_back(l1);
        }
    }
}

void filterLines(const vector<Line4i> &src, vector<Line4i> &dst, int threshold) {
    // отсеиваем "похожие" отрезки
    for(auto const& l1 : src) {
        bool found = false;
        for(auto const& l2 : dst) {
            if (linesCompare(l1, l2, threshold)) {
                found = true;
                break;
            }
        }
        if (!found) {
            dst.push_back(l1);
        }
    }
}

/**
 * Метод для определения смежности 2-х линий. Используется для нахождения треугольников.
 * @param l1 первая сторона потенциального треугольника
 * @param l2 вторая сторона потенциального тругольника
 * @param threshold погрешность в сравнении точек
 * @return Если првые 2 стороны смежны, то 3-ю недостающую сторону треугольника. Иначе, пустую линию.
 */
Line4i testTriangle(Line4i &l1, Line4i &l2, int threshold) {
    if(pointsCompare(l1.p1, l2.p1, threshold)) return Line4i(l1.p2, l2.p2);
    if(pointsCompare(l1.p1, l2.p2, threshold)) return Line4i(l1.p2, l2.p1);
    if(pointsCompare(l1.p2, l2.p1, threshold)) return Line4i(l1.p1, l2.p2);
    if(pointsCompare(l1.p2, l2.p2, threshold)) return Line4i(l1.p1, l2.p1);
    return Line4i(0, 0, 0, 0);
}
