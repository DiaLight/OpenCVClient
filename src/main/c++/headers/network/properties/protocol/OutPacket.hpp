//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_OUTPACKET_HPP
#define OPENCVCLIENT_OUTPACKET_HPP

#include <network/properties/TCPClient.hpp>
#include "Packet.hpp"

class OutPacket : public Packet {

public:
    OutPacket();

    virtual void write(TCPClient *client) = 0;

};


#endif //OPENCVCLIENT_OUTPACKET_HPP
