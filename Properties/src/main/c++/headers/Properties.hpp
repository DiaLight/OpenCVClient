//
// Created by dialight on 06.12.16.
//

#ifndef OPENCVCLIENT_PROPERTIES_HPP
#define OPENCVCLIENT_PROPERTIES_HPP

#include <opencv2/opencv.hpp>
#include <structures/Property.hpp>
#include "PropertiesListener.hpp"

class Properties;

extern Properties props;

class Properties {

    std::vector<PropertiesListenerPointer> newPropertyListeners;
public:
    std::map<std::string, PropertyPointer> all;

    virtual ~Properties();

    int getInt(const std::string& name, int defVal);
    double getDouble(const std::string& name, double defVal);
    int getSelect(const std::string& name, std::map<int, std::string> *list, int def);

    void registerListener(PropertiesListenerPointer listener) {
        newPropertyListeners.push_back(listener);
    }

    PropertyPointer getProperty(std::string key);
};


#endif //OPENCVCLIENT_PROPERTIES_HPP
