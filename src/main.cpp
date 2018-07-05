#include <iostream>
#include "grammar/import.hpp"

int main() {
    sapphire::core::parser::import<std::string::const_iterator> rule;
    const std::string source = "import TestModule1, TestModule2;";
    std::cout << "input : " << source << std::endl;
    std::cout << "====================================" << std::endl;
    auto it = source.begin();
    const auto& end = source.end();
    sapphire::core::ast::import_t result;
    if(!boost::spirit::qi::parse(it,end,rule,result) || it != end) {
        std::cout << "parse failed" << std::endl;
        std::cout << *it << std::endl;
    }
    std::string fstr = "", mstr = "";
    for(auto f : result.functions) { fstr += f; }
    for(auto m : result.modules) { mstr += m; }
    std::cout << "functions : " << fstr << std::endl;
    std::cout << "modules : " << mstr << std::endl;

}