//
// Created by dialight on 17.12.16.
//

#include "opencv/Utils.hpp"


bool Utils::linesCompare(Line4i const &l1, Line4i const &l2, int threshold) {
    if (pointsCompare(l1.p1, l2.p1, threshold) && pointsCompare(l1.p2, l2.p2, threshold)) return true;
    return pointsCompare(l1.p1, l2.p2, threshold) && pointsCompare(l1.p2, l2.p1, threshold);
}

bool Utils::pointsCompare(Point2i const &p1, Point2i const &p2, int threshold) {
    return abs(p1.x - p2.x) <= threshold &&
           abs(p1.y - p2.y) <= threshold;
}

void Utils::filterPoints(const vector<Point2i> &src, vector<Point2i> &dst, int threshold) {
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

void Utils::filterLines(const vector<Line4i> &src, vector<Line4i> &dst, int threshold) {
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

Line4i Utils::testTriangle(const Line4i &l1, const Line4i &l2, int threshold) {
    if(pointsCompare(l1.p1, l2.p1, threshold)) return Line4i(l1.p2, l2.p2);
    if(pointsCompare(l1.p1, l2.p2, threshold)) return Line4i(l1.p2, l2.p1);
    if(pointsCompare(l1.p2, l2.p1, threshold)) return Line4i(l1.p1, l2.p2);
    if(pointsCompare(l1.p2, l2.p2, threshold)) return Line4i(l1.p1, l2.p1);
    return Line4i(0, 0, 0, 0);
}

void ::Utils::filterContoursBySize(vector<vector<Point>> const &in, vector<vector<Point>> &out, int def_min_size, int def_max_size) {
    int min_size = props.getInt("filterContoursBySize.min_size", def_min_size);
    int max_size = props.getInt("filterContoursBySize.max_size", def_max_size);
    int max_int = std::numeric_limits<int>::max();
    for(auto const& contour : in) {
        int minX = max_int;
        int minY = max_int;
        int maxX = 0;
        int maxY = 0;

        for(auto first = contour.begin(); first != contour.end(); ++first) {
            int x = (*first).x;
            int y = (*first).y;
            if(minX > x) minX = x;
            if(minY > y) minY = y;
            if(maxX < x) maxX = x;
            if(maxY < y) maxY = y;
        }

        auto rect = Rect(minX, minY, maxX - minX, maxY - minY);
        if(rect.width < min_size) continue;
        if(rect.width > max_size) continue;
        if(rect.height < min_size) continue;
        if(rect.height > max_size) continue;
        out.push_back(contour);
    }
}

void ::Utils::contoursToLines(vector<vector<Point>> const &in, vector<vector<Line4i>> &out) {
    for(auto const& contour : in) {
//            double area = contourArea(approx, true);

        vector<Line4i> lines;
        auto second = contour.end() - 1;
        for(auto first = contour.begin(); first != contour.end(); ++first) {
            lines.push_back(Line4i(*first, *second));
            second = first;
        }
        out.push_back(lines);
    }
}
