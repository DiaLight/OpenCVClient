//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_ALLPROPERTIESREQUESTPACKET_HPP
#define OPENCVCLIENT_ALLPROPERTIESREQUESTPACKET_HPP


#include <network/properties/protocol/InPacket.hpp>
#include <network/properties/protocol/PacketType.hpp>

class GetAllPropertiesPacket : public InPacket {

public:

    GetAllPropertiesPacket();

    void read(TCPSocketClient *client) override;

    PacketType getType() override;

    int getId() override;

    static InPacket *constructor() {
        return new GetAllPropertiesPacket();
    }

    string toString() override;
};


#endif //OPENCVCLIENT_ALLPROPERTIESREQUESTPACKET_HPP
