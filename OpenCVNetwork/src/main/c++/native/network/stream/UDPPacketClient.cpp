//
// Created by dialight on 06.11.16.
//

#include <network/stream/UDPPacketClient.hpp>
#include <network/stream/protocol/ImagePacket.hpp>

void UDPPacketClient::sendPacket(ImagePacket *packet, ServerAddr *addr) {
    packet->send(this, addr);
}
