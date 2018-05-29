#pragma once
#include "base.h"
#include <string>

namespace sapphire::core::ast {
struct variable_t : ::util::class_identity<variable_t,base_t> {
    std::string attribute;
    std::string name;
    std::string type;
    std::string initializer;
};
}