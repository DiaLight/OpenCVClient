//
// Created by dialight on 03.11.16.
//

#include <structures/IntProperty.hpp>

IntProperty::IntProperty(int defVal) : value(defVal) {}

int IntProperty::get() {
    return value;
}

void IntProperty::updateFrom(Property *prop) {
    this->value = ((IntProperty *) prop)->value;
}

PropertyType IntProperty::getType() {
    return PropertyType::INT;
}

void IntProperty::deserialize(DataStream *ds) {
    value = ds->readInt();
}

void IntProperty::serialize(DataStream *ds) {
    ds->writeInt(value);
}

std::string IntProperty::toString() {
    return std::to_string(value);
}
