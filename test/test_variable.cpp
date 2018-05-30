#include "gtest/gtest.h"
#include "grammar/variable.hpp"

namespace {
using namespace sapphire::core;
ast::variable_t parse(const std::string& source) {
    parser::variable<std::string::const_iterator> rule;
    auto it = source.begin();
    const auto& end = source.end();
    ast::variable_t result;
    if(!boost::spirit::qi::parse(it,end,rule,result) || it != end) {
        std::cout << "parse failed" << std::endl;
        return {};
    }
    return result;
}
}

TEST(variable_test, normal_declaration) {
    using namespace sapphire::core;
    using ::sapphire::core::types::variable_attribute;
    ast::variable_t require = {variable_attribute::let, "test_01", "int", ""};
    EXPECT_EQ(require, parse("let test_01 : int;"));
}

TEST(variable_test, auto_declaration) {
    using namespace sapphire::core;
    using ::sapphire::core::types::variable_attribute;
    ast::variable_t require = {variable_attribute::lazy, "test_02", "auto", "hoge"};
    ASSERT_EQ(require, parse("lazy test_02 := hoge;"));
}
