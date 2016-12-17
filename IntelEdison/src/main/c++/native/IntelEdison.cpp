//
// Created by dialight on 17.12.16.
//

#include <IntelEdison.hpp>

IntelEdison::IntelEdison() {
    uart0_filestream = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart0_filestream == -1) {
        cout << "Error - Unable to open UART. " << strerror(errno) << endl;
    }

    //CONFIGURE THE UART
    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);
}

void IntelEdison::receive() {
    //----- CHECK FOR ANY RX BYTES -----
    // Read up to 255 characters from the port if they are there
    unsigned char rx_buffer[256];
    //Filestream, buffer to store in, number of bytes to read (max)
    ssize_t rx_length = read(uart0_filestream, (void*)rx_buffer, 255);
    if (rx_length < 0) { //An error occured (will occur if there are no bytes)
        cerr << "ERROR on receiving. " << strerror(errno) << endl;
    } else if (rx_length == 0) {
        //No data waiting
    } else {
        //Bytes received
        rx_buffer[rx_length] = '\0';
        cout << rx_length << " bytes read : " << rx_buffer << endl;
    }
}

void IntelEdison::transmit() {
    //---- TX BYTES ----
    unsigned char tx_buffer[20];
    unsigned char *p_tx_buffer;

    p_tx_buffer = &tx_buffer[0];
    *p_tx_buffer++ = 'h';
    *p_tx_buffer++ = 'e';
    *p_tx_buffer++ = 'l';
    *p_tx_buffer++ = 'l';
    *p_tx_buffer++ = 'o';

    ssize_t count = write(uart0_filestream, tx_buffer, (p_tx_buffer - tx_buffer));
    if (count < 0) {
        cerr << "ERROR on transmit. " << strerror(errno) << endl;
    }
}
