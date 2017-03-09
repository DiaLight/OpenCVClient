//
// Created by dialight on 09.03.17.
//

#ifndef OPENCVCLIENT_SIMPLECONFIG_HPP
#define OPENCVCLIENT_SIMPLECONFIG_HPP

#include <opencv2/opencv.hpp>

class SimpleConfig {
    cv::CommandLineParser parser;
public:

    std::string resolution;
    int fps;
    std::string imagePath;
    int deviceIndex;
    std::string xmlPath;
    std::string tldPath;
    bool local;
    std::string remote;
    bool profiler;
    int edisonDebug;
    bool flip;

    SimpleConfig(int argc, const char **argv);

    int read();

};


#endif //OPENCVCLIENT_SIMPLECONFIG_HPP
