//
// Created by dialight on 06.12.16.
//

#include <structures/IntProperty.hpp>
#include <structures/DoubleProperty.hpp>
#include <structures/SelectProperty.hpp>
#include "Properties.hpp"

using namespace std;
using namespace cv;

Properties props;

int Properties::getInt(const string& name, int defVal) {
    auto it = all.find(name);
    if (it != all.end()) return ((IntProperty *) it->second)->get();
    PropertyPointer prop = new IntProperty(defVal);
    all.insert(pair<string, PropertyPointer>(name, prop));
    for(auto l : newPropertyListeners) l->onNewProperty(name, prop);
//    AddPropertyPacket pa(name, prop);
//    trySendPacket(&pa);
    return defVal;
}

double Properties::getDouble(const string& name, double defVal) {
    auto it = all.find(name);
    if (it != all.end()) return ((DoubleProperty *) it->second)->get();
    PropertyPointer prop = new DoubleProperty(defVal);
    all.insert(pair<string, PropertyPointer>(name, prop));
    for(auto l : newPropertyListeners) l->onNewProperty(name, prop);
//    AddPropertyPacket pa(name, prop);
//    trySendPacket(&pa);
    return defVal;
}

int Properties::getSelect(const string &name, map<int, string> *values, int defVal) {
    auto it = all.find(name);
    if (it != all.end()) return ((SelectProperty *) it->second)->getSelected();
    PropertyPointer prop = new SelectProperty(values, defVal);
    all.insert(pair<string, PropertyPointer>(name, prop));
    for(auto l : newPropertyListeners) l->onNewProperty(name, prop);
//    AddPropertyPacket pa(name, prop);
//    trySendPacket(&pa);
    return defVal;
}

Properties::~Properties() {
    for(auto iterator = all.begin(); iterator != all.end(); iterator++) {
        delete iterator->second;
    }
}

PropertyPointer Properties::getProperty(string key) {
    auto it = all.find(key);
    if (it != all.end()) {
        return it->second;
    }
    return nullptr;
}
