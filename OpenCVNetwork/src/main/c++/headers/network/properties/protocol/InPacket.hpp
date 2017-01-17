//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_INPACKET_HPP
#define OPENCVCLIENT_INPACKET_HPP

#include <network/properties/TCPSocketClient.hpp>
#include "Packet.hpp"

class InPacket : public Packet {

public:
    virtual ~InPacket() {}

    virtual void read(TCPSocketClient *client) = 0;

};

typedef InPacket *(*InPacketConstructor)();

#endif //OPENCVCLIENT_INPACKET_HPP
