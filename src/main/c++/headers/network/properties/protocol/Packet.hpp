//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_PACKET_HPP
#define OPENCVCLIENT_PACKET_HPP


#include "PacketType.hpp"

class Packet {

public:
    virtual PacketType getType() = 0;

};


#endif //OPENCVCLIENT_PACKET_HPP
