#pragma once
#include <cstdint>
namespace sapphire::core::types {
enum class function_attribute : uint32_t {
    standard,
    patterned,
    unnamed,
    generic
};
}