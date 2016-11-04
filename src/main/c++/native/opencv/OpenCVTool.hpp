/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OpenCVTool.hpp
 * Author: DiaLight
 *
 * Created on 24 октября 2016 г., 18:35
 */

#ifndef OPENCVTOOL_HPP
#define OPENCVTOOL_HPP

#include <opencv2/opencv.hpp>
#include <sstream>
#include "network/properties/PropertiesClient.hpp"
#include "opencv/FaceDetect.hpp"

using namespace std;
using namespace cv;

class OpenCVTool {
    PropertiesClient *propc;
public:
    FaceDetect faceDetect;
    OpenCVTool(PropertiesClient *propc) : faceDetect(propc) {
        this->propc = propc;
    }
    
    OpenCVTool(const OpenCVTool&) = delete; //deleted copy constructor
    OpenCVTool& operator=(const OpenCVTool &) = delete; //deleted copy assignment operato
    
    ~OpenCVTool(){
        
    }

    void gaussianBlur(Mat mat, int def_ksize = 7, double def_sigma = 1.5) {
        int ksize = propc->getInt("GaussianBlur.ksize", def_ksize);
        if(ksize % 2 == 0) ksize++; //OpenCV Assertion(ksize.width > 0 && ksize.width % 2 == 1 && ksize.height > 0 && ksize.height % 2 == 1)
        if(ksize < 0) ksize = 1;
        double sigma = propc->getDouble("GaussianBlur.sigma", def_sigma);
        GaussianBlur(mat, mat, Size(ksize, ksize), sigma, sigma);
    }

    void canny(Mat mat, double def_thr1 = 0, double def_thr2 = 30.0) {
        double threshold1 = propc->getDouble("Canny.thr1", def_thr1);
        double threshold2 = propc->getDouble("Canny.thr2", def_thr2);
        Canny(mat, mat, threshold1, threshold2, 3);
    }

    void threshold(Mat mat) {
        cv::threshold(mat, mat, 60, 55, CV_THRESH_BINARY);
    }

    void adaptiveThreshold(Mat mat) {
        cv::adaptiveThreshold(mat, mat, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 75, 10);
    }

    void houghLines(Mat gray, Mat frame) {
        vector<Vec4i> lines;
        cv::HoughLinesP(gray, lines, 10, CV_PI / 180, 40, 100, 10);
        for (int i = 0; i < lines.size(); i++) {
            Vec4i a = lines[i];
            int x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3];
            line(frame, Point2i(x1, y1), Point2i(x2, y2), Scalar(0, 255, 0));
        }
    }

    void findContours(Mat gray, Mat frame) {
        vector<vector<Point>> contours;
        cv::findContours(gray, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        cv::drawContours(frame, contours, 10, Scalar(0, 255, 0), CV_FILLED);
//        for (int i = 0; i < contours.size(); i++) {
//            vector<Point> contour = contours[i];
//            
//            line(frame, Point2i(x1, y1), Point2i(x2, y2), Scalar(0, 255, 0));
//        }
    }

private:

};

#endif /* OPENCVTOOL_HPP */

