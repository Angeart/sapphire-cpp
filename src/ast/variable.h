#pragma once
#include "base.h"
#include "types/variable_attribute.h"

SAPPHIRE_AST_DEF(variable_t,
    (::sapphire::core::types::variable_attribute, attribute),
    (std::string, name),
    (std::string, type),
    (std::string, initializer)
)
