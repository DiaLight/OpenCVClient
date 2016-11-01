//
// Created by dialight on 31.10.16.
//

#include <network/exceptions/IOException.hpp>
#include "network/properties/protocol/Protocol.hpp"
#include <sstream>
#include <iostream>

void Protocol::registerInPacket(int id, InPacketConstructor packetConstructor) {
    inPackets.insert(pair<int, InPacketConstructor>(id, packetConstructor));
}

void Protocol::registerOutPacket(int id, PacketType &type) {
    outPackets.insert(pair<PacketType, int> (type, id));
}

InPacket *Protocol::newInstance(int id) {
    auto it = inPackets.find(id);
    if (it == inPackets.end()) {
        std::stringstream ss;
        ss << "Unknown packet id: " << id;
        throw IOException(ss.str());
    }
    return it->second();
}

int Protocol::getId(OutPacket *packet) {
    auto it = outPackets.find(packet->getType());
    if (it == outPackets.end()) {
        std::stringstream ss;
        ss << "Unregistered packet type";
        delete packet;
        throw RuntimeException(ss.str());
    }
    return it->second;
}
