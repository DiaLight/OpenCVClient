//
// Created by dialight on 31.10.16.
//

#include "network/exceptions/RuntimeException.hpp"
#include <iostream>

using namespace std;

RuntimeException::RuntimeException(const string &exception, bool silent) : exception(exception), silent(silent) {

}

RuntimeException::~RuntimeException() {

}

void RuntimeException::printError() {
    if(silent) return;
    cerr << exception << endl;
}
