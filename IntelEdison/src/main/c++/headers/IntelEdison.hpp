//
// Created by dialight on 17.12.16.
//

#ifndef OPENCVCLIENT_INTELEDISON_HPP
#define OPENCVCLIENT_INTELEDISON_HPP

#include <iostream>
// TODO: C - like library. Use #include <fstream> instead
#include <fcntl.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <string.h>

using namespace std;

class IntelEdison {
    int uart0_filestream;
public:
    IntelEdison();

    void receive();

    void transmit();
};


#endif //OPENCVCLIENT_INTELEDISON_HPP
