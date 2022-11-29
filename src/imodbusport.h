/*
 *  Copyright (c) 2022 Peter M. Groen
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "connectionconfig.h"
#include <vector>

namespace osdev {
namespace components {
namespace modbus {

class IModbusPort
{
public:
    IModbusPort(const ConnectionConfig &con_config);
    virtual ~IModbusPort() {}

    // The standard device interface.
    virtual bool Open() const = 0;
    virtual bool Close() const = 0;
    virtual int Read(uint8_t *buffer) const = 0;
    virtual int Write(uint8_t *buffer, size_t length) const = 0;
};

}   /* End namespace modbus */
}   /* End namespace components */
}   /* End namespace osdev */
