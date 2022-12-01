/*
 *  Copyright (c) 2022 Peter M. Groen
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "imodbusport.h"

namespace osdev {
namespace components {
namespace modbus {

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
};

}   /* End namespace modbus */
}   /* End namespace components */
}   /* End namespace osdev */
