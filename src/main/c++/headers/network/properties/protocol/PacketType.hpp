//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_PACKETTYPE_HPP
#define OPENCVCLIENT_PACKETTYPE_HPP

#include <string>

using namespace std;

class PacketType {

    static int counter;
    int id;
    string name;

public:

    PacketType(const string &name);

//    PacketType(const PacketType&) = delete; //deleted copy constructor
    PacketType& operator=(const PacketType &) = delete; //deleted copy assignment operato

    bool operator==(const PacketType &rhs) const;
    bool operator!=(const PacketType &rhs) const;
    bool operator<(const PacketType &rhs) const;
    bool operator>(const PacketType &rhs) const;
    bool operator<=(const PacketType &rhs) const;
    bool operator>=(const PacketType &rhs) const;

    int ordinal();
    string getName();

};


#endif //OPENCVCLIENT_PACKETTYPE_HPP
