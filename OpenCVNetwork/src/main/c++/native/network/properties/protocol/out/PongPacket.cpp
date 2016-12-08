//
// Created by dialight on 01.11.16.
//

#include "network/properties/protocol/out/PongPacket.hpp"

using namespace std;

PongPacket::PongPacket(__uint64_t time) : time(time), OutPacket() {

}

void PongPacket::write(TCPSocketClient *client) {
    client->writeLong(time);
}

PacketType PongPacket::getType() {
    return PacketType::PONG;
}

int PongPacket::getId() {
    return 0xFF;
}

string PongPacket::toString() {
    stringstream ss;
    ss << "PongPacket{time=" << time << "}";
    return ss.str();
}
