//
// Created by dialight on 31.10.16.
//
#include "network/ServerAddr.hpp"
#include <iostream>
#include <sstream>
#include <netdb.h>
#include <cstring>
#include <utils/DiaUtils.hpp>

using namespace std;

ServerAddr::ServerAddr(string addr) {
    port = (uint16_t) -1;

    auto cut = strCut(addr, ':');

    if (!cut.second.empty()) {
        host = cut.first;
        int port = stoi(cut.second);
        if (port >= 0 and port < 65536) {
            this->port = (uint16_t) port;
            struct hostent *server = gethostbyname(host.c_str());
            if (server == NULL) {
                cerr << "ERROR, no such host. " << strerror(errno) << endl;
                exit(1);
            }
            srvAddrLen = sizeof (srvAddr);
            bzero((char *) &srvAddr, srvAddrLen);
            srvAddr.sin_family = AF_INET;
            bcopy(server->h_addr, (char *) &srvAddr.sin_addr.s_addr, (size_t) server->h_length);
            srvAddr.sin_port = htons(this->port);
        } else {
            cerr << "ERROR, Port must be between 0 and 65536" << endl;
            exit(1);
        }
    } else {
        cerr << "ERROR, bad host:port format" << endl;
        exit(1);
    }
}

ServerAddr::~ServerAddr() {

}

string ServerAddr::toString() {
    stringstream ss;
    ss << host << ":" << port;
    return ss.str();
}
