#include "modbus.h"
#include "modbusrtu.h"
#include "modbustcp.h"

using namespace osdev::components::modbus;

ModBus::ModBus()
{
}

ModBus::~ModBus()
{
    if(m_modbus)
    {
        m_modbus.reset(nullptr);
    }
}

bool ModBus::Open(const ConnectionConfig &connection_config)
{
    if(m_modbus == nullptr)
    {
        switch(connection_config.getConnectionType())
        {
            case ConnectionConfig::E_CONNECTIONTYPE::SERIAL:
            m_modbus = std::make_unique<ModbusRtu>(connection_config);
                break;
            case ConnectionConfig::E_CONNECTIONTYPE::TCP:
                m_modbus = std::make_unique<ModbusTcp>(connection_config);
                break;
            case ConnectionConfig::E_CONNECTIONTYPE::UNKNOWN:
                return false;
                break;
        }
    }

    if(m_modbus->isConnected())
    {
        m_modbus->Close();
    }

    return m_modbus->Connect();
}

bool ModBus::Close()
{
    if(m_modbus != nullptr)
    {
        m_modbus->Close();
    }
    return true;
}

Response ModBus::SendRequest(const Request &request)
{
    Response oResponse = {};
    std::vector<uint8_t>    uint8Buffer(static_cast<size_t>(request.getNumberOfRegisters()));
    std::vector<uint16_t>   uint16Buffer(static_cast<size_t>(request.getNumberOfRegisters()));


    switch(request.getFunctionCode())
    {
        case Request::FunctionCode::FC_UNKNOWN:
        {
            break;
        }
        case Request::FunctionCode::FC_READ_COILS:
        {
            // oResponse.resultValue = m_modbus->readCoils(request.getStartAddress(),request.getNumberOfRegisters(), boolBuffer.data());
            break;
        }
        case Request::FunctionCode::FC_READ_DISCRETE_INPUTS:
        {
            // oResponse.resultValue = m_modbus->readInputBits(request.getStartAddress(), request.getNumberOfRegisters(), boolBuffer.data());
            break;
        }
        case Request::FunctionCode::FC_READ_HOLDING_REGISTERS:
        {
            oResponse.resultValue = m_modbus->readHoldingRegisters(request.getStartAddress(), request.getNumberOfRegisters(), uint16Buffer.data());
            if (oResponse.resultValue == request.getNumberOfRegisters())
            {
                for(int index = 0; index < oResponse.resultValue; ++index)
                {
                    oResponse.responseBuffer.emplace_back(static_cast<uint16_t>(uint16Buffer[index]));
                }
            }
            break;
        }
        case Request::FunctionCode::FC_READ_INPUT_REGISTERS:
        {
            oResponse.resultValue = m_modbus->readInputRegisters(request.getStartAddress(), request.getNumberOfRegisters(), uint16Buffer.data());
            if (oResponse.resultValue == request.getNumberOfRegisters())
            {
                for(int index = 0; index < oResponse.resultValue; ++index)
                {
                    oResponse.responseBuffer.emplace_back(static_cast<uint16_t>(uint16Buffer[index]));
                }
            }
            break;
        }
        case Request::FunctionCode::FC_WRITE_SINGLE_COIL:
        case Request::FunctionCode::FC_WRITE_SINGLE_REGISTER:
        {
            oResponse.resultValue = m_modbus->writeCoil(request.getStartAddress(), request.getDataBuffer()[0]);
            break;
        }
        case Request::FunctionCode::FC_WRITE_MULTIPLE_COILS:
        {
            // const auto buffer = std
            break;
        }
        case Request::FunctionCode::FC_WRITE_MULTIPLE_REGISTERS:
        {
            break;
        }
        case Request::FunctionCode::FC_READ_FILE_RECORD:
        {
            // Not implemented (yet)
            break;
        }
        case Request::FunctionCode::FC_WRITE_FILE_RECORD:
        {
            // Not implemented (yet)
            break;
        }
    }

    return Response();
}
