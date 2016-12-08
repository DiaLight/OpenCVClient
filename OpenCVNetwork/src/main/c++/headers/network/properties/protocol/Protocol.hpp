//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_PROTOCOL_HPP
#define OPENCVCLIENT_PROTOCOL_HPP


#include <map>
#include "InPacket.hpp"
#include "OutPacket.hpp"

class Protocol {
    std::map<int, InPacketConstructor> inPackets;

public:

    void registerInPacket(int id, InPacketConstructor packetConstructor);

    InPacket *newInstance(int id);

};


#endif //OPENCVCLIENT_PROTOCOL_HPP
