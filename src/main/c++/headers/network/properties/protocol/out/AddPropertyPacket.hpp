//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_PROPERTYADDPACKET_HPP
#define OPENCVCLIENT_PROPERTYADDPACKET_HPP


#include <network/properties/protocol/OutPacket.hpp>
#include <network/properties/structures/Property.hpp>

class AddPropertyPacket : public OutPacket {

    string key;
    Property *value;
public:

    AddPropertyPacket(const string &key, Property *value);

    void write(TCPSocketClient *client) override;

    PacketType getType() override;

    int getId() override;

    string toString() override;
};


#endif //OPENCVCLIENT_PROPERTYADDPACKET_HPP
