/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tool.hpp
 * Author: DiaLight
 *
 * Created on 24 октября 2016 г., 18:35
 */

#ifndef OPENCVTOOL_HPP
#define OPENCVTOOL_HPP

#include <opencv2/opencv.hpp>
#include <sstream>
#include "network/properties/PropertiesClient.hpp"
#include "opencv/ObjectDetect.hpp"

using namespace std;
using namespace cv;

class Tool {
    PropertiesClient *propc;
    RNG rng;
public:
    Tool(PropertiesClient *propc) : rng(12345) {
        this->propc = propc;
    }
    
    Tool(const Tool&) = delete; //deleted copy constructor
    Tool& operator=(const Tool &) = delete; //deleted copy assignment operato
    
    ~Tool(){
        
    }

    void gaussianBlur(Mat mat, int def_ksize = 7, double def_sigma = 1.5) {
        int ksize = propc->getInt("GaussianBlur.ksize", def_ksize);
        if(ksize % 2 == 0) ksize++; //OpenCV Assertion(ksize.width > 0 && ksize.width % 2 == 1 && ksize.height > 0 && ksize.height % 2 == 1)
        if(ksize < 0) ksize = 1;
        double sigma = propc->getDouble("GaussianBlur.sigma", def_sigma);
        GaussianBlur(mat, mat, Size(ksize, ksize), sigma, sigma);
    }

    void canny(Mat mat, double def_thr1 = 20, double def_thr2 = 60) {
        double threshold1 = propc->getDouble("Canny.threshold1", def_thr1);
        double threshold2 = propc->getDouble("Canny.threshold2", def_thr2);
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
        double rho = propc->getDouble("HoughLinesP.rho", 10);
        cv::HoughLinesP(gray, lines, rho, CV_PI / 180, 40, 100, 10);
        for(auto const& a : lines) {
            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
            line(frame, Point2i(a[0], a[1]), Point2i(a[2], a[3]), color, 3);
        }
    }

    void findContours(Mat gray, Mat frame) {
        vector<vector<Point>> contours;
        cv::findContours(gray, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        for(int i = 0; i < contours.size(); i++) {
            drawContours(frame, contours, i, Scalar(0, 255, 0));
        }
    }
    void findContours2(Mat gray, Mat frame) {
        int min_size = propc->getInt("Contour.min_size", 20);
        int max_size = propc->getInt("Contour.max_size", 200);
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        cv::findContours(gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//        cv::findContours(gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
        int i = 0;
        for(auto contour = contours.begin(); contour != contours.end(); ++contour) {
            vector<Point> approx;
            approxPolyDP(*contour, approx, arcLength(*contour, true)*0.05, true);
//            if(approx.size() != 3) continue;
//            double area = contourArea(approx, true);
            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

            vector<pair<Point, Point>> lines;
            int minX = frame.cols;
            int minY = frame.rows;
            int maxX = 0;
            int maxY = 0;

            Point2i center;
            auto second = approx.end() - 1;
            for(auto first = approx.begin(); first != approx.end(); ++first) {
                int x = (*first).x;
                int y = (*first).y;
                if(minX > x) minX = x;
                if(minY > y) minY = y;
                if(maxX < x) maxX = x;
                if(maxY < y) maxY = y;

                center += *first;
                lines.push_back(pair<Point, Point>(*first, *second));
                second = first;
            }
            center.x /= approx.size();
            center.y /= approx.size();
            auto rect = Rect(minX, minY, maxX - minX, maxY - minY);
            if(rect.width < min_size) continue;
            if(rect.width > max_size) continue;
            if(rect.height < min_size) continue;
            if(rect.height > max_size) continue;

            for(auto l : lines) {
                line(frame, l.first, l.second, color, 2);
            }
//            cv::rectangle(frame, rect, color, 1);

            stringstream ss;
            ss << "(" << i << ")" << approx.size();
            cv::putText(frame, ss.str(), center + Point2i(-10, -5), FONT_HERSHEY_COMPLEX_SMALL, 0.8, color, 1, CV_AA);
            i++;
        }
//        for(int i = 0; i < contours.size(); i++) {
//            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
//            drawContours(frame, contours, i, color, 2, 8, hierarchy, 0, Point());
//        }
    }

private:

};

#endif /* OPENCVTOOL_HPP */

