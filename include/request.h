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
        READ_COILS,
        READ_DISCRETE_INPUTS,
        READ_HOLDING_REGISTERS,
        READ_INPUT_REGISTERS,
        WRITE_SINGLE_COIL,
        WRITE_SINGLE_REGISTER,
        WRITE_MULTIPLE_COILS,
        WRITE_MULTIPLE_REGISTERS,
        WRITE_FILE_RECORD,
    };

    /// Constructor taking all necessary information to create a request.
    ///
    /// @param  functionCode    - The code of the action this request wants to perform.
    /// @param  slaveId         - The Device ID number.
    /// @param  startAddress    - Register number to start reading from or writing to.
    /// @param  numberOfItems   - Number of items to read or write from start_address.
    /// @param  callback        - Function to call when this request returns a response.
    Request(Request::FunctionCode functionCode,
            int slaveId,
            int startAddress,
            int numberOfItems,
            std::function<bool(Response)> callback)
        : m_functionCode(functionCode)
        , m_slaveId(slaveId)
        , m_startAddress(startAddress)
        , m_numberOfItems(numberOfItems)
    {
        callbacks.push_back(callback);
    }

    /// @return The functioncode this request handles.
    FunctionCode GetFunctionCode() const {return m_functionCode;}

    /// @return The slaveID of the device this request is intended for.
    int GetSlaveId() const {return m_slaveId;}

    /// @return The start Address of the register(s) we're reading.
    int GetStartAddress() const {return m_startAddress;}

    /// @return The number of registers we read from the \ref m_startAddress.
    int GetNumberOfItems() const {return m_numberOfItems;}

    /// @return The values read from, or to be written to, the device.
    /// @note never change the length of this vector.
    std::vector<int> GetDataBuffer() const {return m_dataBuffer;}

    /// @return Callbacks registered to call when new data is available.
    /// @note Functionn pointer returns False if the device state is OFFLINE. True, otherwise.
    std::vector<std::function<bool(Response)>> callbacks;

private:
    /// Function code of this request.
    FunctionCode    m_functionCode;

    /// SlaveID of this request.
    int             m_slaveId;

    /// Start address of the register for this request
    int             m_startAddress;

    /// Amount of registers to read/write in this request
    int             m_numberOfItems;

    /// Data to send to the device; must be the same size as \ref m_numberOfItems.
    std::vector<int>    m_dataBuffer;
};
