#pragma once
#include "ast/import.h"
#include "identify.hpp"
#include "core_keywords.hpp"
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <string>
#include <tuple>

namespace sapphire::core::parser {
template<class iterator_t, class skipper_t>
class import : public boost::spirit::qi::grammar<iterator_t, skipper_t, ::sapphire::core::ast::import_t()> {
    public:
        import() : import::base_type(root) {
            namespace qi = boost::spirit::qi;
            namespace ph = boost::phoenix;
            using ::sapphire::core::ast::import_t;
            separated_str = (identifier % keyword::comma);
            root =
            (
                qi::omit[qi::lit("import")]
                >> (
                (
                    separated_str[(&qi::_val)->*&import_t::functions = qi::_1]
                    >> qi::lit("of")
                    >> identifier[ph::push_back((&qi::_val)->*&import_t::modules,qi::_1)]
                )
                | separated_str[(&qi::_val)->*&import_t::modules = qi::_1][ph::clear((&qi::_val)->*&import_t::functions)]
                )
            );
            // root.name("i:root");
            // qi::debug(root);
        }
    private:
        identify<iterator_t> identifier;
        boost::spirit::qi::rule<iterator_t, skipper_t, std::vector<std::string>()> separated_str;
        boost::spirit::qi::rule<iterator_t, skipper_t, ::sapphire::core::ast::import_t()> root;
};
}