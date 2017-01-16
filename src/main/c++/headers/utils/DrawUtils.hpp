//
// Created by dialight on 06.12.16.
//

#ifndef OPENCVCLIENT_DRAWUTILS_HPP
#define OPENCVCLIENT_DRAWUTILS_HPP

#include "opencv/Types.hpp"

namespace DrawUtils {

    void showPoints(Mat &frame, vector<Point2i> const &points);

    void showLines(Mat &frame, vector<Line4i> const &lines);

    void showPointContours(Mat &frame, vector<vector<Point2i>> const &contours);
    void showLineContours(Mat &frame, vector<vector<Line4i>> const &contours);

    void showTriangle(Mat &frame, Triangle12i const &triangle);
    void showTriangle(Mat &frame, Triangle12i const &triangle, Scalar &color);
    void showTriangles(Mat &frame, vector<Triangle12i> const &triangles);
};


#endif //OPENCVCLIENT_DRAWUTILS_HPP
