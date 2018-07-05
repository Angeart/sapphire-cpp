#pragma once
#include <boost/spirit/include/qi.hpp>

namespace sapphire::core {
namespace parser {
template<class iterator>
class skipper : public boost::spirit::qi::grammar<iterator> {
public:
    skipper() : skipper::base_type(root) {
        namespace qi = boost::spirit::qi;
        root = +(qi::blank | qi::eol);
    }
private:
    boost::spirit::qi::rule<iterator> root;
};
}
}