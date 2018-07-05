#pragma once
#include "ast/variable.h"
#include "identify.hpp"
#include "core_keywords.hpp"
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <string>
#include <tuple>

namespace sapphire::core {
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
template<class iterator_t, class skipper_t>
class variable : public boost::spirit::qi::grammar<iterator_t, skipper_t, ::sapphire::core::ast::variable_t()> {
    public:
        variable() : variable::base_type(root) {
            namespace qi = boost::spirit::qi;
            namespace ph = boost::phoenix;
            using ::sapphire::core::ast::variable_t;
            initializer =
            (
                qi::omit[keyword::assign] >>
                (identifier[qi::_val = qi::_1])
            );
            restrainer =
            (
                qi::omit[keyword::dni] >>
                (identifier[qi::_val = qi::_1])
            );
            type =
            (
                qi::omit[keyword::colon] >>
                (identifier[qi::_val = qi::_1])
            );
            root =
            (
                //deduced attribute variable
                (
                    identifier[(&qi::_val)->*&variable_t::name = qi::_1]
                    >> qi::eps[(&qi::_val)->*&variable_t::type = "auto"]
                    >> -type[(&qi::_val)->*&variable_t::type = qi::_1]
                    >> restrainer[(&qi::_val)->*&variable_t::initializer = qi::_1]
                    >> qi::eps[(&qi::_val)->*&variable_t::attribute = types::variable_attribute::let]
                )
                //attributed and deduced variable
                | (
                    attribute[(&qi::_val)->*&variable_t::attribute = qi::_1]
                    >> identifier[(&qi::_val)->*&variable_t::name = qi::_1]
                    >> initializer[(&qi::_val)->*&variable_t::initializer = qi::_1]
                    >> qi::eps[(&qi::_val)->*&variable_t::type = "auto"]
                )
                //typed variable
                | (
                    attribute[(&qi::_val)->*&variable_t::attribute = qi::_1]
                    >> identifier[(&qi::_val)->*&variable_t::name = qi::_1]
                    >> type[(&qi::_val)->*&variable_t::type = qi::_1]
                    >> -initializer[(&qi::_val)->*&variable_t::initializer = qi::_1]
                )
            );
        }
    private:
        identify<iterator_t> identifier;
        boost::spirit::qi::rule<iterator_t, skipper_t, std::string()> initializer;
        boost::spirit::qi::rule<iterator_t, skipper_t, std::string()> restrainer;
        boost::spirit::qi::rule<iterator_t, skipper_t, std::string()> type;
        boost::spirit::qi::rule<iterator_t, skipper_t, ::sapphire::core::ast::variable_t()> root;
        variable_attribute_rule_t attribute;
};
}

}