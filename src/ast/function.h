#pragma once
#include "base.h"
#include "variable.h"
#include "util/enum_bitset.hpp"
#include "types/function_attribute.h"
#include <boost/dynamic_bitset.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <vector>

SAPPHIRE_AST_DEF(function_pattern_t,
    (std::string, pattern),
    (std::string, body)
)

SAPPHIRE_AST_DEF(function_t,
    (std::string, name),
    (std::vector<variable_t>, arguments),
    (std::vector<function_pattern_t>, patterns),
    (function_pattern_t, default_pattern),
    (util::enum_bitset<::sapphire::core::types::function_attribute>, attributes)
)
