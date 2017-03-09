//
// Created by dialight on 06.11.16.
//

#ifndef OPENCVCLIENT_OPENCVMAIN_HPP
#define OPENCVCLIENT_OPENCVMAIN_HPP


#include <IntelEdison.hpp>
#include <SimpleConfig.hpp>
#include <tld/TLDWrap.hpp>
#include "FrameProcessor.hpp"

class Loop : public FrameProcessor {
    SimpleConfig *cfg;
    cv::Mat gray;
    TLDWrap tldWrap;
public:
    Loop(SimpleConfig *cfg);

    void init(cv::Mat &frame) override;

    void handle(cv::Mat &frame) override;

};


#endif //OPENCVCLIENT_OPENCVMAIN_HPP
