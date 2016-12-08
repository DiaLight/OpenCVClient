//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_PONGPACKET_HPP
#define OPENCVCLIENT_PONGPACKET_HPP


#include <network/properties/protocol/OutPacket.hpp>

class PongPacket : public OutPacket {

    __uint64_t time;
public:

    PongPacket(__uint64_t time);

    void write(TCPSocketClient *client) override;

    PacketType getType() override;

    int getId() override;

    std::string toString() override;
};

#endif //OPENCVCLIENT_PONGPACKET_HPP
