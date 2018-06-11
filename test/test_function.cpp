#include "gtest/gtest.h"
#include "parser.hpp"
#include "grammar/function.hpp"

using tester = tester_t<::sapphire::core::parser::function>;

TEST(function_test, minimum_declaration) {
    using namespace sapphire::core;
    tester::result_type require = {"test_01", "", {}, {"", "body"}, 0};
    ASSERT_EQ(require, tester::parse("test_01() { body }"));
}

TEST(function_test, normal_declaration) {
    using namespace sapphire::core;
    tester::result_type require = {"test_02", "let arg1 : int", {}, {"", "body"}, 0};
    ASSERT_EQ(require, tester::parse("test_02(let arg1 : int) { body }"));
}

TEST(function_test, pattern_declaration) {
    using namespace sapphire::core;
    tester::result_type require = {"test_03", "let arg1 : int", {{"pattern1", "pattern_body"}}, {"", "default"}, 0};
    ASSERT_EQ(require, tester::parse("test_03(let arg1 : int) | pattern1 { pattern_body } | { default }"));
}