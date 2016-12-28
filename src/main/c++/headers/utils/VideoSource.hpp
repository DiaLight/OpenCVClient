//
// Created by dialight on 25.11.16.
//

#ifndef OPENCVCLIENT_VIDEOSOURCE_HPP
#define OPENCVCLIENT_VIDEOSOURCE_HPP

#include <string>
#include <opencv2/opencv.hpp>
#ifdef USE_RASPICAM
#include <raspicam/raspicam_cv.h>
#endif

using namespace std;
using namespace cv;

class VideoSource {
    enum VIDEO_SOURCE {
        NONE,
        OPENCV_VIDEO,
        IMAGE,
#ifdef USE_RASPICAM
        RASPICAM,
#endif
    };

    VIDEO_SOURCE src;

#ifdef USE_RASPICAM
    raspicam::RaspiCam_Cv *cam;
#endif
    VideoCapture *cap = nullptr;
    Mat image;
public:
    VideoSource();

    virtual ~VideoSource();

    bool setOpenCVBased(int deviceIndex);

    bool setImageBased(const string& imagePath);

    bool setRaspicamBased();

    void capture(Mat &mat);
};


#endif //OPENCVCLIENT_VIDEOSOURCE_HPP
