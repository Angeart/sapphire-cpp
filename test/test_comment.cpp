#include "gtest/gtest.h"
#include "parser.hpp"
#include "grammar/comment.hpp"

using tester = tester_t<::sapphire::core::parser::comment>;

TEST(comment_test, sinle_line) {
    using namespace sapphire::core;
    tester::result_type require = {
        {"comment"}
    };
    EXPECT_EQ(require, tester::parse("// comment"));
}

TEST(comment_test, multi_line) {
    using namespace sapphire::core;
    tester::result_type require = {
        {"comment"}
    };
    EXPECT_EQ(require, tester::parse("/* comment */"));
}
