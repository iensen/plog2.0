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

TEST(NEWVERSION, 5) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/rshort.plog"), 1.0/3.0, 1e-5);
}

TEST(NEWVERSION, 6) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/obs1.plog"), 1.0 , 1e-5);
}


TEST(NEWVERSION, 7) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/obs2.plog"), 0.0, 1e-5);
}


TEST(NEWVERSION, 8) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/paper/dice1.plog"), 0.25, 1e-5);
}

TEST(NEWVERSION, 9) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/paper/dice2.plog"), 0.15, 1e-5);
}

TEST(NEWVERSION, 10) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/paper/dice3.plog"), 1.0/6.0, 1e-5);
}





int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
