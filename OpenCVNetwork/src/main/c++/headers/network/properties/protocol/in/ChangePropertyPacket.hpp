//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_CHANGEPROPERTYPACKET_HPP
#define OPENCVCLIENT_CHANGEPROPERTYPACKET_HPP


#include <network/properties/protocol/InPacket.hpp>
#include <network/properties/structures/Property.hpp>

class ChangePropertyPacket : public InPacket {

public:
    string key;
    Property *value;

    ChangePropertyPacket();

    virtual ~ChangePropertyPacket();

    void read(TCPSocketClient *client) override;

    PacketType getType() override;

    int getId() override;

    static InPacket *constructor() {
        return new ChangePropertyPacket();
    }

    string toString() override;
};


#endif //OPENCVCLIENT_CHANGEPROPERTYPACKET_HPP
