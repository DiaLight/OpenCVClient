//
// Created by dialight on 31.10.16.
//

#include <Properties.hpp>
#include <opencv/OpenCVWrap.hpp>
#include "frame/processor/ObjectDetect.hpp"

using namespace std;
using namespace cv;

ObjectDetect::ObjectDetect(const string &xmlPath) {
    //haarcascade_frontalface_default.xml
    //lbpcascade_frontalcatface.xml
    if (!classifier.load(xmlPath)) {
        cerr << "Error on loading classifier" << endl;
        exit(-1);
    }
}

ObjectDetect::~ObjectDetect() {

}

void ObjectDetect::handle(Mat &frame) {
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    CVWrap::gaussianBlur(gray, 7, 1.5);
    //        GaussianBlur(gray, gray, Size(7, 7), 1.5, 1.5);
    //        Canny(gray, gray, 0, 30, 3);
    int flags = CV_HAAR_SCALE_IMAGE;
    vector<Rect> faces;
    int min_size = props.getInt("ObjectDetect.min_size", 100);
    int max_size = props.getInt("ObjectDetect.max_size", 200);
    classifier.detectMultiScale(
            gray, faces, 1.1, 2, flags,
            Size(min_size, min_size),
            Size(max_size, max_size)
    );
    for (int i = 0; i < faces.size(); i++) { //very fast operation ( < 1 ms)
        cv::rectangle(frame, faces[i], Scalar(0, 255, 0));
        stringstream ss;
        ss << faces[i].width << " " << faces[i].height;
        cv::putText(frame, ss.str(), cvPoint(faces[i].x, faces[i].y - 5), FONT_HERSHEY_COMPLEX_SMALL, 0.8, CV_RGB(200, 200, 250), 1, LINE_AA);
    }
    faces.clear();
}
