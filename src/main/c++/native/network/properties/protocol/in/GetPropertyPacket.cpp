//
// Created by dialight on 01.11.16.
//

#include "network/properties/protocol/in/GetPropertyPacket.hpp"

PacketType GetPropertyPacket::TYPE("GetPropertyPacket");

GetPropertyPacket::GetPropertyPacket() : InPacket() {}

void GetPropertyPacket::read(TCPClient *client) {
    key = client->readUTF();
}

PacketType GetPropertyPacket::getType() {
    return TYPE;
}
