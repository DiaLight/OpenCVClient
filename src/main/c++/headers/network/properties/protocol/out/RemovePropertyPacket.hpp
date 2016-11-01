//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_REMOVEPROPERTYPACKET_HPP
#define OPENCVCLIENT_REMOVEPROPERTYPACKET_HPP


#include <network/properties/protocol/OutPacket.hpp>

class RemovePropertyPacket : public OutPacket {

    string key;
public:
    static PacketType TYPE;

    RemovePropertyPacket(const string &key);

    void write(TCPClient *client) override;

    PacketType getType() override;

};

#endif //OPENCVCLIENT_REMOVEPROPERTYPACKET_HPP
