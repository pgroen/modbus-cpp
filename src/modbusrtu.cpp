/*
 *  Copyright (c) 2022 Peter M. Groen
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */

#include "modbusrtu.h"

#include <stdio.h>

// Linux headers
#include <fcntl.h>      // Contains file controls like O_RDWR
#include <errno.h>      // Error integer and strerror() function
#include <termios.h>    // Contains POSIX terminal control definitions
#include <unistd.h>     // write(), read(), close()

using namespace osdev::components::modbus;

ModbusRtu::ModbusRtu( const ConnectionConfig &conf )
    : m_conConfig( conf )
    , m_socket( -1 )
{
}

bool ModbusRtu::Connect()
{
    m_socket = open( m_conConfig.getPortName().c_str(), O_RDWR);
    if(m_socket == -1)
    {
        return false;
    }

    struct termios l_tty;

    // Read in existing settings, and handle any error
    if( tcgetattr(m_socket, &l_tty) != 0 )
    {
        // Replace later on with a logger line.
        return false;
    }

    /* Control modes */
    l_tty.c_cflag &= ~PARENB;                   // Clear parity bit, disabling parity (most common)
    l_tty.c_cflag &= ~CSTOPB;                   // Clear stop field, only one stop bit used in communication (most common)
    l_tty.c_cflag &= ~CSIZE;                    // Clear all bits that set the data field
    l_tty.c_cflag |= CS8;                       // 8 bits per byte (most common)
    l_tty.c_cflag &= ~CRTSCTS;                  // Disable RTS / CTS hardware flow control (most common)
    l_tty.c_cflag |= CREAD | CLOCAL;            // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    /* local modes */
    l_tty.c_lflag &= ~ICANON;                   // Something, something CANONICAL.. Something, something Dark Side....
    l_tty.c_lflag &= ~ECHO;                     // Disable echo
    l_tty.c_lflag &= ~ECHOE;                    // Disable Erasure
    l_tty.c_lflag &= ~ECHONL;                   // Diasble new-line echo
    l_tty.c_lflag &= ~ISIG;                     // Disable interpretation of INTS, QUIT and SUSP
    l_tty.c_lflag &= ~(IXON | IXOFF | IXANY );  // Turn off s/w flow control

    /* Ouput modes */
    l_tty.c_oflag &= ~OPOST;                    // Prevent special interpretation of output bytes (e.g. newline chars)
    l_tty.c_oflag &= ~ONLCR;                    // Prevent conversion of newline to carriage return/line feed

    // Wait for up to 1 seconds ( 10 deciseconds), returning as soon as any data is received.
    l_tty.c_cc[VTIME] = 10;
    l_tty.c_cc[VMIN] = 0;

    // Set the read and write baudrate.
    cfsetispeed(&l_tty, m_conConfig.getBaudRate());
    cfsetospeed(&l_tty, m_conConfig.getBaudRate());

    // Save the tty settings.
    if( tcsetattr(m_socket, TCSANOW, &l_tty) != 0 )
    {
        Close();
        return false;
    }

    return true;
}

bool ModbusRtu::Close()
{
    if( close(m_socket) != 0 )
    {
        return false;
    }
    return true;
}

int ModbusRtu::modbusSend(uint8_t *to_send, size_t length)
{
    return write(m_socket, to_send, length);

}

int ModbusRtu::modbusReceive(uint8_t *buffer)
{
    return read(m_socket, buffer, sizeof(*buffer));
}
