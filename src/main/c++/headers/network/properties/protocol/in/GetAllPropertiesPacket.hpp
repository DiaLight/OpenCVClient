//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_ALLPROPERTIESREQUESTPACKET_HPP
#define OPENCVCLIENT_ALLPROPERTIESREQUESTPACKET_HPP


#include <network/properties/protocol/InPacket.hpp>

class GetAllPropertiesPacket : public InPacket {

public:
    static PacketType TYPE;

    GetAllPropertiesPacket();

    void read(TCPClient *client) override;

    PacketType getType() override;

    static InPacket *constructor() {
        return new GetAllPropertiesPacket();
    }

};


#endif //OPENCVCLIENT_ALLPROPERTIESREQUESTPACKET_HPP
