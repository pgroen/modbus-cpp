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

#define X_ISVALIDSOCKET(s) ((s) >= 0)
#define X_CLOSE_SOCKET(s) close(s)
#define X_ISCONNECTSUCCEED(s) ((s) >= 0)

/*!
 * \brief The ModbusTCP class
 */
class ModbusTCP : public ModbusBase
{
public:
    /*!
     * \brief ModbusTCP
     * \param port_configuration
     */
    ModbusTCP(const ConnectionConfig &port_configuration);

    // Pure virtuals. Override when inherited.
    /*!
     * \brief Connect
     * \return
     */
    virtual bool Connect() override;

    /*!
     * \brief Close
     */
    virtual void Close() override;

private:    // Methods
    /*!
     * \brief modbusSend
     * \param to_send
     * \param length
     * \return
     */
    virtual ssize_t modbusSend(uint8_t *to_send, size_t length) override;

    /*!
     * \brief modbusReceive
     * \param buffer
     * \return
     */
    virtual ssize_t modbusReceive(uint8_t *buffer) const override;

private:    // Members
    uint16_t    m_port {};
    std::string m_host{};
    X_SOCKET    m_socket{};
    SOCKADDR_IN m_server{};
};

}   // End namespace modbus
}   // End namespace components
}   // End namespace osdev
