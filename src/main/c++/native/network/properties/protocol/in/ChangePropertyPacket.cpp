//
// Created by dialight on 31.10.16.
//

#include "network/properties/protocol/in/ChangePropertyPacket.hpp"

PacketType ChangePropertyPacket::TYPE("ChangePropertyPacket");

ChangePropertyPacket::ChangePropertyPacket() : InPacket() {

}

void ChangePropertyPacket::read(TCPClient *client) {
    key = client->readUTF();
    value = client->readInt();
}

PacketType ChangePropertyPacket::getType() {
    return TYPE;
}
