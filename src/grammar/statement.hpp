#pragma once
#include "ast/statement.h"
#include "identify.hpp"
#include "core_keywords.hpp"
#include "import.hpp"
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>

namespace sapphire::core::parser {
template<class iterator_t, class skipper_t>
class control_statement : public boost::spirit::qi::grammar<iterator_t, skipper_t, ::sapphire::core::ast::control_statement_t()> {
    public:
        control_statement() : control_statement::base_type(root) {
            namespace qi = boost::spirit::qi;
            namespace ph = boost::phoenix;
            root = import_;
        }
    private:
        import<iterator_t, skipper_t> import_;
        boost::spirit::qi::rule<iterator_t, skipper_t, ::sapphire::core::ast::control_statement_t()> root;
};
template<class iterator_t, class skipper_t>
class all_statement : public boost::spirit::qi::grammar<iterator_t, skipper_t, ::sapphire::core::ast::all_statement_t()> {
    public:
        all_statement() : all_statement::base_type(root) {
            namespace qi = boost::spirit::qi;
            namespace ph = boost::phoenix;
            root = control_statement_;
        }
    private:
        control_statement<iterator_t, skipper_t> control_statement_;
        boost::spirit::qi::rule<iterator_t, skipper_t, ::sapphire::core::ast::all_statement_t()> root;
};
}