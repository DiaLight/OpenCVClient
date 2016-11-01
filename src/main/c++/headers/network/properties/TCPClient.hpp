//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_TCPCLIENT_HPP
#define OPENCVCLIENT_TCPCLIENT_HPP

#include "network/ServerAddr.hpp"

class TCPClient;

class ConnectionGuard {
    TCPClient *client;
    ServerAddr *addr;
public:
    ConnectionGuard(TCPClient *client, ServerAddr *addr);

    virtual ~ConnectionGuard();
};

class TCPClient {
    bool binded;
    bool connected;
    int cliDesc;

    char stringBuf[4096];
public:
    TCPClient();

    TCPClient(const TCPClient&) = delete; //deleted copy constructor
    TCPClient& operator=(const TCPClient &) = delete; //deleted copy assignment operato

    virtual ~TCPClient();

private:
    friend class ConnectionGuard;
    void connectTCP(ServerAddr *addr);
    void close();

public:
    bool isConnected();

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


#endif //OPENCVCLIENT_TCPCLIENT_HPP
