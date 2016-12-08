//
// Created by dialight on 03.11.16.
//

#include <iostream>
#include <sstream>
#include <map>
#include <structures/SelectProperty.hpp>

using namespace std;

SelectProperty::SelectProperty(map<int, string> *selections, int selected) : selections(selections), selected(selected) {

}

void SelectProperty::updateFrom(Property *prop) {
    this->selected = ((SelectProperty *) prop)->selected;
}

int SelectProperty::getSelected() {
    return selected;
}

void SelectProperty::deserialize(DataStream *ds) {
    selected = ds->readByte();
}

void SelectProperty::serialize(DataStream *ds) {
    ds->writeByte((int) selections->size());
    for(auto it = selections->begin(); it != selections->end(); it++) {
        ds->writeByte(it->first);
        ds->writeUTF(it->second);
    }
    ds->writeByte(selected);
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
        ss << "[" << it->first << ", " << it->second << "]";
        it++;
        for(; it != selections->end(); ++it) {
            ss << ", [" << it->first << ", " << it->second << "]";
        }
        ss << "]";
    }
    return ss.str();
}
