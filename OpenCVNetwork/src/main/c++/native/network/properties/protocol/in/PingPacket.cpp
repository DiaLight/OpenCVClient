//
// Created by dialight on 01.11.16.
//

#include "network/properties/protocol/in/PingPacket.hpp"

using namespace std;

PingPacket::PingPacket() : InPacket() {}

void PingPacket::read(TCPSocketClient *client) {
    time = client->readLong();
}

PacketType PingPacket::getType() {
    return PacketType::PING;
}

int PingPacket::getId() {
    return 0xFF;
}

string PingPacket::toString() {
    stringstream ss;
    ss << "PingPacket{time=" << time << "}";
    return ss.str();
}
