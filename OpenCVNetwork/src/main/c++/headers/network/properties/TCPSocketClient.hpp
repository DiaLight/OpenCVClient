//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_TCPCLIENT_HPP
#define OPENCVCLIENT_TCPCLIENT_HPP

#include "network/ServerAddr.hpp"

class TCPSocketClient;

class ConnectionGuard {
    TCPSocketClient *client;
    ServerAddr *addr;
public:
    ConnectionGuard(TCPSocketClient *client, ServerAddr *addr);

    virtual ~ConnectionGuard();
};

class TCPSocketClient {
    bool binded;
    bool connected;
    int cliDesc;

    char stringBuf[4096];
public:
    TCPSocketClient();

    TCPSocketClient(const TCPSocketClient&) = delete; //deleted copy constructor
    TCPSocketClient& operator=(const TCPSocketClient &) = delete; //deleted copy assignment operato

    virtual ~TCPSocketClient();

private:
    friend class ConnectionGuard;
    void connectTCP(ServerAddr *addr);

public:
    void close();
    bool isConnected();

    string readUTF();
    void writeUTF(const string& str);

    int readShort();
    void writeShort(int s);

    int readInt();
    void writeInt(int i);

    double readDouble();
    void writeDouble(double i);

    __uint64_t readLong();
    void writeLong(__uint64_t i);

    int readByte();
    void writeByte(int i);

    bool readBool();
    void writeBool(bool b);

};


#endif //OPENCVCLIENT_TCPCLIENT_HPP
