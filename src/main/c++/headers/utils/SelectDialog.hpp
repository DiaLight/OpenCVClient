//
// Created by dialight on 09.03.17.
//

#ifndef DIALIGHTTLD_SELECTDIALOG_HPP
#define DIALIGHTTLD_SELECTDIALOG_HPP


#include <opencv2/core/mat.hpp>
#include <TLD.h>

class SelectDialog {

    cv::Mat img0;
    cv::Mat img1;
    cv::Point point;
    cv::Rect *bb;
    bool drag = 0;

    std::string windowName;
    bool showCall = false;
public:
    SelectDialog(const std::string &windowName);
    void loop(cv::Mat &mat, tld::TLD &tld);
    void show();

    void mouseHandler(int event, int x, int y, int flags);

private:
    bool getBBFromUser(cv::Mat &frame, cv::Rect &rect);

};


#endif //DIALIGHTTLD_SELECTDIALOG_HPP
