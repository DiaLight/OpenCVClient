//
// Created by dialight on 09.03.17.
//

#include "SimpleConfig.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static String keys = ""
        "{help h usage ? |               | print this message                                                                }"
        "{res resolution |               | capture resolution (Example: 640x480)                                             }"
        "{fps            | -1.0          | fixed fps for video capture                                                       }"
        "{i image        |               | Replace video stream with image                                                   }"
        "{c camera       |-1             | Set index of web camera inside OpenCV VideoCapture class. Must be > 0.            }"
        "{xml            |               | Path to xml of the object detect classifier                                       }"
        "{tld            |               | Path to tld classifier                                                            }"
        "{flip           |false          | Flip image                                                                        }"
        //View settings
        "{l local        |false          | Create simple local gui                                                           }"
        "{r remote       |localhost:2016 | Video stream to remote server                                                     }"
        //Debug settings
        "{p profiler     |false          | Enable profiler messages to console                                               }"
        "{d debug        |-1             | Edison connection debug. Sends '1' symbol to Edison every N seconds. Must be > 0. }"
;

SimpleConfig::SimpleConfig(int argc, const char **argv) : parser(argc, argv, keys) {
    parser.about("OpenCVClient");
}

int SimpleConfig::read() {
    if (parser.has("help")) {
        parser.printMessage();
        return false;
    }

    //Capture settings
    resolution = parser.get<String>("resolution");
    fps = parser.get<int>("fps");
    imagePath = parser.get<String>("image");
    deviceIndex = parser.get<int>("camera");
    //Frame process settings
    xmlPath = parser.get<String>("xml");
    tldPath = parser.get<String>("tld");
    //View settings
    local = parser.get<bool>("local");
    remote = parser.get<String>("remote");
    //Debug settings
    profiler = parser.get<bool>("profiler");
    edisonDebug = parser.get<int>("debug");

    flip = parser.get<bool>("flip");


    if (!parser.check()) {
        parser.printErrors();
        return false;
    }
    return true;
}
