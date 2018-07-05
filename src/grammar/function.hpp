#pragma once
#include "ast/function.h"
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
template<class iterator_t, class skipper_t>
class function : public boost::spirit::qi::grammar<iterator_t, skipper_t, ::sapphire::core::ast::function_t()> {
    public:
        function() : function::base_type(root) {
            namespace qi = boost::spirit::qi;
            namespace ph = boost::phoenix;
            using ::sapphire::core::ast::function_t;
            using ::sapphire::core::ast::function_pattern_t;
            body = (
                qi::omit[keyword::lcb]
                >> qi::as_string[*(qi::char_ - keyword::rcb - qi::blank)][qi::_val = qi::_1]
                >> qi::omit[keyword::rcb]
            );
            pattern = (
                qi::omit[keyword::pipe]
                >> qi::as_string[+(qi::char_ - keyword::lcb - qi::blank)][(&qi::_val)->*&function_pattern_t::pattern = qi::_1]
                >> body[(&qi::_val)->*&function_pattern_t::body = qi::_1]
            );
            patterns = (pattern % qi::eps);
            default_pattern = (
                qi::omit[keyword::pipe]
                >> body[(&qi::_val)->*&function_pattern_t::body = qi::_1]
            );
            body_only = (
                body[(&qi::_val)->*&function_pattern_t::body = qi::_1]
            );
            arguments = (
                qi::omit[keyword::lrb]
                >> qi::no_skip[qi::as_string[*(qi::char_ - keyword::rrb)][qi::_val = qi::_1]]
                >> qi::omit[keyword::rrb]
            );
            root = (
                identifier[(&qi::_val)->*&function_t::name = qi::_1]
                >> arguments[(&qi::_val)->*&function_t::arguments = qi::_1]
                >> (
                    (
                        patterns[(&qi::_val)->*&function_t::patterns = qi::_1]
                        >> default_pattern[(&qi::_val)->*&function_t::default_pattern = qi::_1]
                    )
                    | body_only[(&qi::_val)->*&function_t::default_pattern = qi::_1]
                )
            );
        }
      private:
        identify<iterator_t> identifier;
        boost::spirit::qi::rule<iterator_t, skipper_t, std::string()> body;
        boost::spirit::qi::rule<iterator_t, skipper_t, ::sapphire::core::ast::function_pattern_t()> pattern;
        boost::spirit::qi::rule<iterator_t, skipper_t, std::vector<::sapphire::core::ast::function_pattern_t>()> patterns;
        boost::spirit::qi::rule<iterator_t, skipper_t, ::sapphire::core::ast::function_pattern_t()> default_pattern;
        boost::spirit::qi::rule<iterator_t, skipper_t, ::sapphire::core::ast::function_pattern_t()> body_only;
        boost::spirit::qi::rule<iterator_t, skipper_t, std::string()> arguments;
        boost::spirit::qi::rule<iterator_t, skipper_t, ::sapphire::core::ast::function_t()> root;
};
}
}