#pragma once
#include "base.h"
#include "util/enum_bitset.hpp"
#include "types/function_attribute.h"
#include <boost/dynamic_bitset.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <vector>

namespace sapphire::core::ast {
struct function_pattern_t : ::util::class_identity<function_pattern_t,base_t> {
    std::string pattern;
    std::string body;

    function_pattern_t()
    : pattern()
    , body()
    {}
};
struct function_t : ::util::class_identity<function_t,base_t> {
    std::string name;
    std::string arguments;
    std::vector<function_pattern_t> patterns;
    function_pattern_t default_pattern;
    util::enum_bitset<::sapphire::core::types::function_attribute> attributes;

    function_t()
    : name()
    , patterns()
    , default_pattern()
    , attributes()
    {}
};
}

BOOST_FUSION_ADAPT_STRUCT (
    sapphire::core::ast::function_pattern_t,
    (std::string, pattern),
    (std::string, body)
);