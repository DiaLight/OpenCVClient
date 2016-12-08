//
// Created by dialight on 31.10.16.
//

#include "network/exceptions/IOException.hpp"

IOException::IOException(const std::string &exception, bool silent) : RuntimeException(exception, silent) {

}

IOException::~IOException() {

}

