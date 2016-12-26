//
// Created by dialight on 17.12.16.
//

#ifndef OPENCVCLIENT_IPTRIANGLEDETECT_HPP
#define OPENCVCLIENT_IPTRIANGLEDETECT_HPP

#include <opencv/Types.hpp>

class IPTriangleDetect {

    Mat gray;
public:

    Mat loop(Mat &mat);

    void findBorders(const vector<Point2i> &corners, const vector<Line4i> &lines, vector<Line4i> &borders);
    void findTriangles(const vector<Line4i> &borders, vector<Triangle12i> &triangles);

};


#endif //OPENCVCLIENT_IPTRIANGLEDETECT_HPP
