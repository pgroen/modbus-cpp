/*
 *  Copyright (c) 2022 Peter M. Groen
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <string>

namespace osdev {
namespace components {
namespace modbus {

class ConnectionConfig
{
public:
    enum class E_CONNECTIONTYPE
    {
        SERIAL,
        TCP,
        UNKNOWN
    };

    enum class E_PARITY
    {
        ODD,
        EVEN,
        NONE
    };

    enum class E_BAUDRATE
    {
        R1200   = 1200,
        R2400   = 2400,
        R4800   = 4800,
        R9600   = 9600,
        R19200  = 19200,
        R38400  = 38400,
        R57600  = 57600,
        R76800  = 76800,
        R115200 = 115200
    };

    ConnectionConfig();

    // Getters and Setters
    void                setConnectionType( E_CONNECTIONTYPE type ) { m_conType = type; }
    E_CONNECTIONTYPE    getConnectionType() const { return m_conType; }

    void                setPortName(const std::string &port_name) { m_portName = port_name; }
    std::string         getPortName() { return m_portName; }

    void                setBaudRate( E_BAUDRATE baud_rate ) { m_baudRate = baud_rate; }
    E_BAUDRATE          getBaudRate() const { return m_baudRate; }

    void                setParity(E_PARITY parity) { m_parity = parity; }
    E_PARITY            getParity() const { return m_parity; }

    void                setDataBits(int data_bits) { m_dataBits = data_bits; }
    int                 getDataBits() const { return m_dataBits; }

    void                setStopBits(int stop_bits) { m_stopBits = stop_bits; }
    int                 getStopBits() const { return m_stopBits; }

    void                setIpAddress(const std::string &ip_address) { m_ipAddress = ip_address; }
    std::string         getIpAddress() const { return m_ipAddress; }

    void                setPortNumber(unsigned int port_number) { m_portNumber = port_number; }
    unsigned int        getPortNumber() const { return m_portNumber; }

    void                setFrameTimeout(int frame_timeout) { m_frameTimeOut = frame_timeout; }
    int                 getFrameTimeout() const { return m_frameTimeOut; }

private:
    E_CONNECTIONTYPE    m_conType  = E_CONNECTIONTYPE::UNKNOWN;
    std::string         m_portName;
    E_BAUDRATE          m_baudRate = E_BAUDRATE::R9600;
    E_PARITY            m_parity   = E_PARITY::NONE;
    int                 m_dataBits = 8;
    int                 m_stopBits = 1;
    std::string         m_ipAddress{};
    unsigned int        m_portNumber = 502;
    int                 m_frameTimeOut = -1;

};

}   // End namespace modbus
}   // End namespace components
}   // End namespace osdev
