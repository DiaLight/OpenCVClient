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
#include <csignal>
#include <iomanip>
#include "Profiler.hpp"
#include "network/stream/StreamClient.hpp"
#include "network/stream/ImagePacket.hpp"
#include "opencv/OpenCVTool.hpp"
#include <utils/MacroEnumString.hpp>

using namespace std;
using namespace cv;

void signalHandler(int signum) {
    alive = false;
    cond.notifyAll();
    cout << "Terminated with signal " << signum << " " << strsignal(signum) << endl;
}

#define MethodsMacro(m) \
    m(RAW, "Без оработки") \
    m(FACE_DETECT, "Face detect") \
    m(LINES, "Lines") \
    m(CONTOURS, "Contours") \
    m(BLUR_TEST, "Тест блюра") \
    m(KENNY_TEST, "Тест метода кенни") \
    m(THRESHOLD_TEST, "тест порогового преобразования") \
    m(ADAPTIVE_THRESHOLD_TEST, "тест адаптивного порогового преобразования")
ENUM_STRING(MethodsMacro, Methods, MethodsVector)

int main(int argc, char** argv) {
    try {
        //get target address from command line inArgs
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

        //setup signal inHandler for caught interrupts
        signal(SIGINT, signalHandler);
        signal(SIGTERM, signalHandler);

        OpenCVTool tool(&propc);
        Profiler prof(false);
        Mat frame;
        Mat gray;
        while (alive) {
            prof.start();

            cap >> frame;
            prof.point("Capture");

            cvtColor(frame, gray, COLOR_BGR2GRAY);
            switch(propc.getSelect("method", &MethodsVector, Methods::CONTOURS)) {
                case Methods::RAW: break;
//                case Methods::FACE_DETECT:
//                    tool.gaussianBlur(gray, 7, 1.5);
//                    tool.faceDetect.detectMultiScale(gray, frame);
//                    break;
                case Methods::LINES:
                    tool.gaussianBlur(gray, 7, 1.5);
                    tool.canny(gray, 30, 60);
                    tool.houghLines(gray, frame);
                    break;
                case Methods::CONTOURS:
                    tool.gaussianBlur(gray, 7, 1.5);
                    tool.canny(gray, 60, 80);
                    tool.findContours2(gray, frame);
                    break;
                case Methods::BLUR_TEST: //тест блюра
                    tool.gaussianBlur(gray, 7, 1.5);
                    frame = gray;
                    break;
                case Methods::KENNY_TEST: //тест метода Кенни на блюре
                    tool.gaussianBlur(gray, 7, 1.5);
                    tool.canny(gray, 30, 60); //обводит резкие линии(детектор границ Кенни)
                    frame = gray;
                    break;
                case Methods::THRESHOLD_TEST: //тест порогового преобразования на блюре
                    tool.gaussianBlur(gray, 3, 0.0);
                    tool.threshold(gray);
                    frame = gray;
                    break;
                case Methods::ADAPTIVE_THRESHOLD_TEST: //тест адаптивного порогового преобразования на блюре
                    tool.gaussianBlur(gray, 3, 0.0);
                    tool.adaptiveThreshold(gray);
                    bitwise_not(gray, gray);
                    frame = gray;
                    break;
                default:break;
            }
            prof.point("OpenCV");

            packet.setImage(frame);
            prof.point("Compress");

            packet.send(&scli, &addr); //very fast operation ( < 1 ms)

            prof.end();
        }
        alive = false;
        signal(SIGINT, SIG_DFL);
        signal(SIGTERM, SIG_DFL);
    } catch(cv::Exception e) {
        throw e;
//        cerr << "err: " << e.err << endl;
//        cerr << "file: " << e.file << endl;
//        cerr << "func: " << e.func << endl;
//        cerr << "msg: " << e.msg << endl;
    }
    cout << "Exit main thread gracefully" << endl;
    return 0;
}

