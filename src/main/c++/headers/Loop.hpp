//
// Created by dialight on 06.11.16.
//

#ifndef OPENCVCLIENT_OPENCVMAIN_HPP
#define OPENCVCLIENT_OPENCVMAIN_HPP


#include <platov_aleksey/TriangleDetect.hpp>
#include "opencv/Tool.hpp"

class Loop {
    Tool *tool;
    Mat gray;
    TriangleDetect pa_triangle;
public:
    Loop(Tool *tool);

    Mat loop(Mat frame);
};


#endif //OPENCVCLIENT_OPENCVMAIN_HPP
