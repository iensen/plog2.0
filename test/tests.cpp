//
// Created by iensen on 12/23/16.
//

#include "gtest/gtest.h"
#include "utils.h"


TEST(INITIALTEST, 0) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/p1.plog"), 0.30, 1e-8);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
