//
// Created by dialight on 31.10.16.
//

#ifndef OPENCVCLIENT_RUNTIMEEXCEPTION_HPP
#define OPENCVCLIENT_RUNTIMEEXCEPTION_HPP

#include <string>

class RuntimeException {
    bool silent;
    std::string exception;
protected:

public:
    RuntimeException(const std::string &exception, bool silent = false);

    //RuntimeException(const RuntimeException&) = delete; //deleted copy constructor
    RuntimeException& operator=(const RuntimeException &) = delete; //deleted copy assignment operato

    virtual ~RuntimeException();

    void printError();
};


#endif //OPENCVCLIENT_RUNTIMEEXCEPTION_HPP
