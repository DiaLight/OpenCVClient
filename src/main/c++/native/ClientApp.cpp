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
#include <network/stream/StreamClient.hpp>
#include <utils/CmdParser.hpp>
#include <Properties.hpp>
#include "utils/VideoSource.hpp"
#include "utils/FrameProcessor.hpp"

using namespace std;
using namespace cv;

void signalHandler(int signum) {
    alive = false;
    cond.notifyAll();
    cout << "Terminated with signal " << signum << " " << strsignal(signum) << endl;
}

//static void help() {
//    cout <<
//         "\nThis program ...\n"
//                 "It captures from the camera of your choice: 0, 1, ... default 0\n"
//                 "Call:\n"
//                 "./? ??\n" << endl;
//}

int main(int argc, const char* const argv[]) {
    //TODO: Replace parser
//    cv::CommandLineParser parser(argc, argv, "{help h | | }{ c | 0 | }{ p | | }");
//    if (parser.has("help")) {
//        help();
//        return 0;
//    }
//    if(parser.get<string>("c").size() == 1 && isdigit(parser.get<string>("c")[0])) {
//        cap.open(parser.get<int>("c"));
//    } else {
//        cap.open(parser.get<string>("c"));
//    }
//    if(cap.isOpened()) {
//        cout << "Video " << parser.get<string>("c") <<
//             ": width=" << cap.get(CAP_PROP_FRAME_WIDTH) <<
//             ", height=" << cap.get(CAP_PROP_FRAME_HEIGHT) <<
//             ", nframes=" << cap.get(CAP_PROP_FRAME_COUNT) << endl;
//    }
//    if(parser.has("p")) {
//        int pos = parser.get<int>("p");
//        if (!parser.check()) {
//            parser.printErrors();
//            return -1;
//        }
//        cout << "seeking to frame #" << pos << endl;
//        cap.set(CAP_PROP_POS_FRAMES, pos);
//    }
//    if(!cap.isOpened()) {
//        cout << "Could not initialize capturing..." << endl;
//        return -1;
//    }

    cli::Parser parser(argc, argv);

    //Capture settings
    parser.set_optional<string>("i", "image", "", "Replace video stream with image.");
    parser.set_optional<int>("c", "camera", -1, "Set index of web camera inside OpenCV VideoCapture class. Must be > 0.");
    //Frame process settings
    parser.set_optional<string>("x", "xml", "", "Path to object detect xml.");
    //View settings
    parser.set_optional<bool>("l", "local", false, "Create simple local gui.");
    parser.set_optional<string>("r", "remote", "localhost:2016", "Video stream to remote server.");
    //Debug settings
    parser.set_optional<bool>("p", "profiler", false, "Enable profiler messages to console.");

    parser.run_and_exit_if_error();

    //Capture settings
    auto imagePath = parser.get<string>("i");
    auto deviceIndex = parser.get<int>("c");
    //Frame process settings
    auto xmlPath = parser.get<string>("x");
    //View settings
    auto remote = parser.get<string>("r");
    auto local = parser.get<bool>("l");
    //Debug settings
    auto profiler = parser.get<bool>("p");

    //get target address from command line
    ServerAddr addr(remote);

    try {
        // TODO: rewrite to inherit model
        VideoSource videoSrc; // destructor will release video source
        if (deviceIndex >= 0) {
            if(!videoSrc.setOpenCVBased(deviceIndex)) return -1;
        } else if(!imagePath.empty()) {
            if(!videoSrc.setImageBased(imagePath)) return -1;
        } else {
            if(!videoSrc.setRaspicamBased()) return -1;
        }

        //init tcp properties client bound to target address
        PropertiesClient propc(&addr);
        propc.runAsync();

        FrameProcessor frameProc;
        if(!xmlPath.empty()) {
            if(!frameProc.setClassifierBased(xmlPath)) return -1;
        } else {
            frameProc.setManualHandler();
        }

        //init udp stream client bound to target address
        StreamClient scli;
        scli.bind();

        //setup signal inHandler for caught interrupts
        signal(SIGINT, signalHandler);
        signal(SIGTERM, signalHandler);

        if(local) {
            // TODO: build properties in local window
//                createTrackbar( "Sigma", "Laplacian", &sigma, 15, 0 );
            namedWindow("image", 1);
        }
        Profiler prof(profiler);
        Mat frame;
        while (alive) {
            prof.start();

            videoSrc.capture(frame);
            prof.point("Capture");

            frameProc.handle(frame);
            prof.point("OpenCV");

            ImagePacket packet(frame); //network structure
            prof.point("Compress");

            scli.sendPacket(&packet, &addr); //very fast operation ( < 1 ms)

            if(local) {
                imshow("image", frame);
                waitKey(1);
            }

            int del = props.getInt("loop.delayms", 0);
            if(del > 0) {
                usleep((__useconds_t) del * 1000);
            }

            prof.end();
        }
        alive = false;
        signal(SIGINT, SIG_DFL);
        signal(SIGTERM, SIG_DFL);
    } catch(cv::Exception e) {
//        throw e;
        cerr << "err: " << e.err << endl;
        cerr << "file: " << e.file << endl;
        cerr << "func: " << e.func << endl;
        cerr << "msg: " << e.msg << endl;
    }
    cout << "Exit main thread gracefully" << endl;
    return 0;
}

