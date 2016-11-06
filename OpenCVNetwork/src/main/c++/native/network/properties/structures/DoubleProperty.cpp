//
// Created by dialight on 03.11.16.
//

#include "network/properties/structures/DoubleProperty.hpp"

DoubleProperty::DoubleProperty(double value) : value(value) {}

double DoubleProperty::get() {
    return value;
}

void DoubleProperty::updateFrom(Property *prop) {
    this->value = ((DoubleProperty *) prop)->value;
}

void DoubleProperty::read(TCPSocketClient *client) {
    value = client->readDouble();
}

void DoubleProperty::write(TCPSocketClient *client) {
    client->writeDouble(value);
}

PropertyType DoubleProperty::getType() {
    return PropertyType::DOUBLE;
}

string DoubleProperty::toString() {
    return to_string(value);
}
