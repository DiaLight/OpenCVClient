//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_PINGPACKET_HPP
#define OPENCVCLIENT_PINGPACKET_HPP


#include <network/properties/protocol/InPacket.hpp>

class PingPacket : public InPacket {

public:
    __uint64_t time;

    PingPacket();

    void read(TCPSocketClient *client) override;

    PacketType getType() override;

    int getId() override;

    static InPacket *constructor() {
        return new PingPacket();
    }

    string toString() override;
};


#endif //OPENCVCLIENT_PINGPACKET_HPP
