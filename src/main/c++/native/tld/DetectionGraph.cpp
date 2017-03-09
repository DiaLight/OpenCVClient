//
// Created by dialight on 09.03.17.
//

#include <tld/DetectionGraph.hpp>

using namespace cv;

static Scalar red(0, 0, 255);
static Scalar green(0, 255, 0);
static Scalar yellow(0, 255, 255);
static Scalar gray(128, 128, 128, 0.7);

DetectionGraph::DetectionGraph(int width, int height, float tp, float fp) {
    size = 256;
    chart = new int[size];
    for (int i = 0; i < size; i++) {
        chart[i] = 0;
    }
    pos = 0;
    chartHeight = 50;
    chartPos = Point(width / 3, height - chartHeight);

    levelTP = chartHeight - (int) (tp * chartHeight);
    levelFP = chartHeight - (int) (fp * chartHeight);
}

DetectionGraph::~DetectionGraph() {
    delete[] chart;
}

void DetectionGraph::step(float conf) {
    int level = chartHeight - (int) (conf * chartHeight);
    chart[pos++] = level;
    if(pos >= size) pos = 0;
}

void DetectionGraph::show(Mat &frame) {
    cv::rectangle(frame, chartPos, chartPos + Point(size, chartHeight), gray, CV_FILLED);
    cv::line(frame, chartPos + Point(0, levelTP), chartPos + Point(size, levelTP), green);
    cv::line(frame, chartPos + Point(0, levelFP), chartPos + Point(size, levelFP), red);
    int from = pos - 30;
    if(from < 0) from = 0;
    Point prev = chartPos + Point(from, chart[from]);
    for (int i = from + 1; i < pos; i++) {
        Point cur = chartPos + Point(i, chart[i]);
        cv::line(frame, prev, cur, yellow);
        prev = cur;
    }
}
