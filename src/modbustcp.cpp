/*
 *  Copyright (c) 2022 Peter M. Groen
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */
#include "modbustcp.h"

using namespace osdev::components::modbus;

ModbusTCP::ModbusTCP(const ConnectionConfig &port_configuration)
{

}

bool ModbusTCP::Connect()
{
    if(m_host.empty() || m_port == 0)
    {
        LOG("Missing host and port");
        return false;
    }

    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(!X_ISVALIDSOCKET(m_socket))
    {
        LOG("Errror Opening Socket");
        return false;
    }

    struct timeval timeout {};
    timeout.tv_sec  = 20;        // After 20 seconds connect() will timeout
    timeout.tv_usec = 0;

    setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char *>(&timeout), sizeof(timeout));
    setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char *>(&timeout), sizeof(timeout));
    m_server.sin_family = AF_INET;
    m_server.sin_addr.s_addr = inet_addr(m_host.c_str());
    m_server.sin_port = htons(m_port);

    if(!X_ISCONNECTSUCCEED(connect(m_socket, reinterpret_cast<SOCKADDR *>(&m_server), sizeof(m_server))))
    {
        LOG("Connection Error");
        return false;
    }

    ModbusBase::setConnected(true);
    return true;
}

void ModbusTCP::Close()
{

}

bool ModbusTCP::isConnected() const
{

}

ssize_t ModbusTCP::modbusSend(uint8_t *to_send, size_t length)
{

}

ssize_t ModbusTCP::modbusReceive(uint8_t *buffer) const
{

}
