//
// Created by dialight on 06.12.16.
//

#ifndef OPENCVCLIENT_DATASTREAM_HPP
#define OPENCVCLIENT_DATASTREAM_HPP

#include <string>

class DataStream {

public:
    virtual std::string readUTF() = 0;
    virtual void writeUTF(const std::string& str) = 0;

    virtual int readShort() = 0;
    virtual void writeShort(int s) = 0;

    virtual int readInt() = 0;
    virtual void writeInt(int i) = 0;

    virtual double readDouble() = 0;
    virtual void writeDouble(double i) = 0;

    virtual __uint64_t readLong() = 0;
    virtual void writeLong(__uint64_t i) = 0;

    virtual int readByte() = 0;
    virtual void writeByte(int i) = 0;

    virtual bool readBool() = 0;
    virtual void writeBool(bool b) = 0;
};

#endif //OPENCVCLIENT_DATASTREAM_HPP
