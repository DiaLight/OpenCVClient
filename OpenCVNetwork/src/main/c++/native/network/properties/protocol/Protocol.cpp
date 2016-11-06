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

InPacket *Protocol::newInstance(int id) {
    auto it = inPackets.find(id);
    if (it == inPackets.end()) {
        std::stringstream ss;
        ss << "Unknown packet id: " << id;
        throw IOException(ss.str());
    }
    return it->second();
}
