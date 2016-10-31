/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Client.h
 * Author: dialight
 *
 * Created on 13 октября 2016 г., 10:51
 */

#ifndef STREAMCLIENT_H
#define STREAMCLIENT_H

#include <string>
#include <iostream>
#include <cerrno>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "network/ServerAddr.hpp"

class StreamClient {
    int cliFD;
public:
    StreamClient();
    
    StreamClient(const StreamClient&) = delete; //deleted copy constructor
    StreamClient& operator=(const StreamClient &) = delete; //deleted copy assignment operato
    
    virtual ~StreamClient();
    
    void bind();
    int recv(void *buf, size_t size, ServerAddr *addr);
    void send(void *buf, size_t size, ServerAddr *addr);
};

#endif /* CLIENT_H */

