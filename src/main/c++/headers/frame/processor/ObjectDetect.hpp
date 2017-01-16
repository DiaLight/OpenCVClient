//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_OBJECTDETECT_HPP
#define OPENCVCLIENT_OBJECTDETECT_HPP

#include <opencv2/opencv.hpp>
#include <sstream>
#include <network/properties/PropertiesClient.hpp>
#include <frame/processor/FrameProcessor.hpp>

class ObjectDetect : public FrameProcessor {

    cv::Mat gray;
    cv::CascadeClassifier classifier;
public:
    ObjectDetect(const std::string &xmlPath);
    ObjectDetect(const ObjectDetect&) = delete; //deleted copy constructor
    ObjectDetect& operator=(const ObjectDetect &) = delete; //deleted copy assignment operator
    virtual ~ObjectDetect();

    void handle(cv::Mat &frame) override;

};


#endif //OPENCVCLIENT_OBJECTDETECT_HPP
