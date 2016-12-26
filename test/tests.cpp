//
// Created by iensen on 12/23/16.
//

#include "gtest/gtest.h"
#include "utils.h"


TEST(NEWVERSION, 0) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/p1.plog"), 0.30, 1e-8);
}

TEST(NEWVERSION, 1) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/triv0.plog"), 1.0, 1e-8);
}

TEST(NEWVERSION, 2) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/triv1.plog"), 0.0, 1e-8);
}

TEST(NEWVERSION, 3) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/rels0.plog"), 1.0, 1e-8);
}


TEST(NEWVERSION, 4) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/rels.plog"), 0.5, 1e-8);
}





int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
