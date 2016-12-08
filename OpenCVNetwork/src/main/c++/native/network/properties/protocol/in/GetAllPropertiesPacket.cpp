//
// Created by dialight on 01.11.16.
//

#include "network/properties/protocol/in/GetAllPropertiesPacket.hpp"

using namespace std;

GetAllPropertiesPacket::GetAllPropertiesPacket() : InPacket() {}

void GetAllPropertiesPacket::read(TCPSocketClient *client) {

}

PacketType GetAllPropertiesPacket::getType() {
    return PacketType::GET_ALL_PROPERTIES;
}

int GetAllPropertiesPacket::getId() {
    return 0x00;
}

string GetAllPropertiesPacket::toString() {
    return "GetAllPropertiesPacket{}";
}
