//
// Created by dialight on 31.10.16.
//

#include <structures/PropertyFactory.hpp>
#include "network/properties/protocol/in/ChangePropertyPacket.hpp"

using namespace std;

ChangePropertyPacket::ChangePropertyPacket() : InPacket() {

}

ChangePropertyPacket::~ChangePropertyPacket() {
    delete value;
}

void ChangePropertyPacket::read(TCPSocketClient *client) {
    key = client->readUTF();
    int type = client->readByte();
    value = PropertyFactory::newInstance((PropertyType) type);
    value->deserialize(client);
}

PacketType ChangePropertyPacket::getType() {
    return PacketType::CHANGE_PROPERTY;
}

int ChangePropertyPacket::getId() {
    return 0x02;
}

string ChangePropertyPacket::toString() {
    stringstream ss;
    ss << "ChangePropertyPacket{key=" << key << ", value=" << value->toString() << "}";
    return ss.str();
}
