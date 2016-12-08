//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_ALLPROPERTIESPACKET_HPP
#define OPENCVCLIENT_ALLPROPERTIESPACKET_HPP


#include <network/properties/protocol/OutPacket.hpp>
#include <map>
#include <structures/Property.hpp>

class AllPropertiesPacket : public OutPacket {

    std::map<std::string, PropertyPointer> *props;
public:

    AllPropertiesPacket(std::map<std::string, PropertyPointer> *props);

    void write(TCPSocketClient *client) override;

    PacketType getType() override;

    int getId() override;

    std::string toString() override;
};


#endif //OPENCVCLIENT_ALLPROPERTIESPACKET_HPP
