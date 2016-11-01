//
// Created by dialight on 01.11.16.
//

#include "network/properties/protocol/in/GetAllPropertiesPacket.hpp"

PacketType GetAllPropertiesPacket::TYPE("GetAllPropertiesPacket");

GetAllPropertiesPacket::GetAllPropertiesPacket() : InPacket() {}

void GetAllPropertiesPacket::read(TCPClient *client) {

}

PacketType GetAllPropertiesPacket::getType() {
    return TYPE;
}
