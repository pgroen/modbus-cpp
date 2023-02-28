/*
 *  Copyright (c) 2023 Peter M. Groen
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <cstdint>
#include <functional>
#include <variant>
#include <vector>

namespace osdev {
namespace components {
namespace modbus {

/// The response based on the \ref Request made.
struct Response
{
    /// Whether the \ref Request was successful.
    /// Positive values indicate success and how many entries are in the \ref responseBuffer.
    /// Negative values indicate failure and can be resolved with \ref Modbus::ErrorToString() to a string.
    int resultValue = -1;

    /// Buffer contaiining the response of the \ref Request.
    std::vector<std::variant<uint8_t, uint16_t>> responseBuffer = {};
};

/// A request to be made over ModBus.
///
/// TThis contains all the information the stack needs to actually make the request.
class Request
{
public:
    /// Function code of the request.
    /// We only support a small subset of the ModBus Standard.
    enum class FunctionCode
    {
        FC_UNKNOWN,
        FC_READ_COILS,
        FC_READ_DISCRETE_INPUTS,
        FC_READ_HOLDING_REGISTERS,
        FC_READ_INPUT_REGISTERS,
        FC_WRITE_SINGLE_COIL,
        FC_WRITE_SINGLE_REGISTER,
        FC_WRITE_MULTIPLE_COILS,
        FC_WRITE_MULTIPLE_REGISTERS,
        FC_READ_FILE_RECORD,
        FC_WRITE_FILE_RECORD,
    };

    explicit Request()
        : m_functionCode(Request::FunctionCode::FC_UNKNOWN)
        , m_slaveId(0)
        , m_startAddress(0x00)
        , m_numberOfRegisters(0x00)
    {}

    /// Constructor taking all necessary information to create a request.
    ///
    /// @param  functionCode    - The code of the action this request wants to perform.
    /// @param  slaveId         - The Device ID number.
    /// @param  startAddress    - Register number to start reading from or writing to.
    /// @param  numberOfItems   - Number of items to read or write from start_address.
    /// @param  callback        - Function to call when this request returns a response.
    Request(Request::FunctionCode function_code,
            int slave_id,
            int start_address,
            int num_of_regs,
            std::function<bool(Response)> callback)
        : m_functionCode(function_code)
        , m_slaveId(slave_id)
        , m_startAddress(start_address)
        , m_numberOfRegisters(num_of_regs)
    {
        callbacks.push_back(callback);
    }

    // Begin Getters and setters.
    /// Sets the functioncode for this request
    /// @param  function_code - The functioncode enum.
    void setFunctionCode(FunctionCode function_code) {m_functionCode = function_code;}

    /// @return The functioncode this request handles.
    FunctionCode getFunctionCode() const {return m_functionCode;}

    /// Sets the slaveId of the device this request is intended for.
    /// @param  slave_id - The slave Id of the device.
    void setSlaveId(const int slave_id) {m_slaveId = slave_id;}

    /// @return The slaveID of the device this request is intended for.
    uint8_t getSlaveId() const {return m_slaveId;}

    /// Sets the start address of the register(s) we want to read from.
    /// @param start_address - The start address
    void    setStartAddress(const uint8_t start_address) {m_startAddress = start_address;}

    /// @return The start Address of the register(s) we're reading.
    uint8_t getStartAddress() const {return m_startAddress;}

    /// Sets the number of registers we want to read from the start address.
    /// @param  num_of_regs - The number of registers to read from the start address
    void setNumberOfRegisters(const uint8_t num_of_regs) {m_numberOfRegisters = num_of_regs;}

    /// @return The number of registers we read from the \ref m_startAddress.
    uint8_t getNumberOfRegisters() const {return m_numberOfRegisters;}

    // End Getters and setters.

    /// @return The values read from, or to be written to, the device.
    /// @note never change the length of this vector.
    std::vector<uint8_t> getDataBuffer() const {return m_dataBuffer;}

private:
    /// Function code of this request.
    FunctionCode            m_functionCode = FunctionCode::FC_UNKNOWN;

    /// SlaveID of this request.
    uint8_t                 m_slaveId = 0;

    /// Start address of the register for this request
    uint8_t                 m_startAddress = 0x00;

    /// Amount of registers to read/write in this request
    uint8_t                 m_numberOfRegisters = 0x00;

    /// Data to send to the device; must be the same size as \ref m_numberOfItems.
    std::vector<uint8_t>    m_dataBuffer = {};

    /// @return Callbacks registered to call when new data is available.
    /// @note Functionn pointer returns False if the device state is OFFLINE. True, otherwise.
    std::vector<std::function<bool(Response)>> callbacks = {};
};

}   /* End namespace modbus */
}   /* End namespace components */
}   /* End namespace osdev */

