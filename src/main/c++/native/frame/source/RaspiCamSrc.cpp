//
// Created by dialight on 13.01.17.
//

#include <frame/source/RaspiCamSrc.hpp>

using namespace std;
using namespace cv;

RaspiCamSrc::RaspiCamSrc() {
#ifdef USE_RASPICAM
//    cam.set(CV_CAP_PROP_FRAME_WIDTH, 640);
//    cam.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    //cam->set( CV_CAP_PROP_FORMAT, CV_8UC1 );
    /*
     * CV_CAP_PROP_FRAME_WIDTH
     * CV_CAP_PROP_FRAME_HEIGHT
     * 1280x960: 29.5fps
     * 640x480 : 29.5fps
     * 320x240 : 29.5fps RGB Mode
     * 1280x960: 28 fps
     * 640x480 : 29.29fps
     * 320x240 : 29.24fps BGR Mode
     * 1280x960: 14 fps
     * 640x480 : 29.29fps
     * 320x240 : 29.24fps
     *
     * CV_CAP_PROP_FORMAT: CV_8UC1 or CV_8UC3
     * CV_CAP_PROP_BRIGHTNESS: [0,100]
     * CV_CAP_PROP_CONTRAST: [0,100]
     * CV_CAP_PROP_SATURATION: [0,100]
     * CV_CAP_PROP_GAIN: (iso): [0,100]
     * CV_CAP_PROP_EXPOSURE: -1 auto. [1,100] shutter speed from 0 to 33ms
     * CV_CAP_PROP_WHITE_BALANCE_RED_V : [1,100] -1 auto whitebalance
     * CV_CAP_PROP_WHITE_BALANCE_BLUE_U : [1,100] -1 auto whitebalance
     * CV_CAP_PROP_MODE : [1,7] 0 auto mode
     *
     */
#endif
}

bool RaspiCamSrc::init() {
#ifdef USE_RASPICAM
    if (!cam.open()) {
        cerr << "Error opening camera." << endl;
        cerr << "Ensure you have camera module connected to raspberry board through 15-pin ribbon cable." << endl;
        cerr << "Don't forget to enable camera interface with \"sudo raspi-config\" command." << endl;
        cerr << "Setting up the camera hardware instructions:" << endl;
        cerr << "https://www.raspberrypi.org/documentation/configuration/camera.md" << endl;
        return false;
    }
    return true;
#else
    cerr << "Raspicam module usage unsupported in this build." << endl;
    cerr << "Ensure Raspicam library installed in your system and recompile OpenCVClient." << endl;
    cerr << "Raspicam module repository: https://github.com/cedricve/raspicam" << endl;
    cerr << "You still can use regular usb web camera with flag -c <index>" << endl;
    cerr << "or image source with flag -i <path to image>" << endl;
    return false;
#endif
}

void RaspiCamSrc::capture(Mat &mat) {
#ifdef USE_RASPICAM
    cam.grab();
    cam.retrieve(mat);
#endif
}

void RaspiCamSrc::setResolution(int width, int height) {
#ifdef USE_RASPICAM
    cam.set(CV_CAP_PROP_FRAME_WIDTH, width);
    cam.set(CV_CAP_PROP_FRAME_HEIGHT, height);
#endif
}

void RaspiCamSrc::setFps(int fps) {
#ifdef USE_RASPICAM
    cam.set(CV_CAP_PROP_FPS, fps);
#endif
}
