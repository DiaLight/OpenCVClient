//
// Created by dialight on 09.03.17.
//

#ifndef OPENCVCLIENT_TLDWRAP_HPP
#define OPENCVCLIENT_TLDWRAP_HPP

#include <frame/processor/FrameProcessor.hpp>
#include "TLD.h"
#include "LearningTargets.hpp"
#include "DetectionGraph.hpp"

class TLDWrap : public FrameProcessor {

    std::string tldPath;
    tld::TLD tld;
    float threshold;

    LearningTargets *lt;
    DetectionGraph *dg;
public:
    TLDWrap(std::string const &tldPath);

    void init(cv::Mat &frame) override;

    void handle(cv::Mat &frame) override;

};


#endif //OPENCVCLIENT_TLDWRAP_HPP
