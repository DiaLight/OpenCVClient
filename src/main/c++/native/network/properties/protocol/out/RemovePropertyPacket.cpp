//
// Created by dialight on 01.11.16.
//

#include "network/properties/protocol/out/RemovePropertyPacket.hpp"

PacketType RemovePropertyPacket::TYPE("RemovePropertyPacket");

RemovePropertyPacket::RemovePropertyPacket(const string &key) : key(key) {

}

void RemovePropertyPacket::write(TCPClient *client) {
    client->writeUTF(key);
}

PacketType RemovePropertyPacket::getType() {
    return TYPE;
}
