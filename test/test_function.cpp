#include "gtest/gtest.h"
#include "grammar/function.hpp"

namespace {
using namespace sapphire::core;
ast::function_t parse(const std::string& source) {
    parser::function<std::string::const_iterator> rule;
    auto it = source.begin();
    const auto& end = source.end();
    ast::function_t result;
    if(!boost::spirit::qi::parse(it,end,rule,result) || it != end) {
        std::cout << "parse failed" << std::endl;
        return {};
    }
    return result;
}
}

TEST(function_test, normal_declaration) {
    using namespace sapphire::core;
    ast::function_t require = {"test_01", "", {}, {"", "body"}, 0};
    ASSERT_EQ(require, parse("test_01() { body }"));
}