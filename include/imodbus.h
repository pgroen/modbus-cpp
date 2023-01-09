/*
 *  Copyright (c) 2022 Peter M. Groen
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "request.h"
#include "connectionconfig.h"
#include <vector>

namespace osdev {
namespace components {
namespace modbus {

class IModBus
{
public:
    virtual ~IModBus() {}

    virtual bool Open(const ConnectionConfig &connection_config) = 0;
    virtual bool Close() = 0;
    virtual std::vector<uint8_t> Read(const Request &request) = 0;
    virtual std::vector<uint8_t> Write(const Request &request) = 0;
};

}   /* End namespace modbus */
}   /* End namespace components */
}   /* End namespace osdev */
