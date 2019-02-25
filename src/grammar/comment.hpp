#pragma once
#include "ast/comment.h"
#include "comment.hpp"
#include "base.hpp"

namespace sapphire::core::parser {
template<class iterator_t, class skipper_t>
class comment : public boost::spirit::qi::grammar<iterator_t, skipper_t, ::sapphire::core::ast::comment_t()> {
    public:
        comment() : comment::base_type(root) {
            root = ((
                qi::lit("//") >> qi::as_string[*(qi::char_ - qi::eol)]
            ) | (
                qi::lit("/*") >> qi::as_string[*(qi::char_ - qi::lit("*/"))] >> qi::lit("*/")
            ));
            // root.name("comment::root");
            // qi::debug(root);
        }
    private:
        qi::rule<iterator_t, skipper_t, ::sapphire::core::ast::comment_t()> root;
};
}