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

#include <AppState.hpp>
#include <opencv2/opencv.hpp>
#include <csignal>
#include <Profiler.hpp>
#include <network/stream/UDPSocketClient.hpp>
#include <network/stream/protocol/ImagePacket.hpp>
#include <opencv/Loop.hpp>
#include <network/stream/StreamClient.hpp>
#include <utils/CmdParser.hpp>

using namespace std;
using namespace cv;

void signalHandler(int signum) {
    alive = false;
    cond.notifyAll();
    cout << "Terminated with signal " << signum << " " << strsignal(signum) << endl;
}

int main(int argc, char** argv) {
    cli::Parser parser(argc, argv);

    parser.set_optional<string>("i", "image", "", "Replace video stream with image.");
    parser.set_optional<string>("r", "remote", "localhost:2016", "Video stream to remote server.");
    parser.set_optional<string>("x", "xml", "", "Path to object detect xml.");
    parser.set_optional<bool>("l", "local", false, "Create simple local gui.");

    parser.run_and_exit_if_error();

    auto imagePath = parser.get<string>("i");
    auto remote = parser.get<string>("r");
    auto xmlPath = parser.get<string>("x");
    auto local = parser.get<bool>("l");

    bool isVideo = imagePath.empty();
    bool isXml = !xmlPath.empty();

    //get target address from command line inArgs
    ServerAddr addr(remote);

    VideoCapture *cap = nullptr;
    Mat image;
    if (isVideo) {
        //init video source
        cap = new VideoCapture(0); // default camera
        if (!cap->isOpened()) {
            cout << "No video capture device" << endl;
            alive = false;
            return -1;
        }
    } else {
        image = imread(imagePath, 1);
        if(image.empty()) {
            printf("Cannot read image file: %s\n", imagePath.c_str());
            alive = false;
            return -1;
        }
    }

    try {

        //init tcp properties client bound to target address
        PropertiesClient propc(&addr);
        propc.runAsync();

        //init udp stream client bound to target address
        StreamClient scli;
        scli.bind();

        //setup signal inHandler for caught interrupts
        signal(SIGINT, signalHandler);
        signal(SIGTERM, signalHandler);

        Tool tool(&propc);
        ObjectDetect *detect = nullptr;
        if(isXml) {
            detect = new ObjectDetect(&propc);
        }
        if(local) {
            namedWindow("image", 1);
        }
        Loop cvMain(&propc, &tool);
        Profiler prof(false);
        Mat frame;
        while (alive) {
            prof.start();

            if (isVideo) {
                *cap >> frame;
            } else {
                frame = image.clone();
            }
            prof.point("Capture");

            if(isXml) {
                Mat gray;
                cvtColor(frame, gray, COLOR_BGR2GRAY);
                tool.gaussianBlur(gray, 7, 1.5);
                detect->detectMultiScale(gray, frame);
            } else {
                frame = cvMain.loop(frame);
            }
            prof.point("OpenCV");

            ImagePacket packet(frame); //network structure
            prof.point("Compress");

            scli.sendPacket(&packet, &addr); //very fast operation ( < 1 ms)

            if(local) {
                imshow("image", frame);
                waitKey(1);
            }

            int del = propc.getInt("loop.delayms", 300);
            if(del > 0) {
                usleep((__useconds_t) del * 1000);
            }

            prof.end();
        }
        if (isVideo) {
            delete cap;
        }
        if(isXml) {
            delete detect;
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

