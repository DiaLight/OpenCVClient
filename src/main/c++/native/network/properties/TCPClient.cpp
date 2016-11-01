//
// Created by dialight on 31.10.16.
//

#include <cstring>
#include <unistd.h>
#include <network/exceptions/RuntimeException.hpp>
#include <network/exceptions/IOException.hpp>
#include "network/properties/TCPClient.hpp"

ConnectionGuard::ConnectionGuard(TCPClient *client, ServerAddr *addr) : client(client), addr(addr) {
    client->connectTCP(addr);
}

ConnectionGuard::~ConnectionGuard() {
    client->close();
}

TCPClient::TCPClient() {
    this->binded = false;
    this->connected = false;
}

TCPClient::~TCPClient() {

}

void TCPClient::connectTCP(ServerAddr *addr) {
    if(!binded) {
        cliDesc = socket(AF_INET, SOCK_STREAM, 0);
        if (cliDesc < 0) {
            throw RuntimeException(string("ERROR, Failed creating socket. ") + strerror(errno));
        }
        binded = true;
    }
    if (::connect(cliDesc, (struct sockaddr *) &addr->srvAddr, addr->srvAddrLen) < 0) {
        throw IOException(string("ERROR, Failed to connect. ") + strerror(errno), true);
    }
    connected = true;
}

void TCPClient::close() {
    connected = false;
    if(!binded) return;
    ::close(cliDesc);
    binded = false;
}

bool TCPClient::isConnected() {
    return connected;
}

string TCPClient::readUTF() {
    size_t size = (size_t) readShort();
    ssize_t len = recv(cliDesc, stringBuf, size, 0); //MSG_WAITALL
    if (len != size) {
        if (len == 0) throw IOException(string("Error on readUTF: End of socket"));
        throw IOException(string("Error on readUTF(): ") + strerror(errno));
    }
    return string(stringBuf, size);
}
void TCPClient::writeUTF(const string& str) {
    writeShort((int) str.length());
    ssize_t len = send(cliDesc, str.c_str(), str.length(), MSG_NOSIGNAL);
    if(len != str.length()) {
        throw IOException(string("Error on writeUTF(): ") + strerror(errno));
    }
}

int TCPClient::readShort() {
    int s = 0;
    ssize_t len = recv(cliDesc, &s, 2, 0); //MSG_WAITALL
    if (len != 2) {
        if (len == 0) throw IOException(string("Error on readShort: End of socket"));
        throw IOException(string("Error on readShort(): ") + strerror(errno));
    }
    return __bswap_16(s);
}
void TCPClient::writeShort(int s) {
    s = __bswap_16(s);
    if (send(cliDesc, &s, 2, MSG_NOSIGNAL) != 2) {
        throw IOException(string("Error on writeShort(): ") + strerror(errno));
    }
}

int TCPClient::readInt() {
    unsigned int s = 0;
    ssize_t len = recv(cliDesc, &s, 4, 0); //MSG_WAITALL
    if (len != 4) {
        if (len == 0) throw IOException(string("Error on readInt(): End of socket"));
        throw IOException(string("Error on readInt(): ") + strerror(errno));
    }
    return __bswap_32(s);
}
void TCPClient::writeInt(int i) {
    i = __bswap_32((unsigned int) i);
    if (send(cliDesc, &i, 4, MSG_NOSIGNAL) != 4) {
        throw IOException(string("Error on writeInt(): ") + strerror(errno));
    }
}

__uint64_t TCPClient::readLong() {
    __uint64_t s = 0;
    ssize_t len = recv(cliDesc, &s, 8, 0); //MSG_WAITALL
    if (len != 8) {
        if (len == 0) throw IOException(string("Error on readLong(): End of socket"));
        throw IOException(string("Error on readLong(): ") + strerror(errno));
    }
    return __bswap_64(s);
}
void TCPClient::writeLong(__uint64_t i) {
    i = __bswap_64(i);
    if (send(cliDesc, &i, 8, MSG_NOSIGNAL) != 8) {
        throw IOException(string("Error on writeLong(): ") + strerror(errno));
    }
}

int TCPClient::readByte() {
    int i = 0;
    ssize_t len = recv(cliDesc, &i, 1, 0); //MSG_WAITALL
    if (len != 1) {
        if (len == 0) throw IOException(string("Error on readByte(): End of socket"));
        throw IOException(string("Error on readByte(): ") + strerror(errno));
    }
    return i;
}
void TCPClient::writeByte(int i) {
    if (send(cliDesc, &i, 1, MSG_NOSIGNAL) != 1) {
        throw IOException(string("Error on writeByte(): ") + strerror(errno));
    }
}

bool TCPClient::readBool() {
    int i = 0;
    ssize_t len = recv(cliDesc, &i, 1, 0); //MSG_WAITALL
    if (len != 1) {
        if (len == 0) throw IOException(string("Error on readBool(): End of socket"));
        throw IOException(string("Error on readBool(): ") + strerror(errno));
    }
    return i != 0;
}
void TCPClient::writeBool(bool b) {
    int i = (b ? 1 : 0);
    if (send(cliDesc, &i, 1, MSG_NOSIGNAL) != 1) {
        throw IOException(string("Error on writeBool(): ") + strerror(errno));
    }
}
