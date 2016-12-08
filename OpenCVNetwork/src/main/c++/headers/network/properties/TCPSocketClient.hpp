//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_TCPCLIENT_HPP
#define OPENCVCLIENT_TCPCLIENT_HPP

#include <DataStream.hpp>
#include "network/ServerAddr.hpp"

class TCPSocketClient;

class ConnectionGuard {
    TCPSocketClient *client;
    ServerAddr *addr;
public:
    ConnectionGuard(TCPSocketClient *client, ServerAddr *addr);

    virtual ~ConnectionGuard();
};

class TCPSocketClient : public ::DataStream {
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

    std::string readUTF() override;
    void writeUTF(const std::string& str) override;

    int readShort() override;
    void writeShort(int s) override;

    int readInt() override;
    void writeInt(int i) override;

    double readDouble() override;
    void writeDouble(double i) override;

    __uint64_t readLong() override;
    void writeLong(__uint64_t i) override;

    int readByte() override;
    void writeByte(int i) override;

    bool readBool() override;
    void writeBool(bool b) override;

};


#endif //OPENCVCLIENT_TCPCLIENT_HPP
