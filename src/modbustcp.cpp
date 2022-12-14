/*
 *  Copyright (c) 2022 Peter M. Groen
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */
#include "modbustcp.h"

using namespace osdev::components::modbus;

ModbusTcp::ModbusTcp(const ConnectionConfig &con_config)
    : m_host( con_config.getIpAddress() )
    , m_port( con_config.getPortNumber() )
{

}

bool ModbusTcp::Connect()
{
    if (m_host.empty() || m_port == 0)
        {
            LOG("Missing Host and Port");
            return false;
        }
        else
        {
            LOG("Found Proper Host %s and Port %d", m_host.c_str(), m_port);
        }

        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (!X_ISVALIDSOCKET(m_socket))
        {
            LOG("Error Opening Socket");
            return false;
        }
        else
        {
            LOG("Socket Opened Successfully");
        }

        struct timeval timeout
        {
        };
        timeout.tv_sec = 20; // after 20 seconds connect() will timeout
        timeout.tv_usec = 0;


        setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char *>(&timeout), sizeof(timeout));
        setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char *>(&timeout), sizeof(timeout));
        m_server.sin_family = AF_INET;
        m_server.sin_addr.s_addr = inet_addr(m_host.c_str());
        m_server.sin_port = htons(m_port);

        if (!X_ISCONNECTSUCCEED(connect(m_socket, reinterpret_cast<SOCKADDR *>(&m_server), sizeof(m_server))))
        {
            LOG("Connection Error");
            return false;
        }

        LOG("Connected");
        ModbusBase::setConnected( true );
        return true;
}

bool ModbusTcp::Close()
{
    X_CLOSE_SOCKET(m_socket);
    LOG("Socket Closed");
    ModbusBase::setConnected(false);
    return ModbusBase::getConnected();
}

int ModbusTcp::modbusReceive(uint8_t *buffer)
{
    return recv(m_socket, reinterpret_cast<char *>(buffer), MAX_MSG_LENGTH, 0);
}

int ModbusTcp::modbusSend(uint8_t *buffer, size_t length)
{
    uint32_t msg_id = ModbusBase::getMessageId();
    ModbusBase::setMessageId(msg_id++);
    return send(m_socket, reinterpret_cast<const char *>(buffer), static_cast<size_t>(length), 0);
}
