//
// Created by dialight on 17.12.16.
//

#ifndef OPENCVCLIENT_TYPES_HPP
#define OPENCVCLIENT_TYPES_HPP

#include <opencv2/opencv.hpp>
#include <sstream>

using namespace cv;
using namespace std;

struct line_t {
    Point2i p1;
    Point2i p2;
    line_t(const Point2i &p1, const Point2i &p2) : p1(p1), p2(p2) {}
    line_t(const int &p1x, const int &p1y, const int &p2x, const int &p2y) : p1(p1x, p1y), p2(p2x, p2y) {}
    line_t(const Vec4i &v) : line_t(v[0], v[1], v[2], v[3]) {}
    line_t() : line_t(0, 0, 0, 0) {}

    bool isEmpty() {
        return p1.x + p1.y + p2.x + p2.y == 0;
    }

    string toString() {
        stringstream ss;
        ss << "{[" << p1.x << ", " << p1.y << "], [" << p2.x << ", " << p2.y << "]}";
        return ss.str();
    }
};
typedef struct line_t Line4i;

struct lines_triangle_t {
    Line4i l1;
    Line4i l2;
    Line4i l3;
    lines_triangle_t(const Line4i &l1, const Line4i &l2, const Line4i &l3) : l1(l1), l2(l2), l3(l3) {}
};
typedef struct lines_triangle_t Triangle12i;

struct points_triangle_t {
    Point2i p1;
    Point2i p2;
    Point2i p3;
    points_triangle_t(const Point2i &p1, const Point2i &p2, const Point2i &p3) : p1(p1), p2(p2), p3(p3) {}
    Triangle12i to12i() {
        return Triangle12i(Line4i(p1, p2), Line4i(p1, p3), Line4i(p2, p3));
    }
};
typedef struct points_triangle_t Triangle6i;

#endif //OPENCVCLIENT_TYPES_HPP
