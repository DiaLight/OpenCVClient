//
// Created by dialight on 01.11.16.
//

#ifndef OPENCVCLIENT_TCPPACKETCLIENT_HPP
#define OPENCVCLIENT_TCPPACKETCLIENT_HPP


#include <network/properties/protocol/Protocol.hpp>
#include <mutex>

typedef void (*InPacketHandler)(InPacket *, void *);
typedef void (*OutPacketHandler)(OutPacket *, void *);

class TCPPacketClient : protected TCPSocketClient {

    Protocol *protocol;

    InPacketHandler inHandler;
    void *inArgs;
    OutPacketHandler outHandler;
    void *outArgs;

    mutex writeLock;

protected:
    TCPPacketClient();

public:

    void registerInPacketHandler(InPacketHandler handler, void *args);
    void registerOutPacketHandler(OutPacketHandler handler, void *args);

    void setProtocol(Protocol *protocol);

    void sendPacket(OutPacket *packet);

    bool trySendPacket(OutPacket *packet);

    void processPacket();

};


#endif //OPENCVCLIENT_TCPPACKETCLIENT_HPP
