//
// Created by dialight on 06.11.16.
//

#ifndef OPENCVCLIENT_OPENCVMAIN_HPP
#define OPENCVCLIENT_OPENCVMAIN_HPP


#include <platov_aleksey/PATriangleDetect.hpp>
#include <ilin_pavel/IPTriangleDetect.hpp>
#include "opencv/Tool.hpp"

class Loop {
    Tool *tool;
    Mat gray;
    PATriangleDetect pa_triangle;
    IPTriangleDetect ip_triangle;
public:
    Loop(Tool *tool);

    Mat loop(Mat frame);
};


#endif //OPENCVCLIENT_OPENCVMAIN_HPP
