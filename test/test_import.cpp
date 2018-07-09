#include "gtest/gtest.h"
#include "parser.hpp"
#include "grammar/import.hpp"

using tester = tester_t<::sapphire::core::parser::import>;

TEST(impot_test, sinle_module) {
    using namespace sapphire::core;
    tester::result_type require = {{},{"TestModule"}};
    EXPECT_EQ(require, tester::parse("import TestModule"));
}

TEST(import_test, multi_module) {
    using namespace sapphire::core;
    tester::result_type require = {{},{"TestModule1","TestModule2"}};
    EXPECT_EQ(require, tester::parse("import TestModule1, TestModule2"));
}

TEST(import_test, single_function) {
    using namespace sapphire::core;
    tester::result_type require = {{"TestFunction"},{"FromModule"}};
    EXPECT_EQ(require, tester::parse("import TestFunction of FromModule"));
}

TEST(import_test, multi_function) {
    using namespace sapphire::core;
    tester::result_type require = {{"TestFunction1", "TestFunction2"},{"FromModule"}};
    EXPECT_EQ(require, tester::parse("import TestFunction1, TestFunction2 of FromModule"));
}

TEST(import_test, invalid_multi_function_and_multi_module) {
    using namespace sapphire::core;
    EXPECT_THROW(tester::parse("import TestFunction1, TestFunction2 of FromModule1, FromModule2"), error::unable_parse);
}