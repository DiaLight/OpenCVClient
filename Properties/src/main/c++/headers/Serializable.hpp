//
// Created by dialight on 06.12.16.
//

#ifndef OPENCVCLIENT_SERIALIZABLE_HPP
#define OPENCVCLIENT_SERIALIZABLE_HPP

#include "DataStream.hpp"

class Serializable {

public:
    virtual void deserialize(DataStream *ds) = 0;
    virtual void serialize(DataStream *ds) = 0;
    virtual std::string toString() = 0;

};

#endif //OPENCVCLIENT_SERIALIZABLE_HPP
