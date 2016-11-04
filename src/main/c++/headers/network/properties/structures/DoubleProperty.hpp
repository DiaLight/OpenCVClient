//
// Created by dialight on 03.11.16.
//

#ifndef OPENCVCLIENT_DOUBLEPROPERTY_HPP
#define OPENCVCLIENT_DOUBLEPROPERTY_HPP

#include "Property.hpp"

class DoubleProperty : public Property {

    double value;
public:
    DoubleProperty();
    DoubleProperty(double value);

    double get();

    void read(TCPSocketClient *client) override;

    void write(TCPSocketClient *client) override;

    PropertyType getType() override;

    string toString() override;
};


#endif //OPENCVCLIENT_DOUBLEPROPERTY_HPP
