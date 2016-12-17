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
#include <opencv/ObjectDetect.hpp>
#include <Properties.hpp>
#include "Types.hpp"

using namespace std;
using namespace cv;

class Tool {
    RNG rng;

    vector<Vec4i> tmp;
public:
    Tool(int i = 0) : rng(12345) {
    }
    
    Tool(const Tool&) = delete; //deleted copy constructor
    Tool& operator=(const Tool &) = delete; //deleted copy assignment operato
    
    ~Tool(){
        
    }

    // Deprecated
    void gaussianBlur(Mat mat, int def_ksize = 7, double def_sigma = 1.5) {
        int ksize = props.getInt("GaussianBlur.ksize", def_ksize);
        if(ksize % 2 == 0) ksize++; //OpenCV Assertion(ksize.width > 0 && ksize.width % 2 == 1 && ksize.height > 0 && ksize.height % 2 == 1)
        if(ksize < 0) ksize = 1;
        double sigma = props.getDouble("GaussianBlur.sigma", def_sigma);
        GaussianBlur(mat, mat, Size(ksize, ksize), sigma, sigma);
    }

    void canny(Mat mat, double def_thr1 = 20, double def_thr2 = 60) {
        double threshold1 = props.getDouble("Canny.threshold1", def_thr1);
        double threshold2 = props.getDouble("Canny.threshold2", def_thr2);
        int apertureSize = props.getInt("Canny.apertureSize", 3);
        Canny(mat, mat, threshold1, threshold2, apertureSize);
    }

    map<int, string> HarrisBorderTypesMap = {
            {BorderTypes::BORDER_CONSTANT, "Constant"},
            {BorderTypes::BORDER_REPLICATE, "Replicate"},
            {BorderTypes::BORDER_REFLECT, "Reflect"},
            {BorderTypes::BORDER_WRAP, "Wrap"},
            {BorderTypes::BORDER_REFLECT_101, "Reflect 101"},
            {BorderTypes::BORDER_TRANSPARENT, "Transparent"},
            {BorderTypes::BORDER_ISOLATED, "Isolated"}
    };
    void harris(Mat mat, vector<Point2i> &points, int max = 300, int def_blockSize = 7, int def_ksize = 5, double def_k = 0.05, BorderTypes def_borderType = BorderTypes::BORDER_DEFAULT, int def_threshold = 200) {
        int blockSize = props.getInt("Harris.blockSize", def_blockSize);
        int ksize = props.getInt("Harris.ksize", def_ksize);
        double k = props.getDouble("Harris.k", def_k);
        int borderType = props.getSelect("Harris.borderType", &HarrisBorderTypesMap, def_borderType);
        int threshold = props.getInt("Harris.threshold", def_threshold);

        Mat dst = Mat::zeros(mat.size(), CV_32FC1);

        /// Detecting corners
        cv::cornerHarris(mat, dst, blockSize, ksize, k, borderType);

        /// Normalizing
        normalize(dst, dst, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
        Mat dst_norm_scaled;
        convertScaleAbs(dst, dst_norm_scaled);

        /// Drawing a circle around corners
        for(int j = 0; j < dst.rows ; j++) {
            for(int i = 0; i < dst.cols; i++) {
                if((int) dst.at<float>(j,i) > threshold) {
                    if(points.size() >= max) return;
                    points.push_back(Point2i(i, j));
                }
            }
        }

    }

    void showPoints(Mat &frame, vector<Point2i> const &points) {
        for(auto const& p : points) {
            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
            cv::circle(frame, p, 5,  color, 2, LineTypes::LINE_AA);
        }
    }

    void threshold(Mat mat) {
        cv::threshold(mat, mat, 60, 55, CV_THRESH_BINARY);
    }

    void adaptiveThreshold(Mat mat) {
        cv::adaptiveThreshold(mat, mat, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 75, 10);
    }

    void houghLines(Mat gray, vector<Line4i> &lines) {
//        double hough_rho = 1;
        double rho = props.getDouble("HoughLinesP.rho", 10);
//        double hough_theta = CV_PI / 180;
        double theta = props.getDouble("HoughLinesP.theta", CV_PI / 180);
//        int hough_treshold = 15;//70; // 15
        int treshold = props.getInt("HoughLinesP.treshold", 15);
//        double minLineLength = 65;//50; // 65
        double minLineLength = props.getDouble("HoughLinesP.minLineLength", 65);
//        double maxLineGap = 10;//20; // 10
        double maxLineGap = props.getDouble("HoughLinesP.maxLineGap", 10);

        cv::HoughLinesP(gray, tmp, rho, theta, treshold, minLineLength, maxLineGap);
        lines.reserve(tmp.size());
        for(auto const& t : tmp) lines.push_back(Line4i(t));
        tmp.clear();
    }

    void showLines(Mat &frame, vector<Line4i> const &lines) {
        for(auto const& l : lines) {
            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
            cv::line(frame, l.p1, l.p2, color, 3, LineTypes::LINE_AA);
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
        int min_size = props.getInt("Contour.min_size", 20);
        int max_size = props.getInt("Contour.max_size", 200);
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
            cv::putText(frame, ss.str(), center + Point2i(-10, -5), FONT_HERSHEY_COMPLEX_SMALL, 0.8, color, 1, LineTypes::LINE_AA);
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

