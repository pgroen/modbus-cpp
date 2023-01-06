/****************************************************************
 * Copyright (c)2022 Peter M. Groen
 * This file is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 ****************************************************************/

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "request.h"

using namespace osdev::components::modbus;

TEST(RequestTest, RequestDefaults)
{
    Request oRequest;

    // Check for all the default values
    EXPECT_EQ(oRequest.getFunctionCode(), Request::FunctionCode::FC_UNKNOWN);
    EXPECT_EQ(oRequest.getSlaveId(), 0x00);
    EXPECT_EQ(oRequest.getStartAddress(), 0x00);
    EXPECT_EQ(oRequest.getNumberOfRegisters(), 0x00);

}

TEST(RequestTest, RequestSlaveId)
{
    Request oRequest;
    oRequest.setSlaveId(1);

    EXPECT_EQ(oRequest.getSlaveId(), 1);
}

TEST(RequestTest, RequestStartAddress)
{
    Request oRequest;
    oRequest.setStartAddress(0x04);

    EXPECT_EQ(oRequest.getStartAddress(), 0x04);
}

TEST(RequestTest, RequestNumberOfRegisters)
{
    Request oRequest;
    oRequest.setNumberOfRegisters(0x02);

    EXPECT_EQ(oRequest.getNumberOfRegisters(), 0x02);
}

TEST(RequestTest, RequestReadCoils)
{
    Request oRequest;
    oRequest.setFunctionCode(Request::FunctionCode::READ_COILS);

    EXPECT_EQ(oRequest.getFunctionCode(), Request::FunctionCode::READ_COILS);
}

TEST(RequestTest, RequestReadDiscreteInputs)
{
    Request oRequest;
    oRequest.setFunctionCode(Request::FunctionCode::READ_DISCRETE_INPUTS);

    EXPECT_EQ(oRequest.getFunctionCode(), Request::FunctionCode::READ_DISCRETE_INPUTS);
}

TEST(RequestTest, RequestReadHoldingRegisters)
{
    Request oRequest;
    oRequest.setFunctionCode(Request::FunctionCode::READ_HOLDING_REGISTERS);

    EXPECT_EQ(oRequest.getFunctionCode(), Request::FunctionCode::READ_HOLDING_REGISTERS);
}

TEST(RequestTest, RequestReadInputRegisters)
{
    Request oRequest;
    oRequest.setFunctionCode(Request::FunctionCode::READ_INPUT_REGISTERS);

    EXPECT_EQ(oRequest.getFunctionCode(), Request::FunctionCode::READ_INPUT_REGISTERS);
}

TEST(RequestTest, RequestWriteSingleCoil)
{
    Request oRequest;
    oRequest.setFunctionCode(Request::FunctionCode::WRITE_SINGLE_COIL);

    EXPECT_EQ(oRequest.getFunctionCode(), Request::FunctionCode::WRITE_SINGLE_COIL);
}

TEST(RequestTest, RequestWriteSingleRegister)
{
    Request oRequest;
    oRequest.setFunctionCode(Request::FunctionCode::WRITE_SINGLE_REGISTER);

    EXPECT_EQ(oRequest.getFunctionCode(), Request::FunctionCode::WRITE_SINGLE_REGISTER);
}

TEST(RequestTest, RequestWriteMultipleCoils)
{
    Request oRequest;
    oRequest.setFunctionCode(Request::FunctionCode::WRITE_MULTIPLE_COILS);

    EXPECT_EQ(oRequest.getFunctionCode(), Request::FunctionCode::WRITE_MULTIPLE_COILS);
}

TEST(RequestTest, RequestWriteMultipleRegisters)
{
    Request oRequest;
    oRequest.setFunctionCode(Request::FunctionCode::WRITE_MULTIPLE_REGISTERS);

    EXPECT_EQ(oRequest.getFunctionCode(), Request::FunctionCode::WRITE_MULTIPLE_REGISTERS);
}

TEST(RequestTest, RequestWriteFileRecord)
{
    Request oRequest;
    oRequest.setFunctionCode(Request::FunctionCode::WRITE_FILE_RECORD);

    EXPECT_EQ(oRequest.getFunctionCode(), Request::FunctionCode::WRITE_FILE_RECORD);
}
