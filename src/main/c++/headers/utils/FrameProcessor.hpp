//
// Created by dialight on 26.11.16.
//

#ifndef OPENCVCLIENT_FRAMEPROCESSOR_HPP
#define OPENCVCLIENT_FRAMEPROCESSOR_HPP

#include <string>
#include <opencv/ObjectDetect.hpp>
#include <Loop.hpp>

using namespace cv;

class FrameProcessor {
    enum FRAME_PROCESSOR {
        NONE,
        CLASSIFIER,
        MANUAL,
    };

    FRAME_PROCESSOR proc;

    ObjectDetect *detect;
    Loop *loop;
public:
    FrameProcessor();

    bool setClassifierBased(const string &xmlPath);

    void setManualHandler();

    virtual ~FrameProcessor();

    void handle(Mat &mat);
};


#endif //OPENCVCLIENT_FRAMEPROCESSOR_HPP
