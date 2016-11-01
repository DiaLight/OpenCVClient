//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_PROTOCOL_HPP
#define OPENCVCLIENT_PROTOCOL_HPP


#include <map>
#include "PacketType.hpp"
#include "InPacket.hpp"
#include "OutPacket.hpp"

using namespace std;

class Protocol {
    map<int, InPacketConstructor> inPackets;
    map<PacketType, int> outPackets;

public:

    void registerInPacket(int id, InPacketConstructor packetConstructor);

    void registerOutPacket(int id, PacketType &type);

    InPacket *newInstance(int id);

    int getId(OutPacket *packet);
};


#endif //OPENCVCLIENT_PROTOCOL_HPP
