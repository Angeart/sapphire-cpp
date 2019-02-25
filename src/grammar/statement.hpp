#pragma once
#include "ast/statement.h"
#include "identify.hpp"
#include "import.hpp"
#include "comment.hpp"
#include "base.hpp"

namespace sapphire::core::parser {
template<class iterator_t, class skipper_t>
class control_statement : public qi::grammar<iterator_t, skipper_t, ::sapphire::core::ast::control_statement_t()> {
    public:
        control_statement() : control_statement::base_type(root) {
            root = import_;
            // root.name("control_statement::root");
            // qi::debug(root);
        }
    private:
        import<iterator_t, skipper_t> import_;
        qi::rule<iterator_t, skipper_t, ::sapphire::core::ast::control_statement_t()> root;
};

template<class iterator_t, class skipper_t>
class one_statement : public qi::grammar<iterator_t, skipper_t, ::sapphire::core::ast::one_statement_t()> {
    public:
        one_statement() : one_statement::base_type(root) {
            using ::sapphire::core::ast::one_statement_t;
            root =
            (
                (
                    control_statement_[(&qi::_val)->*&one_statement_t::control_statement = qi::_1]
                ) >> qi::omit[*keyword::semicolon]
            ) >> -(
                comment_[(&qi::_val)->*&one_statement_t::comment = qi::_1]
            );
            // root.name("one_statement::root");
            // qi::debug(root);
        }
    private:
        control_statement<iterator_t, skipper_t> control_statement_;
        comment<iterator_t, skipper_t> comment_;
        qi::rule<iterator_t, skipper_t, ::sapphire::core::ast::one_statement_t()> root;
};
}