/*
 * File:   Main.cpp
 * Author: dialight
 *
 * Created on 13 октября 2016 г., 8:42
 */

#include <App.hpp>
#include <opencv2/opencv.hpp>
#include <csignal>
#include <utils/Profiler.hpp>
#include <network/stream/UDPSocketClient.hpp>
#include <network/stream/protocol/ImagePacket.hpp>
#include <network/stream/StreamClient.hpp>
#include <Properties.hpp>
#include <frame/source/FrameSource.hpp>
#include <frame/source/WebCamSrc.hpp>
#include <frame/source/ImageSrc.hpp>
#include <frame/source/RaspiCamSrc.hpp>
#include <utils/PropertiesLogger.hpp>
#include <utils/DiaUtils.hpp>
#include <utils/PointerGuard.hpp>
#include <IntelEdison.hpp>
#include <network/properties/PropertiesClient.hpp>
#include <frame/processor/ObjectDetect.hpp>
#include <frame/processor/Loop.hpp>
#include "frame/processor/FrameProcessor.hpp"

using namespace std;
using namespace cv;

const String keys = ""
        "{help h usage ? |               | print this message                                                                }"
        "{res resolution |               | capture resolution (Example: 640x480)                                             }"
        "{fps            | -1.0          | fixed fps for video capture                                                       }"
        "{i image        |               | Replace video stream with image                                                   }"
        "{c camera       |-1             | Set index of web camera inside OpenCV VideoCapture class. Must be > 0.            }"
        "{x xml          |               | Path to xml of the object detect classifier                                       }"
        "{flip           |false          | Flip image                                                                        }"
        //View settings
        "{l local        |false          | Create simple local gui                                                           }"
        "{r remote       |localhost:2016 | Video stream to remote server                                                     }"
        //Debug settings
        "{p profiler     |false          | Enable profiler messages to console                                               }"
        "{d debug        |-1             | Edison connection debug. Sends '1' symbol to Edison every N seconds. Must be > 0. }"
;
int main(int argc, const char* const argv[]) {
    app.init();
    CommandLineParser parser(argc, argv, keys);
    parser.about("OpenCVClient");

    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    //Capture settings
    auto resolution = parser.get<String>("resolution");
    auto fps = parser.get<int>("fps");
    auto imagePath = parser.get<String>("image");
    auto deviceIndex = parser.get<int>("camera");
    //Frame process settings
    auto xmlPath = parser.get<String>("xml");
    //View settings
    auto local = parser.get<bool>("local");
    auto remote = parser.get<String>("remote");
    //Debug settings
    auto profiler = parser.get<bool>("profiler");
    auto edisonDebug = parser.get<int>("debug");
    
    auto flip = parser.get<bool>("flip");
    

    if (!parser.check()) {
        parser.printErrors();
        return 0;
    }

//    if(showProperties) {
//        props.registerListener(&propertiesLogger);
//    }

    if(edisonDebug >= 0) {
        IntelEdison e;
        int i = 0;
        while(app.isAlive()) {
            e.transmit();
            cout << i << endl;
            usleep((__useconds_t) edisonDebug * 1000 * 1000);
        }
        return 0;
    }

    //get target address from command line
    ServerAddr addr(remote);

    try {
        PointerGuard<FrameSource> frameSrc;
        if (deviceIndex >= 0) {
            frameSrc.set(new WebCamSrc(deviceIndex));
        } else if(!imagePath.empty()) {
            frameSrc.set(new ImageSrc(imagePath));
        } else {
            frameSrc.set(new RaspiCamSrc());
        }
        if(!frameSrc->init()) {
            return -1;
        }

        if(!resolution.empty()) {
            cout << "Set resolution to " << resolution << endl;
            vector<string> spl = strSplit(resolution, 'x');
            frameSrc->setResolution(stoi(spl[0]), stoi(spl[1]));
        }
        if(fps > 0) {
            cout << "Set fps to " << fps << endl;
            frameSrc->setFps(fps);
        }

        //init tcp properties client bound to target address
        PropertiesClient propc(&addr);
        propc.runAsync();

        PointerGuard<FrameProcessor> frameProc;
        if(!xmlPath.empty()) {
            frameProc.set(new ObjectDetect(xmlPath));
        } else {
            frameProc.set(new Loop());
        }

        //init udp stream client bound to target address
        StreamClient scli;
        scli.bind();

        if(local) {
            // TODO: build properties in local window
//                createTrackbar( "Sigma", "Laplacian", &sigma, 15, 0 );
            namedWindow("image", 1);
        }
        Profiler prof(profiler);
        Mat frame;
        while (app.isAlive()) {
            prof.start();

            frameSrc->capture(frame);
            prof.point("Capture");
            if(flip) cv::flip(frame, frame, -1);

            frameProc->handle(frame);
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
    } catch(cv::Exception e) {
//        throw e;
        cerr << "err: " << e.err << endl;
        cerr << "file: " << e.file << endl;
        cerr << "func: " << e.func << endl;
        cerr << "msg: " << e.msg << endl;
    }
    app.close();
    cout << "Exit main thread gracefully" << endl;
    return 0;
}

