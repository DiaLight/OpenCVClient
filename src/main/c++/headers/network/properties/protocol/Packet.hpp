//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_PACKET_HPP
#define OPENCVCLIENT_PACKET_HPP

#include "PacketType.hpp"
#include <string>
#include <sstream>

using namespace std;

class Packet {

public:
    virtual PacketType getType() = 0;
    virtual int getId() = 0;
    virtual string toString() = 0;

};


#endif //OPENCVCLIENT_PACKET_HPP
