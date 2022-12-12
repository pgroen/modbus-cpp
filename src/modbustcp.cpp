/*
 *  Copyright (c) 2022 Peter M. Groen
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */
#include "modbustcp.h"

using namespace osdev::components::modbus;

ModbusTcp::ModbusTcp(const ConnectionConfig &con_config)

{

}

bool ModbusTcp::Connect()
{

}

bool ModbusTcp::Close()
{

}

int ModbusTcp::modbusReceive(uint8_t *buffer)
{
    return 0;
}

int ModbusTcp::modbusSend(uint8_t *buffer, size_t length)
{
    return 0;
}
