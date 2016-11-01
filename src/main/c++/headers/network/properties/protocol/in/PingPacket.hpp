//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_PINGPACKET_HPP
#define OPENCVCLIENT_PINGPACKET_HPP


#include <network/properties/protocol/InPacket.hpp>

class PingPacket : public InPacket {

public:
    __uint64_t time;
    static PacketType TYPE;

    PingPacket();

    void read(TCPClient *client) override;

    PacketType getType() override;

    static InPacket *constructor() {
        return new PingPacket();
    }

};


#endif //OPENCVCLIENT_PINGPACKET_HPP
