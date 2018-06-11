#include "gtest/gtest.h"
#include "parser.hpp"
#include "grammar/variable.hpp"

using tester = tester_t<::sapphire::core::parser::variable>;


TEST(variable_test, normal_declaration) {
    using namespace sapphire::core;
    using ::sapphire::core::types::variable_attribute;
    tester::result_type require = {variable_attribute::let, "test_01", "int", ""};
    EXPECT_EQ(require, tester::parse("let test_01 : int;"));
}

TEST(variable_test, auto_declaration) {
    using namespace sapphire::core;
    using ::sapphire::core::types::variable_attribute;
    tester::result_type require = {variable_attribute::lazy, "test_02", "auto", "hoge"};
    ASSERT_EQ(require, tester::parse("lazy test_02 = hoge;"));
}

TEST(variable_test, failed_declaration) {
    using namespace sapphire::core;
    using ::sapphire::core::types::variable_attribute;
    ASSERT_THROW(tester::parse("lazy test_02;"), error::unable_parse);
}

TEST(variable_test, deduced_declaration) {
    using namespace sapphire::core;
    using ::sapphire::core::types::variable_attribute;
    tester::result_type require = {variable_attribute::let, "test_03", "auto", "hoge"};
    ASSERT_EQ(require, tester::parse("test_03 := hoge;"));
}