//
// Created by dialight on 06.12.16.
//

#include "opencv/OpenCVWrap.hpp"

void ::CVWrap::canny(Mat &mat, double def_thr1, double def_thr2) {
    double threshold1 = props.getDouble("Canny.threshold1", def_thr1);
    double threshold2 = props.getDouble("Canny.threshold2", def_thr2);
    int apertureSize = props.getInt("Canny.apertureSize", 3);
    Canny(mat, mat, threshold1, threshold2, apertureSize);
}

void ::CVWrap::gaussianBlur(Mat &mat, int def_ksize, double def_sigma) {
    int ksize = props.getInt("GaussianBlur.ksize", def_ksize);
    if(ksize % 2 == 0) ksize++; //OpenCV Assertion(ksize.width > 0 && ksize.width % 2 == 1 && ksize.height > 0 && ksize.height % 2 == 1)
    if(ksize < 0) ksize = 1;
    double sigma = props.getDouble("GaussianBlur.sigma", def_sigma);
    GaussianBlur(mat, mat, Size(ksize, ksize), sigma, sigma);
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

void ::CVWrap::harris(Mat &mat, vector<Point2i> &points,
                      int max, int def_blockSize, int def_ksize, double def_k,
                      BorderTypes def_borderType, int def_threshold) {
    int blockSize = props.getInt("Harris.blockSize", def_blockSize);
    int ksize = props.getInt("Harris.ksize", def_ksize);
    double k = props.getDouble("Harris.k", def_k);
    int borderType = props.getSelect("Harris.borderType", &HarrisBorderTypesMap, def_borderType);
    int threshold = props.getInt("Harris.threshold", def_threshold);

    Mat dst = Mat::zeros(mat.size(), CV_32FC1);

    /// Detecting corners
    cv::cornerHarris(mat, dst, blockSize, ksize, k, borderType);

    /// Normalizing
    normalize(dst, dst, 0, 255, NORM_MINMAX, CV_32FC1);
    Mat dst_norm_scaled;
    convertScaleAbs(dst, dst_norm_scaled);

    /// Drawing a circle around corners
    for(int i = 0; i < dst.cols; i++) {
        for(int j = 0; j < dst.rows ; j++) {
            if((int) dst.at<float>(j,i) > threshold) {
                if(points.size() >= max) return;
                points.push_back(Point2i(i, j));
            }
        }
    }

}

void ::CVWrap::threshold(Mat &mat) {
    cv::threshold(mat, mat, 60, 55, CV_THRESH_BINARY);
}

void ::CVWrap::adaptiveThreshold(Mat &mat) {
    cv::adaptiveThreshold(mat, mat, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 75, 10);
}

vector<Vec4i> tmp;
void ::CVWrap::houghLines(Mat &gray, vector<Line4i> &lines) {
//        double hough_rho = 1;
    double rho = props.getDouble("HoughLinesP.rho", 3);
//        double hough_theta = CV_PI / 180;
    double theta = props.getDouble("HoughLinesP.theta", CV_PI / 180);
//        int hough_treshold = 15;//70; // 15
    int treshold = props.getInt("HoughLinesP.treshold", 15);
//        double minLineLength = 65;//50; // 65
    double minLineLength = props.getDouble("HoughLinesP.minLineLength", 65);
//        double maxLineGap = 10;//20; // 10
    double maxLineGap = props.getDouble("HoughLinesP.maxLineGap", 10);

//    cv::HoughLines(gray, tmp, rho, theta, treshold);
    cv::HoughLinesP(gray, tmp, rho, theta, treshold, minLineLength, maxLineGap);
    lines.reserve(tmp.size());
    for(auto const& t : tmp) lines.push_back(Line4i(t));
    tmp.clear();
}

void ::CVWrap::findContours(Mat &gray, vector<vector<Point>> &contours) {
    cv::findContours(gray, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
}

void ::CVWrap::findContours(Mat &gray, vector<vector<Point>> &contours, vector<Vec4i> &hierarchy) {
    cv::findContours(gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
}

void ::CVWrap::approxPolyDP(vector<vector<Point>> const &in, vector<vector<Point>> &out) {
    double epsilon = props.getDouble("approxPolyDP.epsilon/perimeter", 0.05);
    for(auto const& contour : in) {
        vector<Point> approx;
        cv::approxPolyDP(contour, approx, arcLength(contour, true)*epsilon, true);
        out.push_back(approx);
    }
}

void ::CVWrap::otsu(Mat &gray) {
    double thresh = props.getDouble("otsu.thresh", 0);
    double maxval = props.getDouble("otsu.maxval", 255);
    ::threshold(gray, gray, thresh, maxval, CV_THRESH_OTSU);
}

