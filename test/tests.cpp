//
// Created by iensen on 12/23/16.
//

#include "gtest/gtest.h"
#include "utils.h"

static void run_all_new_nonperf_tests() {
    ::testing::GTEST_FLAG(filter) = "NEWVERSION*";
}

static void run_naive_query_tests() {
    ::testing::GTEST_FLAG(filter) = "*NEWVERSION_NAIVE*";
}

int main(int argc, char **argv) {
    //int PATH_MAX = 100500;

    ::testing::InitGoogleTest(&argc, argv);
    run_all_new_nonperf_tests();

    return RUN_ALL_TESTS();
}
