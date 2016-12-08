//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_IOEXCEPTION_HPP
#define OPENCVCLIENT_IOEXCEPTION_HPP


#include "RuntimeException.hpp"

class IOException : public RuntimeException {

public:
    IOException(const std::string &exception, bool silent = false);

    virtual ~IOException();

};


#endif //OPENCVCLIENT_IOEXCEPTION_HPP
