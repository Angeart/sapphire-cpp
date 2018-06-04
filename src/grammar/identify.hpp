#pragma once
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <string>

namespace sapphire::core::parser {
template<class iterator>
class identify : public boost::spirit::qi::grammar<iterator, std::string()> {
public:
    identify() : identify::base_type(root) {
        namespace qi = boost::spirit::qi;
        namespace ph = boost::phoenix;
        namespace ascii = boost::spirit::ascii;
        root = qi::as_string[ascii::alpha >> *(ascii::alnum | qi::char_('_'))];
    }
private:
    boost::spirit::qi::rule<iterator, std::string()> root;
};
}
