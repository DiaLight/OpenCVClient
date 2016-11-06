/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerAddr.hpp
 * Author: dialight
 *
 * Created on 26 октября 2016 г., 16:39
 */

#ifndef SERVERADDR_HPP
#define SERVERADDR_HPP

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

class ServerAddr {
public:
    string host;
    int port;
    
    struct sockaddr_in srvAddr;
    socklen_t srvAddrLen;
    
    ServerAddr(int argc, char **argv);
    virtual ~ServerAddr();
    ServerAddr(const ServerAddr&) = delete; //deleted copy constructor
    ServerAddr& operator=(const ServerAddr &) = delete; //deleted copy assignment operato

    string toString();

};

#endif /* SERVERADDR_HPP */

