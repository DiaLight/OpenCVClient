//
// Created by dialight on 09.03.17.
//

#ifndef DIALIGHTTLD_LEARNINGTARGETS_HPP
#define DIALIGHTTLD_LEARNINGTARGETS_HPP

#include <opencv2/opencv.hpp>

class LearningTargets {

    std::vector<cv::Mat> targets;
    int previewSize;
    int countPerColumn;
public:
    LearningTargets(int size, int width, int height);

    void clear();

    void add(cv::Mat &frame, cv::Rect &bb);

    void show(cv::Mat &frame);
};


#endif //DIALIGHTTLD_LEARNINGTARGETS_HPP
