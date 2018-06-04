#pragma once
#include "ast/variable.h"
#include "skipper.hpp"
#include "identify.hpp"
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <string>
#include <tuple>

namespace sapphire::core{
namespace parser {
struct variable_attribute_rule_t : public boost::spirit::qi::symbols<char, ::sapphire::core::types::variable_attribute> {
    variable_attribute_rule_t() {
        namespace types = ::sapphire::core::types;
        add ("let", types::variable_attribute::let)
            ("lazy", types::variable_attribute::lazy)
            ("const", types::variable_attribute::constant)
        ;
    }
};
template<class iterator>
class variable : public boost::spirit::qi::grammar<iterator, ::sapphire::core::ast::variable_t()> {
    public:
        variable() : variable::base_type(root) {
            namespace qi = boost::spirit::qi;
            namespace ph = boost::phoenix;
            using ::sapphire::core::ast::variable_t;
            initializer =
            (
                qi::omit[qi::lit(":=")] >>
                skip >>
                (identifier[qi::_val = qi::_1])
            );
            type =
            (
                qi::omit[qi::lit(":")] >>
                skip >>
                (identifier[qi::_val = qi::_1])
            );
            root =
            (
                //deduced attribute variable
                (
                    identifier[(&qi::_val)->*&variable_t::name = qi::_1]
                    >> skip
                    >> -type[(&qi::_val)->*&variable_t::type = qi::_1]
                    >> initializer[(&qi::_val)->*&variable_t::initializer = qi::_1]
                    >> qi::eps[(&qi::_val)->*&variable_t::type = "auto"]
                )
                //attributed and deduced variable
                | (
                    attribute[(&qi::_val)->*&variable_t::attribute = qi::_1]
                    >> one_skip
                    >> identifier[(&qi::_val)->*&variable_t::name = qi::_1]
                    >> skip
                    >> initializer[(&qi::_val)->*&variable_t::initializer = qi::_1]
                    >> qi::eps[(&qi::_val)->*&variable_t::type = "auto"]
                )
                //typed variable
                | (
                    attribute[(&qi::_val)->*&variable_t::attribute = qi::_1]
                    >> one_skip
                    >> identifier[(&qi::_val)->*&variable_t::name = qi::_1]
                    >> skip
                    >> type[(&qi::_val)->*&variable_t::type = qi::_1]
                    >> skip
                    >> -initializer[(&qi::_val)->*&variable_t::initializer = qi::_1]
                )
            ) >>
            skip >>
            qi::omit[qi::lit(";")];
        }
    private:
        skipper<iterator> skip;
        one_skipper<iterator> one_skip;
        identify<iterator> identifier;
        boost::spirit::qi::rule<iterator, std::string()> initializer;
        boost::spirit::qi::rule<iterator, std::string()> type;
        boost::spirit::qi::rule<iterator, ::sapphire::core::ast::variable_t()> root;
        variable_attribute_rule_t attribute;
};
}

}