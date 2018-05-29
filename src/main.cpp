#include <iostream>
#include "grammar/variable.hpp"

int main() {
    sapphire::core::parser::variable<std::string::const_iterator> rule;
    const std::string source = "let hoge : int";
    std::cout << "input : " << source << std::endl;
    std::cout << "====================================" << std::endl;
    auto it = source.begin();
    const auto& end = source.end();
    sapphire::core::ast::variable_t result;
    if(boost::spirit::qi::parse(it,end,rule,result) && it != end) {
        std::cout << "parse failed" << std::endl;
    }
    std::cout << "attr : " << result.attribute << std::endl;
    std::cout << "name : " << result.name << std::endl;
    std::cout << "type : " << result.type << std::endl;
    std::cout << "init : " << result.initializer << std::endl;
}