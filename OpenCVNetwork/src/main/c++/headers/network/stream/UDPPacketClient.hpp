//
// Created by dialight on 06.11.16.
//

#ifndef OPENCVCLIENT_UDPPACKETCLIENT_HPP
#define OPENCVCLIENT_UDPPACKETCLIENT_HPP


#include <network/stream/protocol/ImagePacket.hpp>
#include "UDPSocketClient.hpp"

class UDPPacketClient : public UDPSocketClient {

public:
    void sendPacket(ImagePacket *packet, ServerAddr *addr);

};


#endif //OPENCVCLIENT_UDPPACKETCLIENT_HPP
