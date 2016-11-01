//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_PROPERTYADDPACKET_HPP
#define OPENCVCLIENT_PROPERTYADDPACKET_HPP


#include <network/properties/protocol/OutPacket.hpp>

class AddPropertyPacket : public OutPacket {

    string key;
    int value;
public:
    static PacketType TYPE;

    AddPropertyPacket(const string &key, int value);

    void write(TCPClient *client) override;

    PacketType getType() override;

};


#endif //OPENCVCLIENT_PROPERTYADDPACKET_HPP
