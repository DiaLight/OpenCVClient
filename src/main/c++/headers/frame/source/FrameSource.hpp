//
// Created by dialight on 13.01.17.
//

#ifndef OPENCVCLIENT_FRAMESOURCE_HPP
#define OPENCVCLIENT_FRAMESOURCE_HPP

#include <opencv2/opencv.hpp>

class FrameSource {

public:
    virtual ~FrameSource() {}
    virtual void capture(cv::Mat &mat) = 0;
    virtual bool init() = 0;
    virtual void setResolution(int width, int height) = 0;
    virtual void setFps(int fps)  = 0;

};


#endif //OPENCVCLIENT_FRAMESOURCE_HPP
