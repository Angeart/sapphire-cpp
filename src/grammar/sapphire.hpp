#pragma once
#include "ast/sapphire.h"
#include "statement.hpp"
#include <string>
#include "base.hpp"

namespace sapphire::core::parser {
template<class iterator_t, class skipper_t>
class sapphire : public boost::spirit::qi::grammar<iterator_t, skipper_t, ::sapphire::core::ast::sapphire_t()> {
    public:
        sapphire() : sapphire::base_type(root) {
            statements = *statement;
            root = statements[(&qi::_val)->*&::sapphire::core::ast::sapphire_t::statements = qi::_1];
            // root.name("sapphire::root");
            // qi::debug(root);
        }
    private:
        one_statement<iterator_t, skipper_t> statement;
        boost::spirit::qi::rule<iterator_t, skipper_t, std::vector<::sapphire::core::ast::one_statement_t>()> statements;
        boost::spirit::qi::rule<iterator_t, skipper_t, ::sapphire::core::ast::sapphire_t()> root;
};
}