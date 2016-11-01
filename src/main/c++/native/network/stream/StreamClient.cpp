/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Client.cpp
 * Author: dialight
 * 
 * Created on 13 октября 2016 г., 10:51
 */

#include "network/stream/StreamClient.hpp"

using namespace std;

StreamClient::StreamClient() {
    cliFD = socket(AF_INET, SOCK_DGRAM, 0);
    if (cliFD < 0) {
        cerr << "ERROR opening socket. " << strerror(errno) << endl;
        exit(1);
    }
    
}

StreamClient::~StreamClient() {
    close(cliFD);
}

void StreamClient::bind() {
    struct sockaddr_in cliAddr;
    socklen_t cliAddrLen = sizeof (cliAddr);
    bzero((char *) &cliAddr, cliAddrLen);
    cliAddr.sin_family = AF_INET;
    cliAddr.sin_addr.s_addr = INADDR_ANY;
    cliAddr.sin_port = htons(0);
    if (::bind(cliFD, (struct sockaddr *) &cliAddr, cliAddrLen) < 0) {
        cerr << "ERROR on binding: " << strerror(errno) << endl;
        exit(1);
    }
    cout << "client binded on "
            << inet_ntoa(cliAddr.sin_addr) <<
            ":" << ntohs(cliAddr.sin_port) << endl;
}

ssize_t StreamClient::recv(void *buf, size_t size, ServerAddr *addr) {
    ssize_t n = recvfrom(cliFD, buf, size, 0, (struct sockaddr *) &addr->srvAddr, &addr->srvAddrLen);
    if (n < 0) {
        cerr << "ERROR on receiving. " << strerror(errno) << endl;
        exit(1);
    }
    return n;
}

void StreamClient::send(void *buf, size_t size, ServerAddr *addr) {
    if (sendto(cliFD, buf, size, 0, (struct sockaddr *) &addr->srvAddr, addr->srvAddrLen) < 0) {
        cerr << "ERROR on sending. " << strerror(errno) << endl;
        exit(1);
    }
}
