#pragma once
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>

namespace sapphire::core {
namespace parser {
template<class iterator>
class skipper : public boost::spirit::qi::grammar<iterator> {
public:
    skipper() : skipper::base_type(root) {
        namespace qi = boost::spirit::qi;
        namespace ph = boost::phoenix;
        root = qi::omit[*qi::blank];
    }
private:
    boost::spirit::qi::rule<iterator> root;
};
template<class iterator>
class one_skipper : public boost::spirit::qi::grammar<iterator> {
public:
    one_skipper() : one_skipper::base_type(root) {
        namespace qi = boost::spirit::qi;
        namespace ph = boost::phoenix;
        root = qi::omit[+qi::blank];
    }
private:
    boost::spirit::qi::rule<iterator> root;
};
}
}