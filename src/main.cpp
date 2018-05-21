#include <iostream>
#include "parser.hpp"

int main() {
    opal::core::parser::test<std::string::const_iterator> rule;
    const std::string source = "2 + 3";
    auto it = source.begin();
    const auto& end = source.end();
    opal::core::parser::arithmetic_t result;
    if(boost::spirit::qi::parse(it,end,rule,result) && it != end) {
        std::cout << "parse failed" << std::endl;
    }
    std::cout << "test" << std::endl;
}