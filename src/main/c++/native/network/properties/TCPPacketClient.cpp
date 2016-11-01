//
// Created by dialight on 01.11.16.
//

#include <iostream>
#include "network/properties/TCPPacketClient.hpp"

TCPPacketClient::TCPPacketClient() : TCPClient() {

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
    lock_guard<mutex> lock(this->writeLock);
    outHandler(packet, outArgs);
    writeByte(protocol->getId(packet));
    packet->write(this);
    //lock_guard<mutex> destructor unlock writeLock
}

void TCPPacketClient::processPacket() {
    int id = readByte();
    InPacket *packet = protocol->newInstance(id);
    packet->read(this);
    inHandler(packet, inArgs);
    delete packet;
}
