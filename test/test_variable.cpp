#include "grammar/variable.hpp"
#include "gtest/gtest.h"

namespace {
using namespace sapphire::core;
ast::variable_t parse(const std::string& source) {
    parser::variable<std::string::const_iterator> rule;
    auto it = source.begin();
    const auto& end = source.end();
    ast::variable_t result;
    if(!boost::spirit::qi::parse(it,end,rule,result) && it != end) {
        return {};
    }
    return result;
}
}

TEST(variable_test, normal_declaration) {
    using namespace sapphire::core;
    ast::variable_t require = {"let", "test_01", "int", ""};
    EXPECT_EQ(require, parse("let test_01 : int"));
}