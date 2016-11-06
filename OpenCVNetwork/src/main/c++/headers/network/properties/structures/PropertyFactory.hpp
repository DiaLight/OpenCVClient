//
// Created by dialight on 03.11.16.
//

#ifndef OPENCVCLIENT_PROPERTYFACTORY_HPP
#define OPENCVCLIENT_PROPERTYFACTORY_HPP


#include "Property.hpp"
#include "IntProperty.hpp"
#include "DoubleProperty.hpp"
#include "SelectProperty.hpp"

namespace PropertyFactory {
    Property *newInstance(PropertyType type) {
        switch (type) {
            case INT:
                return new IntProperty();
            case DOUBLE:
                return new DoubleProperty();
            case SELECT:
                return new SelectProperty();
        }
        return nullptr;
    }
};


#endif //OPENCVCLIENT_PROPERTYFACTORY_HPP
