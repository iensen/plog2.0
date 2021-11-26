#include "gtest/gtest.h"
#include "utils.h"
#include "plog/plog.h"
#include "gmock/gmock.h"

using ::testing::HasSubstr;

TEST(NEWVERSION_SYNTAXERROR, 0) {
    auto error = ":10:1-11: error: syntax error, unexpected STMTDEFKEYWORD";
    EXPECT_THAT(get_error("plogapp/tests/errors/syntax_missingDot.plog"), HasSubstr(error));
}

TEST(NEWVERSION_SORTDEFERROR, 0) {
    auto error = ":3:6-10: invalid range definition.";
    EXPECT_THAT(get_error("plogapp/tests/errors/rangeSort.plog"), HasSubstr(error));
}