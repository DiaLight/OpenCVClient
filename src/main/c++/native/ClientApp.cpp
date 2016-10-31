/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Main.cpp
 * Author: dialight
 *
 * Created on 13 октября 2016 г., 8:42
 */

#include "AppState.hpp"
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <sstream>
#include <csignal>
#include "Profiler.hpp"
#include "network/stream/StreamClient.hpp"
#include "network/stream/ImagePacket.hpp"
#include "opencv/OpenCVTool.hpp"
#include "network/properties/PropertiesClient.hpp"

using namespace std;
using namespace cv;

void signalHandler(int signum) {
    alive = false;
}

int main(int argc, char** argv) {

    //get target address from command line args
    ServerAddr addr(argc, argv);

    //init video source
    VideoCapture cap(0); // default camera
    if (!cap.isOpened()) {
        cout << "No video capture device" << endl;
        alive = false;
        return -1;
    }
    
    //init tcp properties client bound to target address
    PropertiesClient propc(&addr);
    propc.runAsync();

    //init udp stream client bound to target address
    StreamClient scli;
    ImagePacket packet; //network structure
    scli.bind();
    
    //setup signal handler for caught interrupts
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    
    OpenCVTool tool(&propc); 
    Profiler prof(false);
    Mat frame;
    Mat gray;
    try {
        while (alive) {
            prof.start();

            cap >> frame;
            prof.point("Capture");

            cvtColor(frame, gray, COLOR_BGR2GRAY);
            switch(propc.getInt("method", 2)) {
                case 0:
                    tool.gaussianBlur(gray, 7, 15);
                    tool.canny(gray, 0, 300); //обводит резкие линии(детектор границ Кенни)
                    tool.faceDetect(gray, frame);
                    break;
                case 1:
                    tool.gaussianBlur(gray, 7, 15);
                    tool.canny(gray, 0, 300);
                    tool.houghLines(gray, frame);
                    break;
                case 2:
                    tool.gaussianBlur(gray, 7, 15);
                    tool.canny(gray, 0, 250);
                    tool.findContours(gray, frame);
                    break;
                    
                case 10: //тест блюра
                    tool.gaussianBlur(gray, 7, 15); //размытие(быстрое убирание помех на изображении)
                    frame = gray;
                    break;
                case 11: //тест метода Кенни на блюре
                    tool.gaussianBlur(gray, 7, 15);
                    tool.canny(gray, 0, 300); //обводит резкие линии(детектор границ Кенни)
                    frame = gray;
                    break;
                case 12: //тест порогового преобразования на блюре
                    tool.gaussianBlur(gray, 3, 0);
                    tool.threshold(gray);
                    bitwise_not(gray, gray);
                    frame = gray;
                    break;
                case 13: //тест адаптивного порогового преобразования на блюре
                    tool.gaussianBlur(gray, 3, 0);
                    tool.adaptiveThreshold(gray);
                    bitwise_not(gray, gray);
                    frame = gray;
                    break;
            }
            prof.point("OpenCV");

            packet.setImage(frame);
            prof.point("Compress");

            packet.send(&scli, &addr); //very fast operation ( < 1 ms)

            prof.end();
            //if (waitKey(15) >= 0) break;
        }
    } catch(cv::Exception e) {
        //cerr << e.what() << endl;
        cerr << "err: " << e.err << endl;
        cerr << "file: " << e.file << endl;
        cerr << "func: " << e.func << endl;
        cerr << "msg: " << e.msg << endl;
    }
    alive = false;
    cout << endl << "Exit nicely" << endl;
    return 0;
}

