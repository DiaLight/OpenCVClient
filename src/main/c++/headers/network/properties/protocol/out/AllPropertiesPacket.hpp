//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_ALLPROPERTIESPACKET_HPP
#define OPENCVCLIENT_ALLPROPERTIESPACKET_HPP


#include <network/properties/protocol/OutPacket.hpp>
#include <map>

using namespace std;

class AllPropertiesPacket : public OutPacket {

    map<string, int> *props;
public:
    static PacketType TYPE;

    AllPropertiesPacket(map<string, int> *props);

    void write(TCPClient *client) override;

    PacketType getType() override;

};


#endif //OPENCVCLIENT_ALLPROPERTIESPACKET_HPP
