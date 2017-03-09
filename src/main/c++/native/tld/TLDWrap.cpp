//
// Created by dialight on 09.03.17.
//

#include <opencv2/opencv.hpp>
#include <tld/TLDWrap.hpp>
#include <opencv/OpenCVWrap.hpp>

using namespace std;
using namespace cv;

static Scalar yellow(0, 255, 255);
static Scalar blue(255, 0, 0);
static Scalar white(255, 255, 255);


TLDWrap::TLDWrap(string const &tldPath) : tldPath(tldPath) {
//    tld.trackerEnabled = true;
//    tld.alternating = false;
//    tld.learningEnabled = true;

    tld::DetectorCascade *detectorCascade = tld.detectorCascade;
//    detectorCascade->varianceFilter->enabled = true;
//    detectorCascade->ensembleClassifier->enabled = true;
    detectorCascade->nnClassifier->enabled = true;

    // classifier
//    detectorCascade->useShift = true;
//    detectorCascade->shift = 0.1f;
//    detectorCascade->minScale = -10;
//    detectorCascade->maxScale = 10;
//    detectorCascade->minSize = 25;
//    detectorCascade->numTrees = 10;
    detectorCascade->numFeatures = 13;
    threshold = detectorCascade->nnClassifier->thetaTP;
//    detectorCascade->nnClassifier->thetaTP = threshold;
//    detectorCascade->nnClassifier->thetaFP = 0.5f;

    tld.readFromFile(tldPath.c_str());
}


void TLDWrap::init(cv::Mat &frame) {
    tld::DetectorCascade *detectorCascade = tld.detectorCascade;
    {
        Mat gray;
        cvtColor(frame, gray, CV_BGR2GRAY);
        detectorCascade->imgWidth = gray.cols;
        detectorCascade->imgHeight = gray.rows;
        detectorCascade->imgWidthStep = (int) gray.step;
    }

    lt = new LearningTargets(15, frame.cols, frame.rows);

    dg = new DetectionGraph(
            frame.cols, frame.rows,
            detectorCascade->nnClassifier->thetaTP,
            detectorCascade->nnClassifier->thetaFP
    );
}

void TLDWrap::handle(cv::Mat &frame) {
    CVWrap::gaussianBlur(frame, 7, 1.5);

    tld.processImage(frame);

    if (tld.currBB != NULL) {
        if(tld.currConf < threshold) {
            lt->add(frame, *tld.currBB);
        }
        rectangle(frame, *tld.currBB, (tld.currConf >= threshold) ? blue : yellow, 4);
    }
    lt->show(frame);

    dg->step(tld.currConf);
    dg->show(frame);

//        for(auto const &r : *tld.detectorCascade->detectionResult->fgList) {
//            rectangle(frame, r, white, 1);
//        }
}

