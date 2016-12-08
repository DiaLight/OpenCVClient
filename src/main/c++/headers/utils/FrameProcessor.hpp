//
// Created by dialight on 26.11.16.
//

#ifndef OPENCVCLIENT_FRAMEPROCESSOR_HPP
#define OPENCVCLIENT_FRAMEPROCESSOR_HPP

#include <string>
#include <opencv/ObjectDetect.hpp>
#include <opencv/Tool.hpp>
#include <Loop.hpp>

using namespace cv;

class FrameProcessor {
    enum FRAME_PROCESSOR {
        NONE,
        CLASSIFIER,
        MANUAL,
    };

    Tool tool;
    FRAME_PROCESSOR proc;

    ObjectDetect *detect;
    Loop *cvMain;
public:
    FrameProcessor();

    bool setClassifierBased(const string &xmlPath);

    void setManualHandler();

    virtual ~FrameProcessor();

    Mat handle(Mat mat);
};


#endif //OPENCVCLIENT_FRAMEPROCESSOR_HPP
