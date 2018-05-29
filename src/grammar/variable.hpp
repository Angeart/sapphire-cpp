#pragma once
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <string>
#include <tuple>
#include "ast/variable.h"

namespace sapphire::core{
namespace parser {
template<class iterator>
class variable : public boost::spirit::qi::grammar<iterator, ::sapphire::core::ast::variable_t()> {
    public:
        variable() : variable::base_type(root) {
            namespace qi = boost::spirit::qi;
            namespace ph = boost::phoenix;
            using ::sapphire::core::ast::variable_t;
            root =
            //attr name
            (
                qi::omit[*qi::space] >>
                (qi::as_string[*(qi::char_ - qi::space)][(&qi::_val)->*&variable_t::attribute = qi::_1]) >>
                qi::omit[*qi::space] >>
                (qi::as_string[*(qi::char_ - qi::space)][(&qi::_val)->*&variable_t::name = qi::_1])
            )[(&qi::_val)->*&variable_t::type = "auto"] >>
            //type
            -(
                qi::omit[*qi::space] >>
                qi::omit[qi::lit(":")] >>
                qi::omit[*qi::space] >>
                 (qi::as_string[*(qi::char_ - qi::space)][(&qi::_val)->*&variable_t::type = qi::_1])
            );
        }
    private:
        boost::spirit::qi::rule<iterator, ::sapphire::core::ast::variable_t()> root;
};
}

}