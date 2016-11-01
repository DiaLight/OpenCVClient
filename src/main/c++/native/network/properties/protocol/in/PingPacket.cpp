//
// Created by dialight on 01.11.16.
//

#include "network/properties/protocol/in/PingPacket.hpp"

PacketType PingPacket::TYPE("PingPacket");

PingPacket::PingPacket() : InPacket() {}

void PingPacket::read(TCPClient *client) {
    time = client->readLong();
}

PacketType PingPacket::getType() {
    return TYPE;
}
