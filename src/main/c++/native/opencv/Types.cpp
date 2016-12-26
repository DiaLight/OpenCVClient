//
// Created by dialight on 26.12.16.
//
#include <opencv/Types.hpp>


void test(Point2i &p, Point2i &min, Point2i &max) {
    if(p.x < min.x) min.x = p.x;
    if(p.y < min.y) min.y = p.y;
    if(p.x > max.x) max.x = p.x;
    if(p.y > max.y) max.y = p.y;
}

AABB4i lines_triangle_t::getAABB() {
    Point2i min(l1.p1);
    Point2i max(l1.p1);
    test(l1.p2, min, max);
    test(l2.p1, min, max);
    test(l2.p2, min, max);
    test(l3.p1, min, max);
    test(l3.p2, min, max);
    return AABB4i(min, max);
}

bool aabb_t::containsPoint(Point p) {
    return p.x >= min.x &&
           p.y >= min.y &&
           p.x <= max.x &&
           p.y <= max.y;
}

bool aabb_t::interact(AABB4i &b) {
    return b.max.x >= min.x &&
           b.max.y >= min.y &&
           b.min.x <= max.x &&
           b.min.y <= max.y;
}

bool aabb_t::contains(AABB4i &b) {
    return b.min.x >= min.x &&
           b.min.y >= min.y &&
           b.max.x <= max.x &&
           b.max.y <= max.y;
}

int aabb_t::area() {
    return (max.x - min.x) * (max.y - min.y);
}
