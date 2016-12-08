//
// Created by dialight on 03.11.16.
//

#include <structures/DoubleProperty.hpp>

DoubleProperty::DoubleProperty(double value) : value(value) {}

double DoubleProperty::get() {
    return value;
}

void DoubleProperty::updateFrom(Property *prop) {
    this->value = ((DoubleProperty *) prop)->value;
}

PropertyType DoubleProperty::getType() {
    return PropertyType::DOUBLE;
}

void DoubleProperty::deserialize(DataStream *ds) {
    value = ds->readDouble();
}

void DoubleProperty::serialize(DataStream *ds) {
    ds->writeDouble(value);
}

std::string DoubleProperty::toString() {
    return std::to_string(value);
}
