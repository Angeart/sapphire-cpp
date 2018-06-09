#pragma once
#include "ast/function.h"
#include "skipper.hpp"
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
template<class iterator>
class function : public boost::spirit::qi::grammar<iterator, ::sapphire::core::ast::function_t()> {
    public:
        function() : function::base_type(root) {
            namespace qi = boost::spirit::qi;
            namespace ph = boost::phoenix;
            using ::sapphire::core::ast::function_t;
            using ::sapphire::core::ast::function_pattern_t;
            body = (
                qi::omit[keyword::lcb]
                >> skip
                >> qi::as_string[*(qi::char_ - keyword::rcb - qi::blank)][qi::_val = qi::_1]
                >> skip
                >> qi::omit[keyword::rcb]
            );
            pattern = (
                qi::omit[keyword::pipe]
                >> skip_eol
                >> qi::as_string[*(qi::char_ - keyword::lcb)][(&qi::_val)->*&function_pattern_t::pattern = qi::_1]
                >> skip_eol
                >> body[(&qi::_val)->*&function_pattern_t::body = qi::_1]
            );
            patterns = +(pattern);
            default_pattern = (
                qi::omit[keyword::pipe]
                >> skip_eol
                >> body[(&qi::_val)->*&function_pattern_t::body = qi::_1]
            );
            body_only = (
                skip_eol
                >> body[(&qi::_val)->*&function_pattern_t::body = qi::_1]
            );
            arguments = (
                qi::omit[keyword::lrb]
                >> skip
                >> qi::as_string[*(qi::char_ - keyword::rrb)][qi::_val = qi::_1]
                >> skip
                >> qi::omit[keyword::rrb]
            );
            root = (
                identifier[(&qi::_val)->*&function_t::name = qi::_1]
                >> skip
                >> arguments[(&qi::_val)->*&function_t::arguments = qi::_1]
                >> skip_eol
                >> (
                    (
                        patterns[(&qi::_val)->*&function_t::patterns = qi::_1]
                        >> skip_eol
                        >> default_pattern[(&qi::_val)->*&function_t::default_pattern = qi::_1]
                    )
                    | body_only[(&qi::_val)->*&function_t::default_pattern = qi::_1]
                )
                >> skip_eol
            );
        }
    private:
        skipper<iterator> skip;
        skipper_with_eol<iterator> skip_eol;
        identify<iterator> identifier;
        boost::spirit::qi::rule<iterator, std::string()> body;
        boost::spirit::qi::rule<iterator, ::sapphire::core::ast::function_pattern_t()> pattern;
        boost::spirit::qi::rule<iterator, std::vector<::sapphire::core::ast::function_pattern_t>()> patterns;
        boost::spirit::qi::rule<iterator, ::sapphire::core::ast::function_pattern_t()> default_pattern;
        boost::spirit::qi::rule<iterator, ::sapphire::core::ast::function_pattern_t()> body_only;
        boost::spirit::qi::rule<iterator, std::string()> arguments;
        boost::spirit::qi::rule<iterator, ::sapphire::core::ast::function_t()> root;
};
}
}