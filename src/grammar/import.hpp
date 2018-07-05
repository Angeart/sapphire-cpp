#pragma once
#include "ast/import.h"
#include "skipper.hpp"
#include "identify.hpp"
#include "core_keywords.hpp"
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <string>
#include <tuple>

namespace sapphire::core::parser {
template<class iterator>
class import : public boost::spirit::qi::grammar<iterator, ::sapphire::core::ast::import_t()> {
    public:
        import() : import::base_type(root) {
            namespace qi = boost::spirit::qi;
            namespace ph = boost::phoenix;
            using ::sapphire::core::ast::import_t;
            separated_str = (identifier % (keyword::comma >> skip));
            root =
            (
                qi::omit[qi::lit("import")]
                >> one_skip
                >> (
                (
                    separated_str[(&qi::_val)->*&import_t::functions = qi::_1]
                    >> one_skip
                    >> qi::lit("of")
                    >> one_skip
                    >> separated_str[(&qi::_val)->*&import_t::modules = qi::_1]
                )
                | separated_str[(&qi::_val)->*&import_t::modules = qi::_1][ph::clear((&qi::_val)->*&import_t::functions)]
                )
                >> skip
                >> qi::omit[keyword::semicolon]
            );
        }
    private:
        skipper<iterator> skip;
        one_skipper<iterator> one_skip;
        identify<iterator> identifier;
        boost::spirit::qi::rule<iterator, std::vector<std::string>()> separated_str;
        boost::spirit::qi::rule<iterator, ::sapphire::core::ast::import_t()> root;
};
}