//
// Created by dialight on 13.01.17.
//

#include <frame/source/ImageSrc.hpp>

using namespace std;
using namespace cv;

ImageSrc::ImageSrc(const string &imagePath) : imagePath(imagePath) {
    image = imread(imagePath, 1);
}

bool ImageSrc::init() {
    if(image.empty()) {
        cerr << "Cannot read image file: " << imagePath << endl;
        return false;
    }
    return true;
}

void ImageSrc::capture(Mat &mat) {
    mat = image.clone();
}

void ImageSrc::setResolution(int width, int height) {
    resize(image, image, Size2i(width, height));
//    image.create(width, height, image.type());
}

void ImageSrc::setFps(int fps) {

}
