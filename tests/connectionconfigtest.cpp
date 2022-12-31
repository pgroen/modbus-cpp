/****************************************************************
 * Copyright (c)2022 Peter M. Groen
 * This file is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 ****************************************************************/

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "connectionconfig.h"

using namespace osdev::components::modbus;

TEST(ConnectionConfigTest, SerialPortConfig)
{
    ConnectionConfig oConfig;
    oConfig.setBaudRate( B9600 );
    oConfig.setConnectionType( ConnectionConfig::E_CONNECTIONTYPE::SERIAL );
    oConfig.setDataBits( 8 );
    oConfig.setStopBits( 1 );
    oConfig.setFrameTimeout( 10 );
    oConfig.setParity( ConnectionConfig::E_PARITY::NONE );
    oConfig.setPortName( "/dev/ttyUSB0" );

    // Test all parameters
    EXPECT_EQ(oConfig.getBaudRate(), B9600);
    EXPECT_EQ(oConfig.getConnectionType(), ConnectionConfig::E_CONNECTIONTYPE::SERIAL);
    EXPECT_EQ(oConfig.getDataBits(), 8);
    EXPECT_EQ(oConfig.getStopBits(), 1);
    EXPECT_EQ(oConfig.getFrameTimeout(), 10);
    EXPECT_EQ(oConfig.getParity(), ConnectionConfig::E_PARITY::NONE);
    EXPECT_EQ(oConfig.getPortName(), "/dev/ttyUSB0");
}
