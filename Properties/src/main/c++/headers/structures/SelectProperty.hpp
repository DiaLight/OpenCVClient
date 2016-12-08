//
// Created by dialight on 03.11.16.
//

#ifndef OPENCVCLIENT_SELECTPROPERTY_HPP
#define OPENCVCLIENT_SELECTPROPERTY_HPP

#include <string>
#include <map>
#include "Property.hpp"

class SelectProperty : public Property {

    std::map<int, std::string> *selections;
    int selected;
public:

    SelectProperty() = default;

    SelectProperty(std::map<int, std::string> *selections, int selected);

    int getSelected();

    void updateFrom(PropertyPointer prop) override;

    PropertyType getType() override;

    void deserialize(DataStream *ds) override;
    void serialize(DataStream *ds) override;

    std::string toString() override;
};


#endif //OPENCVCLIENT_SELECTPROPERTY_HPP
