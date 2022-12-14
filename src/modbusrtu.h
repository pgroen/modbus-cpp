/*
 *  Copyright (c) 2022 Peter M. Groen
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */

#include "modbusbase.h"

namespace osdev {
namespace components {
namespace modbus {

class ModbusRtu : public ModbusBase
{
public:
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

};

}   /* End namespace modbus */
}   /* End namespace components */
}   /* End namespace osdev */
