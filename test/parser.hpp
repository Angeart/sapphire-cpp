#include <boost/spirit/include/qi.hpp>

namespace {

namespace error {
struct unable_parse {};
}
template<template<class iterator> class rule_t, class iterator_t = std::string::const_iterator, class result_t = typename rule_t<iterator_t>::start_type::attr_type>
struct tester_t {
    using result_type = result_t;
    static result_t parse(const std::string& input) {
        rule_t<iterator_t> rule;
        result_t result;
        auto it = input.begin();
        const auto& end = input.end();
        if(!boost::spirit::qi::parse(it,end,rule,result) || it != end) {
            throw error::unable_parse();
            return {};
        }
        return result;
    }
};
}