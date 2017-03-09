/*
 * File:   Main.cpp
 * Author: dialight
 *
 * Created on 13 октября 2016 г., 8:42
 */

#include <App.hpp>
#include <opencv2/opencv.hpp>
#include <utils/Profiler.hpp>
#include <network/stream/UDPSocketClient.hpp>
#include <network/stream/protocol/ImagePacket.hpp>
#include <network/stream/StreamClient.hpp>
#include <Properties.hpp>
#include <frame/source/FrameSource.hpp>
#include <frame/source/WebCamSrc.hpp>
#include <frame/source/ImageSrc.hpp>
#include <frame/source/RaspiCamSrc.hpp>
#include <utils/DiaUtils.hpp>
#include <utils/PointerGuard.hpp>
#include <IntelEdison.hpp>
#include <network/properties/PropertiesClient.hpp>
#include <frame/processor/ObjectDetect.hpp>
#include <frame/processor/Loop.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char* const argv[]) {
    app.init();
    SimpleConfig cfg(argc, (const char **) argv);

    if(!cfg.read()) return 0;
//    if(showProperties) {
//        props.registerListener(&propertiesLogger);
//    }

    if(cfg.edisonDebug >= 0) {
        IntelEdison e;
        int i = 0;
        while(app.isAlive()) {
            e.transmit();
            cout << i << endl;
            usleep((__useconds_t) cfg.edisonDebug * 1000 * 1000);
        }
        return 0;
    }

    //get target address from command line
    ServerAddr addr(cfg.remote);

    try {
        PointerGuard<FrameSource> frameSrc;
        if (cfg.deviceIndex >= 0) {
            frameSrc.set(new WebCamSrc(cfg.deviceIndex));
        } else if(!cfg.imagePath.empty()) {
            frameSrc.set(new ImageSrc(cfg.imagePath));
        } else {
            frameSrc.set(new RaspiCamSrc());
        }
        if(!frameSrc->init()) {
            return -1;
        }

        if(!cfg.resolution.empty()) {
            cout << "Set resolution to " << cfg.resolution << endl;
            vector<string> spl = strSplit(cfg.resolution, 'x');
            frameSrc->setResolution(stoi(spl[0]), stoi(spl[1]));
        }
        if(cfg.fps > 0) {
            cout << "Set fps to " << cfg.fps << endl;
            frameSrc->setFps(cfg.fps);
        }

        //init tcp properties client bound to target address
        PropertiesClient propc(&addr);
        propc.runAsync();

        PointerGuard<FrameProcessor> frameProc;
        if(!cfg.xmlPath.empty()) {
            frameProc.set(new ObjectDetect(cfg.xmlPath));
        } else {
            frameProc.set(new Loop(&cfg));
        }

        //init udp stream client bound to target address
        StreamClient scli;
        scli.bind();

        if(cfg.local) {
            // TODO: build properties in local window
//                createTrackbar( "Sigma", "Laplacian", &sigma, 15, 0 );
            namedWindow("image", 1);
        }
        Profiler prof(cfg.profiler);
        Mat frame;
        frameSrc->capture(frame);
        frameProc->init(frame);
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

            if(cfg.local) {
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

