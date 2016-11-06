//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_RESETPROPERTYPACKET_HPP
#define OPENCVCLIENT_RESETPROPERTYPACKET_HPP


#include <network/properties/protocol/InPacket.hpp>

class ResetPropertyPacket : public InPacket {

public:
    string key;

    ResetPropertyPacket();

    void read(TCPSocketClient *client) override;

    PacketType getType() override;

    int getId() override;

    static InPacket *constructor() {
        return new ResetPropertyPacket();
    }

    string toString() override;
};


#endif //OPENCVCLIENT_RESETPROPERTYPACKET_HPP
