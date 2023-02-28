#include "modbus.h"

using namespace osdev::components::modbus;

ModBus::ModBus()
{
}

bool ModBus::Open(const ConnectionConfig &connection_config)
{
    switch(connection_config.getConnectionType())
    {
        case ConnectionConfig::E_CONNECTIONTYPE::SERIAL:
            break;
        case ConnectionConfig::E_CONNECTIONTYPE::TCP:
            break;
        case ConnectionConfig::E_CONNECTIONTYPE::UNKNOWN:
            break;
    }

    return true;
}

bool ModBus::Close()
{
    return true;
}

std::vector<uint8_t> ModBus::Read(const Request &request)
{
    std::vector<uint8_t> vecResult;

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

    return vecResult;
}

std::vector<uint8_t> ModBus::Write(const Request &request)
{
    (void)request;

    return std::vector<uint8_t>();
}
