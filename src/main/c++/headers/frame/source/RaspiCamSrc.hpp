//
// Created by dialight on 13.01.17.
//

#ifndef OPENCVCLIENT_RASPICAMSRC_HPP
#define OPENCVCLIENT_RASPICAMSRC_HPP


#include "FrameSource.hpp"
#ifdef USE_RASPICAM
#include <raspicam/raspicam_cv.h>
#endif

class RaspiCamSrc : public FrameSource {

#ifdef USE_RASPICAM
    raspicam::RaspiCam_Cv cam;
#endif
public:
    RaspiCamSrc();

    void capture(cv::Mat &mat) override;

    bool init() override;

    void setResolution(int width, int height) override;

    void setFps(int fps) override;
};


#endif //OPENCVCLIENT_RASPICAMSRC_HPP
