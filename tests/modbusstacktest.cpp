/****************************************************************
 * Copyright (c)2022 Peter M. Groen
 * This file is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 ****************************************************************/
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "connectionconfig.h"

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

}
