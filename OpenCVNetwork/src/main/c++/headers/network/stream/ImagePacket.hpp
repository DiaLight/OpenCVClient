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
#include "StreamClient.hpp"

class ImagePacket {
    int bufSize;
    char *buf;
    std::vector<uchar> buff; //buffer for encoding
    std::vector<int> param;
    __uint64_t frameIndex;
public:
    ImagePacket();
    virtual ~ImagePacket();
    
    void setImage(cv::InputArray img);
    void send(StreamClient *cli, ServerAddr *addr);
private:

};

#endif /* IMAGEPACKET_H */

