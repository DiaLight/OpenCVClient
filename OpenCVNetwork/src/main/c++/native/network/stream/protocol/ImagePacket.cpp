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

#include "network/stream/protocol/ImagePacket.hpp"

using namespace cv;
using namespace std;

int bufSize = 64 * 1024 - 20 - 8 - 1;
char *buf = new char[bufSize]();
std::vector<uchar> image;

std::vector<int> param = {
        cv::IMWRITE_JPEG_QUALITY,
        80 //default(95) 0-100
};

ImagePacket::ImagePacket(InputArray frame) {
    imencode(".jpg", frame, image, param);
    frameIndex = (uint64_t) time(0);
}

ImagePacket::~ImagePacket() {
//    delete buf;
}

void ImagePacket::send(UDPSocketClient *cli, ServerAddr *addr) {
    int size = (int) image.size();
    int left = (size + 4 + 8) % (bufSize - 8 - 1);
    int parts = (size + 4) / (bufSize - 8 - 1);
    if (left != 0) parts++;
    int dataPos = 0;
    for (int i = 0; i < parts; i++) {
        int bufPos = 0;
        ((long *) (buf + bufPos))[0] = __bswap_64(frameIndex);
        bufPos += 8;
        ((char *) (buf + bufPos))[0] = (char) i;
        bufPos += 1;
        if (i == 0) {
            ((int *) (buf + bufPos))[0] = __bswap_32((unsigned int) size);
            bufPos += 4;
        }
        int partSize = bufSize - bufPos;
        if (dataPos + partSize > size) partSize = size - dataPos;
        memcpy((void*) (buf + bufPos), (void*) (((char *) image.data()) + dataPos), (size_t) partSize);
        dataPos += partSize;
        bufPos += partSize;
        cli->send(buf, (size_t) bufPos, addr);
    }
}
