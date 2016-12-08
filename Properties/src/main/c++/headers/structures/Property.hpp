//
// Created by dialight on 03.11.16.
//

#ifndef OPENCVCLIENT_PROPERTY_HPP
#define OPENCVCLIENT_PROPERTY_HPP

#include <Serializable.hpp>

class Property;

enum PropertyType {
    INT,
    DOUBLE,
    SELECT
};

typedef Property *PropertyPointer;

class Property : public ::Serializable {
public:
    virtual void updateFrom(PropertyPointer prop) = 0;
    virtual PropertyType getType() = 0;
};


#endif //OPENCVCLIENT_PROPERTY_HPP
