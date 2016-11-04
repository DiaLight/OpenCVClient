//
// Created by dialight on 03.11.16.
//

#include "network/properties/structures/IntProperty.hpp"

IntProperty::IntProperty() {

}

IntProperty::IntProperty(int defVal) : value(defVal) {

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

int IntProperty::get() {
    return value;
}

string IntProperty::toString() {
    return to_string(value);
}
