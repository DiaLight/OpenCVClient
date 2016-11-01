//
// Created by dialight on 31.10.16.
//

#include "opencv/FaceDetect.hpp"

FaceDetect::FaceDetect(PropertiesClient *propc) {
    this->propc = propc;
    //haarcascade_frontalface_default.xml
    //lbpcascade_frontalcatface.xml
    if (!face_cascade.load("/home/dialight/haarcascade_frontalface_default.xml")) {
        cout << "Error on loading classifier" << endl;
        exit(1);
    }
}

FaceDetect::~FaceDetect() {

}

void FaceDetect::detectMultiScale(Mat gray, Mat frame) {
    //        GaussianBlur(gray, gray, Size(7, 7), 1.5, 1.5);
    //        Canny(gray, gray, 0, 30, 3);
    int flags = CV_HAAR_SCALE_IMAGE;
    vector<Rect> faces;
    int min_face_size = propc->getInt("detectMultiScale.min_size", 100);
    int max_face_size = propc->getInt("detectMultiScale.max_size", 200);
    face_cascade.detectMultiScale(
            gray, faces, 1.1, 2, flags,
            Size(min_face_size, min_face_size),
            Size(max_face_size, max_face_size)
    );
    for (int i = 0; i < faces.size(); i++) { //very fast operation ( < 1 ms)
        cv::rectangle(frame, faces[i], Scalar(0, 255, 0));
        stringstream ss;
        ss << faces[i].width << " " << faces[i].height;
        cv::putText(frame, ss.str(), cvPoint(faces[i].x, faces[i].y - 5), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
    }
    faces.clear();
}
