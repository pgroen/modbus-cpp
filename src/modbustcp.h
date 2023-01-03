/*
 *  Copyright (c) 2022 Peter M. Groen
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "modbusbase.h"
#include "connectionconfig.h"

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace osdev {
namespace components {
namespace modbus {

using X_SOCKET = int;
using SOCKADDR = struct sockaddr;
using SOCKADDR_IN = struct sockaddr_in;

#define MAX_MSG_LENGTH 260

class ModbusTcp : public ModbusBase
{
public:
    explicit ModbusTcp(const ConnectionConfig &con_config);
    virtual ~ModbusTcp() {}

    virtual bool Connect() override;
    virtual bool Close() override;

    /*!
     * \brief modbusSend
     * \param to_send
     * \param length
     * \return
     */
    virtual int modbusSend(uint8_t *to_send, size_t length) override;

    /*!
     * \brief modbusReceive
     * \param buffer
     * \return
     */
    virtual int modbusReceive(uint8_t *buffer) override;

private:
    std::string     m_host {"127.0.0.1"};
    uint16_t        m_port {502};
    X_SOCKET        m_socket {-1};
    SOCKADDR_IN     m_server {};

};

}   /* End namespace modbus */
}   /* End namespace components */
}   /* End namespace osdev */
