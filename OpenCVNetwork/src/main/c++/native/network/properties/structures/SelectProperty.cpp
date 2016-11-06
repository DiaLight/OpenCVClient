//
// Created by dialight on 03.11.16.
//

#include <iostream>
#include <sstream>
#include "network/properties/structures/SelectProperty.hpp"

SelectProperty::SelectProperty(vector<string> *selections, int selected) : selections(selections), selected(selected) {
}

void SelectProperty::updateFrom(Property *prop) {
    this->selected = ((SelectProperty *) prop)->selected;
}

int SelectProperty::getSelected() {
    return selected;
}

void SelectProperty::read(TCPSocketClient *client) {
    selected = client->readByte();
}

void SelectProperty::write(TCPSocketClient *client) {
    client->writeByte((int) selections->size());
    for(auto const& value: *selections) {
        client->writeUTF(value);
    }
    client->writeByte(selected);
}

PropertyType SelectProperty::getType() {
    return PropertyType::SELECT;
}

string SelectProperty::toString() {
    stringstream ss;
    ss << "selected=" << selected << ", ";
    if(selections == nullptr || selections->empty()) {
        ss << "[]";
    } else {
        ss << "[";
        auto it = selections->begin();
        ss << *it;
        it++;
        for(; it != selections->end(); ++it) {
            ss << ", " << *it;
        }
        ss << "]";
    }
    return ss.str();
}
