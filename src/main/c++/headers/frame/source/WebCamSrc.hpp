//
// Created by dialight on 13.01.17.
//

#ifndef OPENCVCLIENT_WEBCAMSRC_HPP
#define OPENCVCLIENT_WEBCAMSRC_HPP


#include "FrameSource.hpp"

class WebCamSrc : public FrameSource {

    int deviceIndex;
    cv::VideoCapture *cap = nullptr;
public:
    WebCamSrc(int deviceIndex);
    virtual ~WebCamSrc();

    bool init() override;

    void capture(cv::Mat &mat) override;

    void setResolution(int width, int height) override;

    void setFps(int fps) override;
};


#endif //OPENCVCLIENT_WEBCAMSRC_HPP
