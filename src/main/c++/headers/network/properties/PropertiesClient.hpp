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
#include "network/ServerAddr.hpp"

using namespace std;

class PropertiesClient {
    ServerAddr *addr;
    int cliDesc;
    bool connected;
    
    thread *thr;
    mutex params_m;
    map <string, int> params;

    char stringBuf[4096];
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
    void process();

    string readUTF();
    void writeUTF(const string& str);

    int readShort();
    void writeShort(int s);

    int readInt();
    void writeInt(int i);

    __uint64_t readLong();
    void writeLong(__uint64_t i);

    int readByte();
    void writeByte(int i);

    bool readBool();
    void writeBool(bool b);
    
};

#endif /* CONFIGSERVER_HPP */

