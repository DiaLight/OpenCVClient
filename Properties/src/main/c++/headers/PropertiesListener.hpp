//
// Created by dialight on 08.12.16.
//

#ifndef OPENCVCLIENT_PROPERTIESLISTENER_HPP
#define OPENCVCLIENT_PROPERTIESLISTENER_HPP


#include <structures/Property.hpp>

class PropertiesListener;

typedef PropertiesListener *PropertiesListenerPointer;

class PropertiesListener {
public:
    virtual void onNewProperty(std::string name, PropertyPointer property) = 0;
};

#endif //OPENCVCLIENT_PROPERTIESLISTENER_HPP
