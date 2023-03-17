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

    if(m_modbus->getConnected())
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

    switch(request.getFunctionCode())
    {
        case Request::FunctionCode::FC_UNKNOWN:
            break;
        case Request::FunctionCode::FC_READ_COILS:
            break;
        case Request::FunctionCode::FC_READ_DISCRETE_INPUTS:
            break;
        case Request::FunctionCode::FC_READ_HOLDING_REGISTERS:
            break;
        case Request::FunctionCode::FC_READ_INPUT_REGISTERS:
            break;
        case Request::FunctionCode::FC_WRITE_SINGLE_COIL:
            break;
        case Request::FunctionCode::FC_WRITE_SINGLE_REGISTER:
            break;
        case Request::FunctionCode::FC_WRITE_MULTIPLE_COILS:
            break;
        case Request::FunctionCode::FC_WRITE_MULTIPLE_REGISTERS:
            break;
        case Request::FunctionCode::FC_READ_FILE_RECORD:
            break;
        case Request::FunctionCode::FC_WRITE_FILE_RECORD:
            break;
    }

    return Response;
}
