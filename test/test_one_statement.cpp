#include "gtest/gtest.h"
#include "parser.hpp"
#include "grammar/statement.hpp"

using tester = tester_t<::sapphire::core::parser::one_statement>;

TEST(all_statement_test, sinle_module) {
    using namespace sapphire::core;
    tester::result_type require = {
        ast::control_statement_t(
            {{}, {"TestModule"}}
        ),
        {}
    };
    EXPECT_EQ(require, tester::parse("import TestModule;"));
}
