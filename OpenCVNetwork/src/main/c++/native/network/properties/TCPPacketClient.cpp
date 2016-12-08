//
// Created by dialight on 01.11.16.
//

#include "network/properties/PropertiesClient.hpp"
#include <network/exceptions/IOException.hpp>

TCPPacketClient::TCPPacketClient() : TCPSocketClient() {

}

void TCPPacketClient::registerInPacketHandler(InPacketHandler handler, void *args) {
    this->inHandler = handler;
    this->inArgs = args;
}

void TCPPacketClient::registerOutPacketHandler(OutPacketHandler handler, void *args) {
    this->outHandler = handler;
    this->outArgs = args;
}

void TCPPacketClient::setProtocol(Protocol *protocol) {
    this->protocol = protocol;
}

void TCPPacketClient::sendPacket(OutPacket *packet) {
    std::lock_guard<std::mutex> lock(this->writeLock);
    outHandler(packet, outArgs);
    writeByte(packet->getId());
    packet->write(this);
    //lock_guard<mutex> destructor unlock writeLock
}

bool TCPPacketClient::trySendPacket(OutPacket *packet) {
    if (isConnected()) {
        try {
            sendPacket(packet); //thread safe
        } catch (IOException e) {
            e.printError();
            close();
        }
    }
}

void TCPPacketClient::processPacket() {
    int id = readByte();
    InPacket *packet = protocol->newInstance(id);
    packet->read(this);
    inHandler(packet, inArgs);
    delete packet;
}