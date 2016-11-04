//
// Created by dialight on 03.11.16.
//

#ifndef OPENCVCLIENT_PROPERTY_HPP
#define OPENCVCLIENT_PROPERTY_HPP

#include <network/properties/TCPSocketClient.hpp>

class Property;

enum PropertyType {
    INT,
    DOUBLE,
    SELECT
};

typedef Property *PropertyPointer;

class Property {
public:
    virtual void updateFrom(Property *prop) = 0;
    virtual void read(TCPSocketClient *client) = 0;
    virtual void write(TCPSocketClient *client) = 0;
    virtual PropertyType getType() = 0;
    virtual string toString() = 0;
};


#endif //OPENCVCLIENT_PROPERTY_HPP
