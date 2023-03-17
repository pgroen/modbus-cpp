/*
 *  Copyright (c) 2023 Peter M. Groen
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "imodbus.h"
#include "modbusbase.h"
#include <memory>

namespace osdev {
namespace components {
namespace modbus {

class ModBus : public IModBus
{
public:
    /// Default CTor
    ModBus();

    /// Default DTor
    virtual ~ModBus();

    // Implementation of IModBus
    virtual bool Open(const ConnectionConfig &connection_config) override;
    virtual bool Close() override;
    virtual Response SendRequest(const Request &request) override;

private:
    std::unique_ptr<ModbusBase> m_modbus = nullptr;
};

}   /* End namespace modbus */
}   /* End namespace components */
}   /* End namespace osdev */
