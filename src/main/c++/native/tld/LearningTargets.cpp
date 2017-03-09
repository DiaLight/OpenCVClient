//
// Created by dialight on 09.03.17.
//

#include <tld/LearningTargets.hpp>

using namespace cv;
using namespace std;

LearningTargets::LearningTargets(int size, int width, int height) {
    previewSize = size;
    countPerColumn = height / previewSize;
}

void LearningTargets::clear() {
    targets.clear();
}

void LearningTargets::add(cv::Mat &frame, cv::Rect &bb) {
    Mat target;
    resize(Mat(frame, bb), target, Size(previewSize, previewSize));
    targets.push_back(target);
}

void LearningTargets::show(cv::Mat &frame) {
    int i = 0;
    for(auto const &trg : targets) {
        int x = (i / countPerColumn) * previewSize;
        int y = (i % countPerColumn) * previewSize;
        i++;
        trg.copyTo(Mat(frame, Rect(x, y, previewSize, previewSize)));
    }
}
