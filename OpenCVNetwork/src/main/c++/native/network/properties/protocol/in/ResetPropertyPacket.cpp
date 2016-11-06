//
// Created by dialight on 01.11.16.
//

#include "network/properties/protocol/in/ResetPropertyPacket.hpp"

ResetPropertyPacket::ResetPropertyPacket() : InPacket() {}

void ResetPropertyPacket::read(TCPSocketClient *client) {
    key = client->readUTF();
}

PacketType ResetPropertyPacket::getType() {
    return PacketType::RESET_PROPERTY;
}

int ResetPropertyPacket::getId() {
    return 0x03;
}

string ResetPropertyPacket::toString() {
    stringstream ss;
    ss << "ResetPropertyPacket{key=" << key << "}";
    return ss.str();
}
