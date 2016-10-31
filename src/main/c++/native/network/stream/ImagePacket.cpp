/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ImagePacket.cpp
 * Author: DiaLight
 * 
 * Created on 24 октября 2016 г., 13:11
 */

#include "network/stream/ImagePacket.hpp"

using namespace cv;
using namespace std;

ImagePacket::ImagePacket() : param(2) {
    bufSize = 64 * 1024 - 20 - 8 - 1;
    buf = new char[bufSize]();
    param[0] = cv::IMWRITE_JPEG_QUALITY;
    param[1] = 80; //default(95) 0-100
}

ImagePacket::~ImagePacket() {
    delete buf;
}

void ImagePacket::setImage(InputArray img) {
    imencode(".jpg", img, buff, param);
    frameIndex = time(0);
}

void ImagePacket::send(StreamClient *cli, ServerAddr *addr) {
    int size = buff.size();
    int left = (size + 4 + 8) % (bufSize - 8 - 1);
    int parts = (size + 4) / (bufSize - 8 - 1);
    if (left != 0) parts++;
    int dataPos = 0;
    for (int i = 0; i < parts; i++) {
        int bufPos = 0;
        ((long *) (buf + bufPos))[0] = __bswap_64(frameIndex);
        bufPos += 8;
        ((char *) (buf + bufPos))[0] = i;
        bufPos += 1;
        if (i == 0) {
            ((int *) (buf + bufPos))[0] = __bswap_32(size);
            bufPos += 4;
        }
        int partSize = bufSize - bufPos;
        if (dataPos + partSize > size) partSize = size - dataPos;
        memcpy((void*) (buf + bufPos), (void*) (((char *) buff.data()) + dataPos), partSize);
        dataPos += partSize;
        bufPos += partSize;
        cli->send(buf, bufPos, addr);
    }
}
