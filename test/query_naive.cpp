//
// Created by iensen on 6/6/20.
//

#include "gtest/gtest.h"
#include "utils.h"

TEST(NEWVERSION_NAIVE, _simple) {
    ASSERT_NEAR(run_plog("plogapp/tests/rshortwithpratom.plog", NewPlogMode::QUERY_NAIVE), 0.25, 1e-5);
}

TEST(PERF_NEWVERSION_NAIVE_BLOCKS, _20x5) {
    ASSERT_NEAR(run_plog("plogapp/tests/weijuns_testsuite/Blocks/blockmap20_5.plg", NewPlogMode::QUERY_NAIVE), 0.191692, 1e-5);
}

