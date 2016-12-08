//
// Created by dialight on 03.11.16.
//

#ifndef OPENCVCLIENT_INTPROPERTY_HPP
#define OPENCVCLIENT_INTPROPERTY_HPP


#include "Property.hpp"

class IntProperty : public Property {

    int value;
public:
    IntProperty() = default;
    IntProperty(int defVal);

    int get();

    void updateFrom(PropertyPointer prop) override;

    PropertyType getType() override;

    void deserialize(DataStream *ds) override;
    void serialize(DataStream *ds) override;

    std::string toString() override;

};


#endif //OPENCVCLIENT_INTPROPERTY_HPP
