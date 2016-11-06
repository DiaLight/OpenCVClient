//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_REMOVEPROPERTYPACKET_HPP
#define OPENCVCLIENT_REMOVEPROPERTYPACKET_HPP


#include <network/properties/protocol/OutPacket.hpp>

class RemovePropertyPacket : public OutPacket {

    string key;
public:

    RemovePropertyPacket(const string &key);

    void write(TCPSocketClient *client) override;

    PacketType getType() override;

    int getId() override;

    string toString() override;

};

#endif //OPENCVCLIENT_REMOVEPROPERTYPACKET_HPP
