//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_OUTPACKET_HPP
#define OPENCVCLIENT_OUTPACKET_HPP

#include <network/properties/TCPSocketClient.hpp>
#include "Packet.hpp"

class OutPacket : public Packet {

public:

    virtual void write(TCPSocketClient *client) = 0;

};


#endif //OPENCVCLIENT_OUTPACKET_HPP
