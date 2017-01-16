//
// Created by dialight on 15.01.17.
//

#include "utils/PropertiesLogger.hpp"
#include <iostream>
using namespace std;

PropertiesLogger propertiesLogger;

void PropertiesLogger::onNewProperty(std::string name, PropertyPointer property) {
    cout << "prop: " << name << " = " << property->toString() << endl;
}
