//
// Created by dialight on 03.11.16.
//

#include "network/properties/structures/IntProperty.hpp"

IntProperty::IntProperty(int defVal) : value(defVal) {}

int IntProperty::get() {
    return value;
}

void IntProperty::updateFrom(Property *prop) {
    this->value = ((IntProperty *) prop)->value;
}

void IntProperty::read(TCPSocketClient *client) {
    value = client->readInt();
}

void IntProperty::write(TCPSocketClient *client) {
    client->writeInt(value);
}

PropertyType IntProperty::getType() {
    return PropertyType::INT;
}

string IntProperty::toString() {
    return to_string(value);
}
