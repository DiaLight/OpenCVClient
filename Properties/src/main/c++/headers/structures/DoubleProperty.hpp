//
// Created by dialight on 03.11.16.
//

#ifndef OPENCVCLIENT_DOUBLEPROPERTY_HPP
#define OPENCVCLIENT_DOUBLEPROPERTY_HPP

#include "Property.hpp"

class DoubleProperty : public Property {

    double value;
public:
    DoubleProperty() = default;
    DoubleProperty(double value);

    double get();

    void updateFrom(PropertyPointer prop) override;

    PropertyType getType() override;

    void deserialize(DataStream *ds) override;
    void serialize(DataStream *ds) override;

    std::string toString() override;

};


#endif //OPENCVCLIENT_DOUBLEPROPERTY_HPP
