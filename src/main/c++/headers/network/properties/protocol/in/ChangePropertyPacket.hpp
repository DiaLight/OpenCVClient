//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_CHANGEPROPERTYPACKET_HPP
#define OPENCVCLIENT_CHANGEPROPERTYPACKET_HPP


#include <network/properties/protocol/InPacket.hpp>

class ChangePropertyPacket : public InPacket {

public:
    string key;
    int value;
    static PacketType TYPE;

    ChangePropertyPacket();

    void read(TCPClient *client) override;

    PacketType getType() override;

    static InPacket *constructor() {
        return new ChangePropertyPacket();
    }

};


#endif //OPENCVCLIENT_CHANGEPROPERTYPACKET_HPP
