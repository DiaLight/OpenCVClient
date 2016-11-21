//
// Created by dialight on 31.10.16.
//

#include "opencv/ObjectDetect.hpp"

ObjectDetect::ObjectDetect(PropertiesClient *propc) {
    this->propc = propc;
    //haarcascade_frontalface_default.xml
    //lbpcascade_frontalcatface.xml
    if (!classifier.load("/home/dialight/haarcascade_frontalface_default.xml")) {
        cout << "Error on loading classifier" << endl;
        exit(1);
    }
}

ObjectDetect::~ObjectDetect() {

}

void ObjectDetect::detectMultiScale(Mat gray, Mat frame) {
    //        GaussianBlur(gray, gray, Size(7, 7), 1.5, 1.5);
    //        Canny(gray, gray, 0, 30, 3);
    int flags = CV_HAAR_SCALE_IMAGE;
    vector<Rect> faces;
    int min_size = propc->getInt("ObjectDetect.min_size", 100);
    int max_size = propc->getInt("ObjectDetect.max_size", 200);
    classifier.detectMultiScale(
            gray, faces, 1.1, 2, flags,
            Size(min_size, min_size),
            Size(max_size, max_size)
    );
    for (int i = 0; i < faces.size(); i++) { //very fast operation ( < 1 ms)
        cv::rectangle(frame, faces[i], Scalar(0, 255, 0));
        stringstream ss;
        ss << faces[i].width << " " << faces[i].height;
        cv::putText(frame, ss.str(), cvPoint(faces[i].x, faces[i].y - 5), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
    }
    faces.clear();
}
