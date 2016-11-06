//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_ALLPROPERTIESPACKET_HPP
#define OPENCVCLIENT_ALLPROPERTIESPACKET_HPP


#include <network/properties/protocol/OutPacket.hpp>
#include <map>
#include <network/properties/structures/Property.hpp>

using namespace std;

class AllPropertiesPacket : public OutPacket {

    map<string, PropertyPointer> *props;
public:

    AllPropertiesPacket(map<string, PropertyPointer> *props);

    void write(TCPSocketClient *client) override;

    PacketType getType() override;

    int getId() override;

    string toString() override;
};


#endif //OPENCVCLIENT_ALLPROPERTIESPACKET_HPP
