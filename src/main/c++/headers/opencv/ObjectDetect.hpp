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

class ObjectDetect {

    CascadeClassifier classifier;
public:
    ObjectDetect(const string &xmlPath);
    ObjectDetect(const ObjectDetect&) = delete; //deleted copy constructor
    ObjectDetect& operator=(const ObjectDetect &) = delete; //deleted copy assignment operator
    virtual ~ObjectDetect();

    void detectMultiScale(Mat gray, Mat frame);
};


#endif //OPENCVCLIENT_FACEDETECT_HPP
