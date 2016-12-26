//
// Created by dialight on 26.11.16.
//

#include <utils/FrameProcessor.hpp>
#include <opencv/OpenCVWrap.hpp>

FrameProcessor::FrameProcessor() : proc(NONE) {

}

FrameProcessor::~FrameProcessor() {
    switch (proc) {
        case NONE:break;
        case CLASSIFIER:
            delete detect;
            break;
        case MANUAL:
            delete loop;
            break;
    }
}

bool FrameProcessor::setClassifierBased(const string &xmlPath) {
    if(proc != FRAME_PROCESSOR::NONE) return false;
    detect = new ObjectDetect(xmlPath);
    proc = FRAME_PROCESSOR::CLASSIFIER;
    return true;
}

void FrameProcessor::setManualHandler() {
    if(proc != FRAME_PROCESSOR::NONE) return;
    loop = new Loop();
    proc = FRAME_PROCESSOR::MANUAL;
}

void FrameProcessor::handle(Mat &frame) {
    switch (proc) {
        case NONE:break;
        case CLASSIFIER:
            detect->detectMultiScale(frame);
            break;
        case MANUAL:
            loop->loop(frame);
            break;
    }
}
