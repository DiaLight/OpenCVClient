//
// Created by dialight on 26.11.16.
//

#include <utils/FrameProcessor.hpp>

FrameProcessor::FrameProcessor() : proc(NONE) {

}

FrameProcessor::~FrameProcessor() {
    switch (proc) {
        case NONE:break;
        case CLASSIFIER:
            delete detect;
            break;
        case MANUAL:
            delete cvMain;
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
    cvMain = new Loop(&tool);
    proc = FRAME_PROCESSOR::MANUAL;
}

Mat FrameProcessor::handle(Mat frame) {
    Mat gray;
    switch (proc) {
        case NONE:break;
        case CLASSIFIER:
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            tool.gaussianBlur(gray, 7, 1.5);
            detect->detectMultiScale(gray, frame);
            break;
        case MANUAL:
            return cvMain->loop(frame);
    }
    return frame;
}
