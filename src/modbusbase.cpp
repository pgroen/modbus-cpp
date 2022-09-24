/*
 *  Copyright (c) 2022 Peter M. Groen
 *  
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */

#include "modbusbase.h"

int ModbusBase::readCoils(uint16_t address, uint16_t amount, bool *buffer)
{

}

int ModbusBase::readInputBits(uint16_t address, uint16_t amount, bool *buffer)
{

}

int ModbusBase::readHoldingRegisters(uint16_t address, uitn16_t amount, uint16_t *buffer)
{

}

int ModbusBase::readInputRegisters(uint16_t address, uint16_t amount, uint16_t *buffer)
{

}

int ModbusBase::writeCoil(uint16_t address, const bool &to_write)
{

}

int ModbusBase::writeRegister(uint16_t address, const uint16_t &value)
{

}

int ModbusBase::writeCoils(uint16_t address, uint16_t amount, const bool *value)
{

}

int ModbusBase::writeRegisters(uint16_t address, uint16_t amount, const uint16_t *value)
{

}

void ModbusBase::buildRequest(uint8_t *to_send, uint16_t address, int function_code) const
{
    to_send[0] = (uint8_t)(m_msg_id >> 8u);
    to_send[1] = (uint8_t)(m_msg_id & 0x00FFu);
    to_send[2] = 0;
    to_send[3] = 0;
    to_send[4] = 0;
    to_send[6] = (uint8_t)m_slaveId;
    to_send[7] = (uint8_t)function_code;
    to_send[8] = (uint8_t)(address >> 8u);
    to_send[9] = (uint8_t)(address & 0x00FFu);
}

int ModbusBase::modbusRead(uint16_t address, uint16_t amount, int function_code)
{
    // TODO: Building the frames should be dependant on the chosen transport layer.. ( 256 for RTU, 260 for TCP )
    // Declare as pure virtual and implement in the transport-specific class? 
    // For now we focus on TCP as it is easier to implement.
    uint8_t to_send[12];
    buildRequest(to_send, address, function_code);
    to_send[5] = 6;
    to_send[10] = (uint8_t)
    }
}

int ModbusBase::modbusWrite(uint16_t address, uint16_t amount, int function_code, const uint16_t *value)
{
    // TODO: Building the frames should be dependant on the chosen transport layer.. ( 256 for RTU, 260 for TCP )
    // Declare as pure virtual and implement in the transport-specific class? 
    // For now we focus on TCP as it is easier to implement.
    int status = 0;
    uint8_t *to_send;

    switch (function_code)
    {
        // Intentionally fall-through
        case WRITE_COIL:
        case WRITE_REG:
        {
            to_send = new uint8_t[12];
            buildRequest(to_send, address, function_code);
            to_send[5] = 6;
            to_send[10] = (uint8_t)(value[0] >> 8u);
            to_send[11] = (uint8_t)(value[0] & 0x00FFu);
            status = modbusSend(to_send, 12);
            break;
        }
        case WRITE_REGS:
        {
            to_send = new uint8_t[13 + 2 * amount];
            buildRequest(to_send, address, function_code);
            to_send[5] = (uint8_t)(7 + 2 * amount);
            to_send[10] = (uint8_t)(amount >> 8u);
            to_send[11] = (uint8_t)(amount & 0x00FFu);
            to_send[12] = (uint8_t)(2 * amount);
            for (int i = 0; i < amount; i++)
            {
                to_send[13 + 2 * i] = (uint8_t)(value[i] >> 8u);
                to_send[14 + 2 * i] = (uint8_t)(value[i] & 0x00FFu);
            }
            status = modbusSend(to_send, 13 + 2 * amount);
            break;
        }
        case WRITE_COILS:
        {
            to_send = new uint8_t[14 + ( amount - 1 ) / 8];
            buildRequest(to_send, address, function_code);
            to_send[5] = (uint8_t)(7 + ( amount + 7 ) / 8);
            to_send[10] = (uint8_t)(amount >> 8u);
            to_send[11] = (uint8_t)(amount & 0x00FFu);
            to_send[12] = (uint8_t)((amount + 7) / 8);
            for (int i = 0; i < (amount + 7) / 8; i++)
            {
                to_send[13 + i] = 0     // Init needed before summing.
            }
            for (int i = 0; i < amount; i++)
            {
                to_send[13 + i / 8] += (uint8_t)(value[i] << (i % 8u));
            }
            status = modbusSend(to_send, 13 + (amount - 1) / 8);
        }
    }
    delete[] to_send;
    return status;
}

ssize_t ModbusBase::modbusSend(uint8_t *to_send, size_t length)
{

}

ssize_t ModbusBase::modbusReceive(uint8_t *buffer) const
{

}

void ModbusBase::modbusErrorHandle(const uint8_t *msg, int function_code)
{

}

void ModbusBase::setBadConnection()
{

}

void ModbusBase::setBadInput()
{

}

