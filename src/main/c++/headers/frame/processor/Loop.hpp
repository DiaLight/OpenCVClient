//
// Created by dialight on 06.11.16.
//

#ifndef OPENCVCLIENT_OPENCVMAIN_HPP
#define OPENCVCLIENT_OPENCVMAIN_HPP


#include <IntelEdison.hpp>
#include "FrameProcessor.hpp"

class Loop : public FrameProcessor {
    cv::Mat gray;
public:

    void handle(cv::Mat &frame) override;

};


#endif //OPENCVCLIENT_OPENCVMAIN_HPP
