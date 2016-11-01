//
// Created by dialight on 01.11.16.
//

#include "network/properties/protocol/out/AllPropertiesPacket.hpp"

PacketType AllPropertiesPacket::TYPE("AllPropertiesPacket");

AllPropertiesPacket::AllPropertiesPacket(map<string, int> *props) : props(props) {

}

void AllPropertiesPacket::write(TCPClient *client) {
    client->writeShort((int) props->size());
    for (auto it = props->begin(); it != props->end(); ++it) {
        client->writeUTF(it->first);
        client->writeInt(it->second);
    }
}

PacketType AllPropertiesPacket::getType() {
    return TYPE;
}

