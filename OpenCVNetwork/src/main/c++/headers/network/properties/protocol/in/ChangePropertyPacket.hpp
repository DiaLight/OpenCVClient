//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_CHANGEPROPERTYPACKET_HPP
#define OPENCVCLIENT_CHANGEPROPERTYPACKET_HPP


#include <network/properties/protocol/InPacket.hpp>
#include <structures/Property.hpp>

class ChangePropertyPacket : public InPacket {

public:
    std::string key;
    PropertyPointer value;

    ChangePropertyPacket();

    virtual ~ChangePropertyPacket();

    void read(TCPSocketClient *client) override;

    PacketType getType() override;

    int getId() override;

    static InPacket *constructor() {
        return new ChangePropertyPacket();
    }

    std::string toString() override;
};


#endif //OPENCVCLIENT_CHANGEPROPERTYPACKET_HPP
