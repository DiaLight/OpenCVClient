//
// Created by dialight on 31.10.16.
//
#include "network/properties/PropertiesClient.hpp"
#include "AppState.hpp"
#include <cstdlib>
#include <string>
#include <sstream>
#include <string.h>
#include <iostream>
#include <unistd.h>

using namespace std;

PropertiesClient::PropertiesClient(ServerAddr *addr) {
    this->addr = addr;
    this->thr = NULL;
    this->connected = false;
}

PropertiesClient::~PropertiesClient() {
    close(cliDesc);
    if(thr != NULL) {
        thr->join();
        delete thr;
    }
}

int PropertiesClient::getInt(const string& name, int defVal) {
    auto it = params.find(name);
    if (it != params.end()) return it->second;
    params.insert(pair<string, int>(name, defVal));
    params_m.lock();
    if (connected) {
        try {
            writeByte(1); //read
            writeUTF(name);
            writeInt(defVal);
        } catch (string e) {
            cerr << e << endl;
        }
    }
    params_m.unlock();
    return defVal;
}

void PropertiesClient::runAsync() {
    thr = new thread(connectStatic, this);
}

void PropertiesClient::connect() {
    while(alive) {
        cliDesc = socket(AF_INET, SOCK_STREAM, 0);
        if (cliDesc < 0) {
            cerr << "ERROR, Failed creating socket. " << strerror(errno) << endl;
            exit(1);
        }
        if (::connect(cliDesc, (struct sockaddr *) &addr->srvAddr, addr->srvAddrLen) < 0) {
            //cerr << "ERROR, Failed to connect. " << strerror(errno) << endl;
            sleep(2);
            continue;
        }
        cout << "Properties client connected" << endl;
        try {
            process();
        } catch(string e) {
            params_m.try_lock();
            connected = false;
            params_m.unlock();
            cerr << e << endl;
        }
        close(cliDesc);
        sleep(3);
    }
    pthread_exit(NULL);
}

void PropertiesClient::process() {
    size_t size = params.size();
    params_m.lock();
    connected = true;
    params_m.unlock();
    while (alive && connected) {
        int op = readByte();
        switch(op) {
            case 0: //update all
                params_m.lock();
                writeByte(0); //callback id
                writeShort(params.size());
                for (auto it = params.begin(); it != params.end(); ++it) {
                    writeUTF(it->first);
                    writeInt(it->second);
                }
                params_m.unlock();
                break;
            case 1: { //read
                string key = readUTF();
                auto it = params.find(key);
                params_m.lock();
                if (it != params.end()) {
                    writeByte(1); //write
                    writeUTF(key);
                    writeInt(it->second);
                } else {
                    writeByte(3); //remove
                    writeUTF(key);
                }
                params_m.unlock();
            }break;
            case 2: { //write
                string key = readUTF();
                int value = readInt();
                auto it = params.find(key);
                if (it != params.end()) {
                    it->second = value;
                } else {
                    params.insert(pair<string, int>(key, value));
                }
            }break;
            case 3: { //reset
                string key = readUTF();
                params.erase(key);
            }
                break;
            case 0xFF: { //ping-pong
                __uint64_t time = readLong();
                params_m.lock();
                writeByte(0xFF); //callback id
                writeLong(time);
                params_m.unlock();
            }
                break;
            default:
                stringstream ss;
                ss << "Error in protocol: Bad operation " << op;
                throw ss.str();
        }
    }
}

string PropertiesClient::readUTF() {
    int size = readShort();
    ssize_t len = recv(cliDesc, stringBuf, size, 0); //MSG_WAITALL
    if (len != size) {
        if (len == 0) throw string("Error on readUTF: End of socket");
        throw string("Error on readUTF(): ") + strerror(errno);
    }
    return string(stringBuf, size);
}

void PropertiesClient::writeUTF(const string& str) {
    writeShort(str.length());
    ssize_t len = send(cliDesc, str.c_str(), str.length(), MSG_NOSIGNAL);
    if(len != str.length()) {
        throw string("Error on writeUTF(): ") + strerror(errno);
    }
}

int PropertiesClient::readShort() {
    int s = 0;
    ssize_t len = recv(cliDesc, &s, 2, 0); //MSG_WAITALL
    if (len != 2) {
        if (len == 0) throw string("Error on readShort: End of socket");
        throw string("Error on readShort(): ") + strerror(errno);
    }
    return __bswap_16(s);
}

void PropertiesClient::writeShort(int s) {
    s = __bswap_16(s);
    if (send(cliDesc, &s, 2, MSG_NOSIGNAL) != 2) {
        throw string("Error on writeShort(): ") + strerror(errno);
    }
}

int PropertiesClient::readInt() {
    int s = 0;
    ssize_t len = recv(cliDesc, &s, 4, 0); //MSG_WAITALL
    if (len != 4) {
        if (len == 0) throw string("Error on readInt(): End of socket");
        throw string("Error on readInt(): ") + strerror(errno);
    }
    return __bswap_32(s);
}

void PropertiesClient::writeInt(int i) {
    i = __bswap_32(i);
    if (send(cliDesc, &i, 4, MSG_NOSIGNAL) != 4) {
        throw string("Error on writeInt(): ") + strerror(errno);
    }
}

__uint64_t PropertiesClient::readLong() {
    __uint64_t s = 0;
    ssize_t len = recv(cliDesc, &s, 8, 0); //MSG_WAITALL
    if (len != 8) {
        if (len == 0) throw string("Error on readLong(): End of socket");
        throw string("Error on readLong(): ") + strerror(errno);
    }
    return __bswap_64(s);
}

void PropertiesClient::writeLong(__uint64_t i) {
    i = __bswap_64(i);
    if (send(cliDesc, &i, 8, MSG_NOSIGNAL) != 8) {
        throw string("Error on writeLong(): ") + strerror(errno);
    }
}

int PropertiesClient::readByte() {
    int i = 0;
    ssize_t len = recv(cliDesc, &i, 1, 0); //MSG_WAITALL
    if (len != 1) {
        if (len == 0) throw string("Error on readByte(): End of socket");
        throw string("Error on readByte(): ") + strerror(errno);
    }
    return i;
}

void PropertiesClient::writeByte(int i) {
    if (send(cliDesc, &i, 1, MSG_NOSIGNAL) != 1) {
        throw string("Error on writeByte(): ") + strerror(errno);
    }
}

bool PropertiesClient::readBool() {
    int i = 0;
    ssize_t len = recv(cliDesc, &i, 1, 0); //MSG_WAITALL
    if (len != 1) {
        if (len == 0) throw string("Error on readBool(): End of socket");
        throw string("Error on readBool(): ") + strerror(errno);
    }
    return i != 0;
}

void PropertiesClient::writeBool(bool b) {
    int i = (b ? 1 : 0);
    if (send(cliDesc, &i, 1, MSG_NOSIGNAL) != 1) {
        throw string("Error on writeBool(): ") + strerror(errno);
    }
}
