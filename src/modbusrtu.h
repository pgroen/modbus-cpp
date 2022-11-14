/*
 *  Copyright (c) 2022 Peter M. Groen
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "modbusbase.h"

namespace osdev {
namespace components {
namespace modbus {

class ModbusRTU : public ModbusBase
{
public:
    ModbusRTU();
};

}   // End namespace modbus
}   // End namespace components
}   // End namespace osdev
