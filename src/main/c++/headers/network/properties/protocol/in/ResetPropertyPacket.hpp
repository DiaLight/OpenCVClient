//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_RESETPROPERTYPACKET_HPP
#define OPENCVCLIENT_RESETPROPERTYPACKET_HPP


#include <network/properties/protocol/InPacket.hpp>

class ResetPropertyPacket : public InPacket {

public:
    string key;
    static PacketType TYPE;

    ResetPropertyPacket();

    void read(TCPClient *client) override;

    PacketType getType() override;

    static InPacket *constructor() {
        return new ResetPropertyPacket();
    }

};


#endif //OPENCVCLIENT_RESETPROPERTYPACKET_HPP
