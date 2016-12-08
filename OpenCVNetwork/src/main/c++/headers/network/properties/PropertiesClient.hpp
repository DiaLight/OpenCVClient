/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PropertiesClient.hpp
 * Author: dialight
 *
 * Created on 26 октября 2016 г., 16:36
 */

#ifndef PROPERTIESCLIENT_HPP
#define PROPERTIESCLIENT_HPP

#include "AppState.hpp"
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <network/properties/protocol/Protocol.hpp>
#include <PropertiesListener.hpp>
#include "TCPSocketClient.hpp"
#include "TCPPacketClient.hpp"

class PropertiesClient : TCPPacketClient, public ::PropertiesListener {

    ServerAddr *addr;

    std::thread *clientThread;
public:
    static bool DEBUG;
    static std::vector<PacketType> IGNORE_PACKET;

    PropertiesClient(ServerAddr *addr);

    PropertiesClient(const PropertiesClient&) = delete; //deleted copy constructor
    PropertiesClient& operator=(const PropertiesClient &) = delete; //deleted copy assignment operator
    
    virtual ~PropertiesClient();

    void onNewProperty(std::string name, PropertyPointer property) override;

    void runAsync();

private:

    static void connectStatic(void *params) {
        ((PropertiesClient *) params)->connect();
    }
    void connect();

    static void onInPacketReceivedStatic(InPacket *p, void *args) {
        ((PropertiesClient *) args)->onInPacketReceived(p);
    }
    void onInPacketReceived(InPacket *p);

    static void onOutPacketSendStatic(OutPacket *p, void *args) {
        ((PropertiesClient *) args)->onOutPacketSend(p);
    }
    void onOutPacketSend(OutPacket *p);

};

#endif /* CONFIGSERVER_HPP */

