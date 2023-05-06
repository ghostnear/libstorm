#pragma once

#include "deps.hpp"
#include "math/all.hpp"
#include "system/all.hpp"
#include "prefabs/all.hpp"

namespace Storm
{
    int32_t StormInit();
    int32_t StormQuit(int32_t ret_val);

    int32_t StormMainLoop();
}
