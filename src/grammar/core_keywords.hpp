#pragma once
#include <boost/spirit/include/qi_symbols.hpp>

namespace sapphire::core::parser::keyword {

namespace detail {
struct keyword : public boost::spirit::qi::symbols<> {
    keyword(const std::string& keyword) {
        add(keyword);
    }
};
}

const auto colon = detail::keyword(":");
const auto semicolon = detail::keyword(";"); // end of sentence
const auto dni = detail::keyword(":=");      // declare and initialize
const auto assign = detail::keyword("=");    // assign to variable
const auto lrb = detail::keyword("(");       // left round bracket
const auto rrb = detail::keyword(")");       // right round bracket
const auto lb = detail::keyword("[");        // left square bracket
const auto rb = detail::keyword("]");        // right square bracket
const auto lcb = detail::keyword("{");       // left curly brace
const auto rcb = detail::keyword("}");       // right curly brace
const auto pipe = detail::keyword("|");
}