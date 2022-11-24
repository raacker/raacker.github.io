#pragma once

#include <iostream>
#include "../CommProtocol/CommProtocol.h"

namespace TMIOSDP
{
    class Command
    {
    public:
        virtual ~Command(){};
        virtual Comm::Status Execute() = 0;
    };
}