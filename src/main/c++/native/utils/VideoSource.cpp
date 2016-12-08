//
// Created by dialight on 25.11.16.
//

#include <utils/VideoSource.hpp>

VideoSource::VideoSource() : src(NONE) {}

VideoSource::~VideoSource() {
    switch (src) {
        case NONE:break;
        case OPENCV_VIDEO:
            cap->release();
            delete cap;
            break;
        case IMAGE:break;
#ifdef USE_RASPICAM
        case RASPICAM:
            cam->release();
            delete cam;
            break;
#endif
    }
}

bool VideoSource::setOpenCVBased(int deviceIndex) {
    if(src != VIDEO_SOURCE::NONE) return false;
    //init video source
    cap = new VideoCapture(deviceIndex); // default camera
    if (!cap->isOpened()) {
        cerr << "No video capture device with index " << deviceIndex << endl;
        return false;
    }
    src = VIDEO_SOURCE::OPENCV_VIDEO;
    return true;
}

bool VideoSource::setImageBased(const string& imagePath) {
    if(src != VIDEO_SOURCE::NONE) return false;
    image = imread(imagePath, 1);
    if(image.empty()) {
        cerr << "Cannot read image file: " << imagePath << endl;
        return false;
    }
    src = VIDEO_SOURCE::IMAGE;
    return true;
}

bool VideoSource::setRaspicamBased() {
    if(src != VIDEO_SOURCE::NONE) return false;
#ifdef USE_RASPICAM
    cam = new raspicam::RaspiCam_Cv();
    cam->set( CV_CAP_PROP_FORMAT, CV_8UC1 );
    if ( !cam->open()) {
        cerr << "Error opening camera" << endl;
        return false;
    }
    src = VIDEO_SOURCE::RASPICAM;
    return true;
#else
    cerr << "Raspicam module usage unsupported in this build." << endl;
    cerr << "Ensure Raspicam library installed in your system and recompile OpenCVClient." << endl;
    cerr << "Raspicam module repository: https://github.com/cedricve/raspicam" << endl;
    cerr << "You still can use regular usb web camera with flag -c <index>" << endl;
    cerr << "or image source with flag -i <path to image>" << endl;
    return false;
#endif
}

void VideoSource::capture(Mat &mat) {
    switch (src) {
        case NONE:
            cerr << "There is no opened video source" << endl;
            exit(-1);
        case OPENCV_VIDEO:
            *cap >> mat;
            break;
        case IMAGE:
            mat = image.clone();
            break;
#ifdef USE_RASPICAM
        case RASPICAM:
            cam->grab();
            cam->retrieve(mat);
            break;
#endif
    }
}
