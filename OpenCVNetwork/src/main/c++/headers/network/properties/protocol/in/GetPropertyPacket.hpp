//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_GETPROPERTYPACKET_HPP
#define OPENCVCLIENT_GETPROPERTYPACKET_HPP


#include <network/properties/protocol/InPacket.hpp>

class GetPropertyPacket : public InPacket {

public:
    std::string key;

    GetPropertyPacket();

    void read(TCPSocketClient *client) override;

    PacketType getType() override;

    int getId() override;

    static InPacket *constructor() {
        return new GetPropertyPacket();
    }

    std::string toString() override;
};


#endif //OPENCVCLIENT_GETPROPERTYPACKET_HPP
