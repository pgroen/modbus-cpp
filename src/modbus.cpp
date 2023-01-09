#include "modbus.h"

using namespace osdev::components::modbus;

ModBus::ModBus()
{

}

bool ModBus::Open(const ConnectionConfig &connection_config)
{
    (void)connection_config;

    return true;
}

bool ModBus::Close()
{
    return true;
}

std::vector<uint8_t> ModBus::Read(const Request &request)
{
    (void)request;

    return std::vector<uint8_t>();
}

std::vector<uint8_t> ModBus::Write(const Request &request)
{
    (void)request;

    return std::vector<uint8_t>();
}
