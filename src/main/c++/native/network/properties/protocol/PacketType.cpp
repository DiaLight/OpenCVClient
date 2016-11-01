//
// Created by dialight on 01.11.16.
//

#include <network/properties/protocol/PacketType.hpp>

int PacketType::counter;

PacketType::PacketType(const string &name) : name(name) {
    id = counter++;
}

bool PacketType::operator==(const PacketType &rhs) const {
    return id == rhs.id;
}

bool PacketType::operator!=(const PacketType &rhs) const {
    return !(rhs == *this);
}

bool PacketType::operator<(const PacketType &rhs) const {
    return id < rhs.id;
}

bool PacketType::operator>(const PacketType &rhs) const {
    return rhs < *this;
}

bool PacketType::operator<=(const PacketType &rhs) const {
    return !(rhs < *this);
}

bool PacketType::operator>=(const PacketType &rhs) const {
    return !(*this < rhs);
}

int PacketType::ordinal() {
    return id;
}

string PacketType::getName() {
    return name;
}
