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

using namespace std;
using namespace cv;

class OpenCVTool {
    PropertiesClient *propc;
    CascadeClassifier face_cascade;
    vector<Rect> faces;
    Size min_face;
    Size max_face;
public:
    OpenCVTool(PropertiesClient *propc) {
        this->propc = propc;
        int min_face_size = 100;
        int max_face_size = 200;
        min_face = Size(min_face_size, min_face_size);
        max_face = Size(max_face_size, max_face_size);
        //haarcascade_frontalface_default.xml
        //lbpcascade_frontalcatface.xml
        if (!face_cascade.load("/home/dialight/haarcascade_frontalface_default.xml")) {
            cout << "Error on loading classifier" << endl;
            exit(1);
        }
    }
    
    OpenCVTool(const OpenCVTool&) = delete; //deleted copy constructor
    OpenCVTool& operator=(const OpenCVTool &) = delete; //deleted copy assignment operato
    
    ~OpenCVTool(){
        
    }

    void gaussianBlur(Mat mat, int def_ksize = 7, int def_sigma = 15) {
        int ksize = propc->getInt("GaussianBlur.ksize", def_ksize);
        if(ksize % 2 == 0) ksize++; //OpenCV Assertion(ksize.width > 0 && ksize.width % 2 == 1 && ksize.height > 0 && ksize.height % 2 == 1)
        if(ksize < 0) ksize = 1;
        double sigma = propc->getInt("GaussianBlur.sigma", def_sigma) * 0.1;
        GaussianBlur(mat, mat, Size(ksize, ksize), sigma, sigma);
    }

    void canny(Mat mat, int def_thr1 = 0, int def_thr2 = 300) {
        double threshold1 = propc->getInt("Canny.thr1", def_thr1) * 0.1;
        double threshold2 = propc->getInt("Canny.thr2", def_thr2) * 0.1;
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
    
    void faceDetect(Mat gray, Mat frame) {
        //        GaussianBlur(gray, gray, Size(7, 7), 1.5, 1.5);
        //        Canny(gray, gray, 0, 30, 3);
        int flags = CV_HAAR_SCALE_IMAGE;
        face_cascade.detectMultiScale(gray, faces, 1.1, 2, flags, min_face, max_face);
        for (int i = 0; i < faces.size(); i++) { //very fast operation ( < 1 ms)
            cv::rectangle(frame, faces[i], Scalar(0, 255, 0));
            stringstream ss;
            ss << faces[i].width << " " << faces[i].height;
            cv::putText(frame, ss.str(), cvPoint(faces[i].x, faces[i].y - 5), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
        }
        faces.clear();
    }
private:

};

#endif /* OPENCVTOOL_HPP */

