//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_PROPERTYADDPACKET_HPP
#define OPENCVCLIENT_PROPERTYADDPACKET_HPP


#include <network/properties/protocol/OutPacket.hpp>
#include <structures/Property.hpp>

class AddPropertyPacket : public OutPacket {

    std::string key;
    PropertyPointer value;
public:

    AddPropertyPacket(const std::string &key, PropertyPointer value);

    void write(TCPSocketClient *client) override;

    PacketType getType() override;

    int getId() override;

    std::string toString() override;
};


#endif //OPENCVCLIENT_PROPERTYADDPACKET_HPP
