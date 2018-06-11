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
    
    function_pattern_t(const std::string& pattern_, const std::string& body_)
    : pattern(pattern_)
    , body(body_)
    {}

    function_pattern_t()
    : pattern()
    , body()
    {}
    
    bool operator== (const function_pattern_t& rhs) const {
        return this->pattern == rhs.pattern
            && this->body == rhs.body;
    }
    
};
struct function_t : ::util::class_identity<function_t,base_t> {
    std::string name;
    std::string arguments;
    std::vector<function_pattern_t> patterns;
    function_pattern_t default_pattern;
    util::enum_bitset<::sapphire::core::types::function_attribute> attributes;
    
    function_t(
          const std::string& name_
        , const std::string& arguments_
        , const std::vector<function_pattern_t>& patterns_
        , const function_pattern_t& default_pattern_
        , const util::enum_bitset<::sapphire::core::types::function_attribute>& attributes_
    )
    : name(name_)
    , arguments(arguments_)
    , patterns(patterns_)
    , default_pattern(default_pattern_)
    , attributes(attributes_)
    {}

    function_t()
    : name()
    , arguments()
    , patterns()
    , default_pattern()
    , attributes()
    {}
    
    bool operator== (const function_t& rhs) const {
        return this->name == rhs.name
            && this->arguments == rhs.arguments
            && this->attributes == rhs.attributes
            && this->default_pattern == rhs.default_pattern
            && this->patterns == rhs.patterns;
    }
};
}

BOOST_FUSION_ADAPT_STRUCT (
    sapphire::core::ast::function_pattern_t,
    (std::string, pattern),
    (std::string, body)
);

std::ostream& operator<<(std::ostream& os, const sapphire::core::ast::function_pattern_t& data) {
    os << " pattern: " << data.pattern << std::endl;
    os << " body: " << data.body << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const sapphire::core::ast::function_t& data) {
    os << "name: " << data.name << std::endl;
    os << "arguments: " << data.arguments << std::endl;
    os << "patterns" << std::endl;
    for(const auto& pattern : data.patterns)
        os << pattern << std::endl;
    os << "default_pattern" << std::endl;
    os << data.default_pattern << std::endl;
    return os;
}