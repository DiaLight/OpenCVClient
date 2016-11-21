/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ImagePacket.h
 * Author: DiaLight
 *
 * Created on 24 октября 2016 г., 13:10
 */

#ifndef IMAGEPACKET_H
#define IMAGEPACKET_H

#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <ctime>
#include "network/ServerAddr.hpp"
#include "network/stream/UDPSocketClient.hpp"

class ImagePacket {
    uint64_t frameIndex;
public:
    ImagePacket(cv::InputArray frame);
    virtual ~ImagePacket();

    void send(UDPSocketClient *cli, ServerAddr *addr);


private:

};

#endif /* IMAGEPACKET_H */

