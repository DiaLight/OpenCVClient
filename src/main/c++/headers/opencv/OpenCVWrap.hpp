//
// Created by dialight on 06.12.16.
//

#ifndef OPENCVCLIENT_OPENCVWRAP_HPP
#define OPENCVCLIENT_OPENCVWRAP_HPP

#include <opencv2/opencv.hpp>
#include <sstream>
#include "network/properties/PropertiesClient.hpp"
#include "Types.hpp"
#include <Properties.hpp>

using namespace std;
using namespace cv;

namespace CVWrap {

    void canny(Mat &mat, double def_thr1 = 20, double def_thr2 = 60);

    void gaussianBlur(Mat &mat, int def_ksize = 7, double def_sigma = 1.5);

    void harris(Mat &mat, vector<Point2i> &points, int max = 300, int def_blockSize = 7, int def_ksize = 5, double def_k = 0.05, BorderTypes def_borderType = BorderTypes::BORDER_DEFAULT, int def_threshold = 200);

    void threshold(Mat &mat);

    void adaptiveThreshold(Mat &mat);

    void houghLines(Mat &gray, vector<Line4i> &lines);

    void findContours(Mat &gray, vector<vector<Point>> &contours);

    void findContours(Mat &gray, vector<vector<Point>> &contours, vector<Vec4i> &hierarchy);

    void approxPolyDP(vector<vector<Point>> const &in, vector<vector<Point>> &out);
};


#endif //OPENCVCLIENT_OPENCVWRAP_HPP
