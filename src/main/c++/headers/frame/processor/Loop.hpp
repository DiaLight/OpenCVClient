//
// Created by dialight on 06.11.16.
//

#ifndef OPENCVCLIENT_OPENCVMAIN_HPP
#define OPENCVCLIENT_OPENCVMAIN_HPP


#include <platov_aleksey/PATriangleDetect.hpp>
#include <ilin_pavel/IPTriangleDetect.hpp>
#include <ilin_pavel/IPTriangleDetect2.hpp>
#include <IntelEdison.hpp>
#include "FrameProcessor.hpp"

class Loop : public FrameProcessor {
    Mat gray;
    PATriangleDetect pa_triangle;
    IPTriangleDetect ip_triangle;
    IPTriangleDetect2 ip_triangle2;

    Triangle12i last;
    RNG rng;
    Scalar color;
    IntelEdison edison;
public:

    void handle(cv::Mat &frame) override;

};


#endif //OPENCVCLIENT_OPENCVMAIN_HPP
