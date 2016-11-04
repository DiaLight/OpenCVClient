//
// Created by dialight on 03.11.16.
//

#ifndef OPENCVCLIENT_SELECTPROPERTY_HPP
#define OPENCVCLIENT_SELECTPROPERTY_HPP

#include <string>
#include <vector>
#include "Property.hpp"

using namespace std;

class SelectProperty : public Property {

    vector<string> *selections;
    int selected;
public:

    SelectProperty() = default;

    SelectProperty(vector<string> *selections, int selected);

    int getSelected();

    void read(TCPSocketClient *client) override;

    void write(TCPSocketClient *client) override;

    PropertyType getType() override;

    string toString() override;

    void updateFrom(Property *prop) override;
};


#endif //OPENCVCLIENT_SELECTPROPERTY_HPP
