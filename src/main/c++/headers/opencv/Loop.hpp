//
// Created by dialight on 06.11.16.
//

#ifndef OPENCVCLIENT_OPENCVMAIN_HPP
#define OPENCVCLIENT_OPENCVMAIN_HPP


#include "Tool.hpp"

class Loop {
    PropertiesClient *propc;
    Tool *tool;
    Mat gray;
public:
    Loop(PropertiesClient *propc, Tool *tool);

    Mat loop(Mat frame);
};


#endif //OPENCVCLIENT_OPENCVMAIN_HPP
