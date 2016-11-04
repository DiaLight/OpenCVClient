//
// Created by dialight on 31.10.16.
//

#include "network/properties/protocol/out/AddPropertyPacket.hpp"

AddPropertyPacket::AddPropertyPacket(const string &key, Property *value) : key(key), value(value) {
}

void AddPropertyPacket::write(TCPSocketClient *client) {
    client->writeUTF(key);
    client->writeByte(value->getType());
    value->write(client);
}

PacketType AddPropertyPacket::getType() {
    return PacketType::ADD_PROPERTY;
}

int AddPropertyPacket::getId() {
    return 0x01;
}

string AddPropertyPacket::toString() {
    stringstream ss;
    ss << "AddPropertyPacket{key=" << key << ", value=" << value->toString() << "}";
    return ss.str();
}
