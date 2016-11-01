//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_GETPROPERTYPACKET_HPP
#define OPENCVCLIENT_GETPROPERTYPACKET_HPP


#include <network/properties/protocol/InPacket.hpp>

class GetPropertyPacket : public InPacket {

public:
    string key;
    static PacketType TYPE;

    GetPropertyPacket();

    void read(TCPClient *client) override;

    PacketType getType() override;

    static InPacket *constructor() {
        return new GetPropertyPacket();
    }

};


#endif //OPENCVCLIENT_GETPROPERTYPACKET_HPP
