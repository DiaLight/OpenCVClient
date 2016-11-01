//
// Created by dialight on 31.10.16.
//

#include "network/properties/protocol/out/AddPropertyPacket.hpp"

PacketType AddPropertyPacket::TYPE("AddPropertyPacket");

AddPropertyPacket::AddPropertyPacket(const string &key, int value) : key(key), value(value) {
}

void AddPropertyPacket::write(TCPClient *client) {
    client->writeUTF(key);
    client->writeInt(value);
}

PacketType AddPropertyPacket::getType() {
    return TYPE;
}
