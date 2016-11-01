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
#include <thread>
#include <mutex>
#include <network/properties/protocol/Protocol.hpp>
#include "TCPClient.hpp"
#include "TCPPacketClient.hpp"

using namespace std;

class PropertiesClient : TCPPacketClient {
    ServerAddr *addr;

    thread *thr;
    map <string, int> props;
public:
    PropertiesClient(ServerAddr *addr);

    PropertiesClient(const PropertiesClient&) = delete; //deleted copy constructor
    PropertiesClient& operator=(const PropertiesClient &) = delete; //deleted copy assignment operato
    
    virtual ~PropertiesClient();

    int getInt(const string& name, int defVal);
    
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

