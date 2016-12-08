//
// Created by dialight on 01.11.16.
//

#include "network/properties/protocol/in/GetPropertyPacket.hpp"

using namespace std;

GetPropertyPacket::GetPropertyPacket() : InPacket() {}

void GetPropertyPacket::read(TCPSocketClient *client) {
    key = client->readUTF();
}

PacketType GetPropertyPacket::getType() {
    return PacketType::GET_PROPERTY;
}

int GetPropertyPacket::getId() {
    return 0x01;
}

string GetPropertyPacket::toString() {
    stringstream ss;
    ss << "ChangePropertyPacket{key=" << key << "}";
    return ss.str();
}
