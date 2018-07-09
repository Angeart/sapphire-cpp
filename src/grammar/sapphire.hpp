#pragma once
#include "ast/sapphire.h"
#include "core_keywords.hpp"
#include "statement.hpp"
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <string>

namespace sapphire::core::parser {
template<class iterator_t, class skipper_t>
class sapphire : public boost::spirit::qi::grammar<iterator_t, skipper_t, ::sapphire::core::ast::sapphire_t()> {
    public:
        sapphire() : sapphire::base_type(root) {
            namespace qi = boost::spirit::qi;
            namespace ph = boost::phoenix;
            statements = +(statement >> qi::omit[keyword::semicolon]);
            root = statements;
        }
    private:
        all_statement<iterator_t, skipper_t> statement;
        boost::spirit::qi::rule<iterator_t, skipper_t, std::vector<::sapphire::core::ast::all_statement_t>()> statements;
        boost::spirit::qi::rule<iterator_t, skipper_t, ::sapphire::core::ast::sapphire_t()> root;
};
}