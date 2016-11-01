//
// Created by dialight on 01.11.16.
//

#include "network/properties/protocol/in/ResetPropertyPacket.hpp"

PacketType ResetPropertyPacket::TYPE("ResetPropertyPacket");

ResetPropertyPacket::ResetPropertyPacket() : InPacket() {}

void ResetPropertyPacket::read(TCPClient *client) {
    key = client->readUTF();
}

PacketType ResetPropertyPacket::getType() {
    return TYPE;
}
