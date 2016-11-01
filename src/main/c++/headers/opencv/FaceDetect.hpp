//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_FACEDETECT_HPP
#define OPENCVCLIENT_FACEDETECT_HPP

#include <opencv2/opencv.hpp>
#include <sstream>
#include <network/properties/PropertiesClient.hpp>

using namespace std;
using namespace cv;

class FaceDetect {

    PropertiesClient *propc;
    CascadeClassifier face_cascade;
public:
    FaceDetect(PropertiesClient *propc);
    FaceDetect(const FaceDetect&) = delete; //deleted copy constructor
    FaceDetect& operator=(const FaceDetect &) = delete; //deleted copy assignment operato
    virtual ~FaceDetect();

    void detectMultiScale(Mat gray, Mat frame);
};


#endif //OPENCVCLIENT_FACEDETECT_HPP
