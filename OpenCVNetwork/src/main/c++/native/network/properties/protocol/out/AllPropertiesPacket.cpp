//
// Created by dialight on 01.11.16.
//

#include "network/properties/protocol/out/AllPropertiesPacket.hpp"

AllPropertiesPacket::AllPropertiesPacket(map<string, PropertyPointer> *props) : props(props) {

}

void AllPropertiesPacket::write(TCPSocketClient *client) {
    client->writeShort((int) props->size());
    for (auto it = props->begin(); it != props->end(); ++it) {
        client->writeUTF(it->first);
        client->writeByte(it->second->getType());
        it->second->write(client);
    }
}

PacketType AllPropertiesPacket::getType() {
    return PacketType::ALL_PROPERTIES;
}

int AllPropertiesPacket::getId() {
    return 0x00;
}

string AllPropertiesPacket::toString() {
    stringstream ss;
    ss << "AllPropertiesPacket{props=";
    if(props->empty()) {
        ss << "{}";
    } else {
        ss << "{\n";
        for (auto it = props->begin(); it != props->end(); ++it) {
            ss << "    " << it->first << " = " << it->second->toString() << "\n";
        }
        ss << "}";
    }
    ss << "}";
    return ss.str();
}

