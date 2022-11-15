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

private:
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
};

}   // End namespace modbus
}   // End namespace components
}   // End namespace osdev
