//
// Created by dialight on 17.12.16.
//

#ifndef OPENCVCLIENT_UTILS_HPP
#define OPENCVCLIENT_UTILS_HPP

#include "Types.hpp"

#define DEFAULT_THRESHOlD 16

bool pointsCompare(Point2i const& p1, Point2i const& p2, int threshold = DEFAULT_THRESHOlD);
bool linesCompare(Line4i const& l1, Line4i const& l2, int threshold = DEFAULT_THRESHOlD);

void filterPoints(const vector<Point2i> &src, vector<Point2i> &dst, int threshold = DEFAULT_THRESHOlD);
void filterLines(const vector<Line4i> &src, vector<Line4i> &dst, int threshold = DEFAULT_THRESHOlD);

Line4i testTriangle(Line4i &l1, Line4i &l2, int threshold = DEFAULT_THRESHOlD);


#endif //OPENCVCLIENT_UTILS_HPP
