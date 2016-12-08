//
// Created by dialight on 01.11.16.
//

#include "network/properties/protocol/out/RemovePropertyPacket.hpp"

using namespace std;

RemovePropertyPacket::RemovePropertyPacket(const string &key) : key(key) {

}

void RemovePropertyPacket::write(TCPSocketClient *client) {
    client->writeUTF(key);
}

PacketType RemovePropertyPacket::getType() {
    return PacketType::REMOVE_PROPERTY;
}

int RemovePropertyPacket::getId() {
    return 0x03;
}

string RemovePropertyPacket::toString() {
    stringstream ss;
    ss << "RemovePropertyPacket{key=" << key << "}";
    return ss.str();
}
