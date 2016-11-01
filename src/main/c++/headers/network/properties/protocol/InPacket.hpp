//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_INPACKET_HPP
#define OPENCVCLIENT_INPACKET_HPP

#include <network/properties/TCPClient.hpp>
#include "Packet.hpp"

class InPacket : public Packet {

public:

    InPacket();

    virtual void read(TCPClient *client) = 0;

};

typedef InPacket *(*InPacketConstructor)();

#endif //OPENCVCLIENT_INPACKET_HPP
