//
// Created by dialight on 13.01.17.
//

#ifndef OPENCVCLIENT_PICTURESRC_HPP
#define OPENCVCLIENT_PICTURESRC_HPP


#include "FrameSource.hpp"

class ImageSrc : public FrameSource {

    std::string imagePath;
    cv::Mat image;
public:
    ImageSrc(const std::string &imagePath);

    bool init() override;

    void capture(cv::Mat &mat) override;

    void setResolution(int width, int height) override;

    void setFps(int fps) override;
};


#endif //OPENCVCLIENT_PICTURESRC_HPP
