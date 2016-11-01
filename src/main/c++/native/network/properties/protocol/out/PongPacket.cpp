//
// Created by dialight on 01.11.16.
//

#include "network/properties/protocol/out/PongPacket.hpp"

PacketType PongPacket::TYPE("PongPacket");

PongPacket::PongPacket(__uint64_t time) : time(time), OutPacket() {

}

void PongPacket::write(TCPClient *client) {
    client->writeLong(time);
}

PacketType PongPacket::getType() {
    return TYPE;
}
