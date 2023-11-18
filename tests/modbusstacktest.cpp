/****************************************************************
 * Copyright (c)2022 Peter M. Groen
 * This file is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 ****************************************************************/
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

#include "connectionconfig.h"
#include "modbus.h"
#include "request.h"

using namespace osdev::components::modbus;

TEST(ModbusStackTest, StackConnectRTU)
{
    // Setup the connection configuration
    ConnectionConfig oConfig;
    oConfig.setBaudRate(B9600);
    oConfig.setConnectionType(ConnectionConfig::E_CONNECTIONTYPE::SERIAL);
    oConfig.setDataBits(8);
    oConfig.setStopBits(1);
    oConfig.setFrameTimeout(10);
    oConfig.setParity(ConnectionConfig::E_PARITY::NONE);
    oConfig.setPortName("/dev/ttyUSB0");

    // Create the modbus-stack..
    ModBus oModbus;
    EXPECT_EQ(oModbus.Open(oConfig), true);
    
    // Create a request to read the Temperature from a physical device XY-MD02
    Request request(Request::FunctionCode::FC_READ_HOLDING_REGISTERS, 
                    1, 
                    0x0001, 
                    2, 
                    [](Response response) mutable
                    {
                        std::cout << "Result: " << response.resultValue << std::endl;
                        return true;
                    });

    // Send the request
    Response response = oModbus.SendRequest(request);
}
