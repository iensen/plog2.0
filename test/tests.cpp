//
// Created by iensen on 12/23/16.
//

#include "gtest/gtest.h"
#include "utils.h"



static void run_naive_query_tests() {
    ::testing::GTEST_FLAG(filter) = "NEWVERSION_NAIVE*";
}

int main(int argc, char **argv) {
    //int PATH_MAX = 100500;

    ::testing::InitGoogleTest(&argc, argv);
    run_naive_query_tests();
    //::testing::GTEST_FLAG(filter) = "NEWVERSION_SQ*";
    //::testing::GTEST_FLAG(filter) = "NEWVERSION_BLOCKS._20x5*";
    //::testing::GTEST_FLAG(filter) = "OLDVERSION_SQ*";
    //::testing::GTEST_FLAG(filter) = "NEWVERSION_BLOCKS._20x5*";
    //::testing::GTEST_FLAG(filter) = "NEWVERSION_POKER._5x4x36*";

    //::testing::GTEST_FLAG(filter) = "OLDVERSION_NAIVE_BLOCKS._20x5";


    //::testing::GTEST_FLAG(filter) = "NEWVERSION_NASA._l4";
    //::testing::GTEST_FLAG(filter) = "NEWVERSION_NASA._fgl4";
    // ::testing::GTEST_FLAG(filter) = "OLDVERSION_NAIVE_POKER._*";
    // ::testing::GTEST_FLAG(filter) = "NEWVERSION_POKER._5x3";
    //::testing::GTEST_FLAG(filter) = "NEWVERSION_NASA._fgl4rdn";
    //::testing::GTEST_FLAG(filter) = "NEWVERSION_POKER._*";
    //::testing::GTEST_FLAG(filter) = "NEWVERSION_BLOCKS._*";
    //::testing::GTEST_FLAG(filter) = "PERF_OLDVERSION_NAIVE_POKER*";

    return RUN_ALL_TESTS();
}
