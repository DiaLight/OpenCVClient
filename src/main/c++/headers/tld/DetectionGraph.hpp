//
// Created by dialight on 09.03.17.
//

#ifndef DIALIGHTTLD_DETECTIONGRAPH_HPP
#define DIALIGHTTLD_DETECTIONGRAPH_HPP

#include <opencv2/opencv.hpp>

class DetectionGraph {

    int size;
    int *chart;
    int pos;
    int chartHeight;
    cv::Point chartPos;
    int levelTP;
    int levelFP;
public:
    DetectionGraph(int width, int height, float tp, float fp);

    void step(float conf);

    void show(cv::Mat &mat);

    virtual ~DetectionGraph();
};


#endif //DIALIGHTTLD_DETECTIONGRAPH_HPP
