//
// Created by dialight on 03.11.16.
//

#ifndef OPENCVCLIENT_INTPROPERTY_HPP
#define OPENCVCLIENT_INTPROPERTY_HPP


#include "Property.hpp"

class IntProperty : public Property {

    int value;
public:
    IntProperty();
    IntProperty(int defVal);

    int get();

    void read(TCPSocketClient *client) override;

    void write(TCPSocketClient *client) override;
    PropertyType getType() override;

    string toString() override;
};


#endif //OPENCVCLIENT_INTPROPERTY_HPP
