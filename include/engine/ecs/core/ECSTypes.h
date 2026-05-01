#ifndef ECS_TYPES_H
#define ECS_TYPES_H

#pragma once

#include <bitset>

const unsigned int MAX_ENTITIES = 100000;
const unsigned short MAX_COMPONENTS = 1024;
const unsigned short MAX_SYSTEMS = 256;

using EntityId = unsigned int;
using ComponentId = unsigned short;
using Index = size_t;
using Signature = std::bitset<MAX_COMPONENTS>;
using Priority = unsigned char;

namespace SystemPriority {
    constexpr Priority CRITICAL = 0;
    constexpr Priority VERY_HIGH = 32;
    constexpr Priority HIGH = 64;
    constexpr Priority MEDIUM = 128;
    constexpr Priority LOW = 192;
    constexpr Priority VERY_LOW = 212;
    constexpr Priority NONE = 255;
}

#endif //ECS_TYPES_H