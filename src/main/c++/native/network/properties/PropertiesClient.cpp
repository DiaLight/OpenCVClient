//
// Created by dialight on 31.10.16.
//
#include "network/properties/PropertiesClient.hpp"
#include <sstream>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <network/exceptions/IOException.hpp>
#include <network/properties/protocol/in/ChangePropertyPacket.hpp>
#include <network/properties/protocol/in/PingPacket.hpp>
#include <network/properties/protocol/in/GetAllPropertiesPacket.hpp>
#include <network/properties/protocol/in/GetPropertyPacket.hpp>
#include <network/properties/protocol/in/ResetPropertyPacket.hpp>
#include <network/properties/protocol/out/AddPropertyPacket.hpp>
#include <network/properties/protocol/out/RemovePropertyPacket.hpp>
#include <network/properties/protocol/out/PongPacket.hpp>
#include <network/properties/protocol/out/AllPropertiesPacket.hpp>

using namespace std;

PropertiesClient::PropertiesClient(ServerAddr *addr) : TCPPacketClient() {
    this->addr = addr;
    this->thr = NULL;
}

PropertiesClient::~PropertiesClient() {
    if(thr != NULL) {
        thr->join();
        delete thr;
    }
}

int PropertiesClient::getInt(const string& name, int defVal) {
    auto it = props.find(name);
    if (it != props.end()) return it->second;
    props.insert(pair<string, int>(name, defVal));
    if (isConnected()) {
        try {
            AddPropertyPacket pa(name, defVal);
            sendPacket(&pa); //thread safe
        } catch (IOException e) {
            e.printError();
        }
    }
    return defVal;
}

void PropertiesClient::runAsync() {
    thr = new thread(connectStatic, this);
}

void PropertiesClient::onOutPacketSend(OutPacket *p) {
    cout << "out: " << p->getType().getName() << endl;
}

void PropertiesClient::onInPacketReceived(InPacket *p) {
    cout << "in: " << p->getType().getName() << endl;
    if(p->getType() == PingPacket::TYPE) {
        PingPacket *packet = (PingPacket *) p;
        PongPacket pa(packet->time);
        sendPacket(&pa);
        return;
    }
    if(p->getType() == GetAllPropertiesPacket::TYPE) {
        AllPropertiesPacket pa(&props);
        sendPacket(&pa);
        return;
    }
    if(p->getType() == GetPropertyPacket::TYPE) {
        GetPropertyPacket *packet = (GetPropertyPacket *) p;
        auto it = props.find(packet->key);
        if (it != props.end()) {
            AddPropertyPacket pa(packet->key, it->second);
            sendPacket(&pa);
        } else {
            RemovePropertyPacket pa(packet->key);
            sendPacket(&pa);
        }
        return;
    }
    if(p->getType() == ChangePropertyPacket::TYPE) {
        ChangePropertyPacket *packet = (ChangePropertyPacket *) p;
        auto it = props.find(packet->key);
        if (it != props.end()) {
            it->second = packet->value;
        } else {
            props.insert(pair<string, int>(packet->key, packet->value));
        }
        return;
    }
    if(p->getType() == ResetPropertyPacket::TYPE) {
        ResetPropertyPacket *packet = (ResetPropertyPacket *) p;
        props.erase(packet->key);
        return;
    }
    throw RuntimeException("Unknown packet type. Please, register your packet in protocol.");
}

void PropertiesClient::connect() {

    Protocol protocol;

    protocol.registerInPacket(0, GetAllPropertiesPacket::constructor);
    protocol.registerInPacket(1, GetPropertyPacket::constructor);
    protocol.registerInPacket(2, ChangePropertyPacket::constructor);
    protocol.registerInPacket(3, ResetPropertyPacket::constructor);
    protocol.registerInPacket(0xFF, PingPacket::constructor);

    protocol.registerOutPacket(0, AllPropertiesPacket::TYPE);
    protocol.registerOutPacket(1, AddPropertyPacket::TYPE);
    protocol.registerOutPacket(3, RemovePropertyPacket::TYPE);
    protocol.registerOutPacket(0xFF, PongPacket::TYPE);

    setProtocol(&protocol);

    registerInPacketHandler(onInPacketReceivedStatic, this);
    registerOutPacketHandler(onOutPacketSendStatic, this);

    while(alive) {
        try {
            ConnectionGuard guard(this, addr); //life cycle safe
            cout << "Properties client connected" << endl;
            while (alive && isConnected()) {
                processPacket();
            }
            //guard destructor close connection
        } catch(IOException e) {
            e.printError();
        }
        sleep(3);
    }
    pthread_exit(NULL);
}

