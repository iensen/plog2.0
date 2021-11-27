#include "gtest/gtest.h"
#include "utils.h"
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

TEST(NEWVERSION_UNDEFINEDSORT, SETEXPR) {
    auto error = ":4:7-10: undefined sort #s1.";
    EXPECT_THAT(get_error("plogapp/tests/errors/undefinedSortInSetExpr.plog"), HasSubstr(error));
}

TEST(NEWVERSION_SORTREDEFININTION, 0) {
    auto error = "4:1-10: incorrect sort definition. The sort s was already defined at line 3";
    EXPECT_THAT(get_error("plogapp/tests/errors/doubleSortDef.plog"), HasSubstr(error));
}

TEST(NEWVERSION_UNDEFINEDSORT, FUNCSORT) {
    auto error = "4:13-16: undefined sort #s1.";
    EXPECT_THAT(get_error("plogapp/tests/errors/undefinedSortInFuncSortExpr.plog"), HasSubstr(error));
}

TEST(NEWVERSION_ATTRDECLERROR, REDEFINITION) {
    auto error = "5:1-17: attribute a was already defined in line 4. Remove one of the definitions.";
    EXPECT_THAT(get_error("plogapp/tests/errors/doubleAttDecl.plog"), HasSubstr(error));
}

TEST(NEWVERSION_ATTRDECLERROR, CONFLICT_WITH_RECORD1) {
    auto error = "4:1-11: the definition of attribute f conflicts with a record of the same name";
    EXPECT_THAT(get_error("plogapp/tests/errors/AttAndRecordConflict1.plog"), HasSubstr(error));
}

TEST(NEWVERSION_ATTRDECLERROR, CONFLICT_WITH_RECORD2) {
    auto error = "5:1-13: the definition of attribute f conflicts with a record of the same name";
    EXPECT_THAT(get_error("plogapp/tests/errors/AttAndRecordConflict2.plog"), HasSubstr(error));
}

// test for wrong sort expression used to define possible attribute values.
TEST(NEWVERSION_ATTRDECLERROR, WRONG_SORTEXPR) {
    auto error = "5:11-14: undefined sort #s3";
    EXPECT_THAT(get_error("plogapp/tests/errors/WrongSortExprInAttlDecl.plog"), HasSubstr(error));
}

// test for wrong sort expression used to define possible attribute arguments.
TEST(NEWVERSION_ATTRDECLERROR, WRONG_SORTEXPR2) {
    auto error = "5:4-7: undefined sort #s3";
    EXPECT_THAT(get_error("plogapp/tests/errors/WrongSortExprInAttlDecl2.plog"), HasSubstr(error));
}


