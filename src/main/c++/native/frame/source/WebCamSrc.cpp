//
// Created by dialight on 13.01.17.
//

#include "frame/source/WebCamSrc.hpp"

using namespace std;
using namespace cv;

WebCamSrc::WebCamSrc(int deviceIndex) : deviceIndex(deviceIndex) {
    cap = new VideoCapture(deviceIndex);
}

WebCamSrc::~WebCamSrc() {
    delete cap;
}

bool WebCamSrc::init() {
    if (!cap->isOpened()) {
        cerr << "No video capture device with index " << deviceIndex << endl;
        return false;
    }
    return true;
}

void WebCamSrc::capture(Mat &mat) {
    *cap >> mat;
}

void WebCamSrc::setResolution(int width, int height) {
    cap->set(CAP_PROP_FRAME_WIDTH, width);
    cap->set(CAP_PROP_FRAME_HEIGHT, height);
}

void WebCamSrc::setFps(int fps) {
    cap->set(CAP_PROP_FPS, fps);
}
