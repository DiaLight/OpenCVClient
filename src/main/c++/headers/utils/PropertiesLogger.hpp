//
// Created by dialight on 15.01.17.
//

#ifndef OPENCVCLIENT_PROPERTIESLOGGER_HPP
#define OPENCVCLIENT_PROPERTIESLOGGER_HPP


#include <PropertiesListener.hpp>

class PropertiesLogger : public ::PropertiesListener {
public:
    void onNewProperty(std::string name, PropertyPointer property) override;
};

extern PropertiesLogger propertiesLogger;

#endif //OPENCVCLIENT_PROPERTIESLOGGER_HPP
