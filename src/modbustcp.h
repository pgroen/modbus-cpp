/*
 *  Copyright (c) 2022 Peter M. Groen
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "imodbusport.h"

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

class ModbusTcp : public IModbusPort
{
public:
    explicit ModbusTcp(const ConnectionConfig &con_config);
    virtual ~ModbusTcp() {}

    // The standard device interface.
    // Implementation of IModbusPort
    virtual bool Open() const override;
    virtual bool Close() const override;
    virtual int Read(uint8_t *buffer) const override;
    virtual int Write(uint8_t *buffer, size_t length) const override;

private:
    uint16_t        m_port {502};
    std::string     m_host {};
    X_SOCKET        m_socket {-1};
    SOCKADDR_IN     m_server {};

};

}   /* End namespace modbus */
}   /* End namespace components */
}   /* End namespace osdev */
