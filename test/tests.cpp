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


TEST(NEWVERSION, 11) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/paper/monty1.plog"), 0.33333, 1e-5);
}


TEST(NEWVERSION, 12) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/paper/monty2.plog"), 0.0, 1e-5);
}

TEST(NEWVERSION, 13) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/paper/monty3.plog"), 0.66666, 1e-5);
}

TEST(OLDVERSTION_NAIVE_BLOCKS, _5x1) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap5_1.plg",OldPlogMode::NAIVE), 0.4, 1e-5);
}


TEST(OLDVERSTION_NAIVE_BLOCKS, _5x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap5_2.plg",OldPlogMode::NAIVE), 0.0, 1e-5);
}


TEST(OLDVERSTION_NAIVE_BLOCKS, _5x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap5_3.plg",OldPlogMode::NAIVE), 0.0, 1e-5);
}


TEST(OLDVERSTION_NAIVE_BLOCKS, _10x1) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap10_1.plg",OldPlogMode::NAIVE), 0.6, 1e-5);
}



TEST(OLDVERSTION_NAIVE_BLOCKS, _10x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap10_2.plg",OldPlogMode::NAIVE), 0.266667, 1e-5);
}



TEST(OLDVERSTION_NAIVE_BLOCKS, _10x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap10_3.plg",OldPlogMode::NAIVE), 0.0833333, 1e-5);
}


TEST(OLDVERSTION_NAIVE_BLOCKS, _15x1) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap15_1.plg",OldPlogMode::NAIVE), 0.733333 , 1e-5);
}



TEST(OLDVERSTION_NAIVE_BLOCKS, _15x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap15_2.plg",OldPlogMode::NAIVE), 0.504762, 1e-5);
}



TEST(OLDVERSTION_NAIVE_BLOCKS, _15x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap15_3.plg",OldPlogMode::NAIVE), 0.318681, 1e-5);
}


TEST(OLDVERSTION_NAIVE_BLOCKS, _20x1) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_1.plg",OldPlogMode::NAIVE), 0.8, 1e-5);
}



TEST(OLDVERSTION_NAIVE_BLOCKS, _20x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_2.plg",OldPlogMode::NAIVE), 0.621053, 1e-5);
}




TEST(OLDVERSTION_NAIVE_BLOCKS, _20x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_3.plg",OldPlogMode::NAIVE), 0.454386, 1e-5);
}




TEST(OLDVERSTION_NAIVE_BLOCKS, _20x5) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_5.plg",OldPlogMode::NAIVE), 0.191692, 1e-5);
}



TEST(OLDVERSTION_NAIVE_BLOCKS, _20x7) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_7.plg",OldPlogMode::NAIVE), 0.0549278, 1e-5);
}




TEST(OLDVERSTION_DCO_BLOCKS, _5x1) {
ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap5_1.plg",OldPlogMode::DCOOPTIMIZED), 0.4, 1e-5);
}


TEST(OLDVERSTION_DCO_BLOCKS, _5x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap5_2.plg",OldPlogMode::DCOOPTIMIZED), 0.0, 1e-5);
}


TEST(OLDVERSTION_DCO_BLOCKS, _5x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap5_3.plg",OldPlogMode::DCOOPTIMIZED), 0.0, 1e-5);
}


TEST(OLDVERSTION_DCO_BLOCKS, _10x1) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap10_1.plg",OldPlogMode::DCOOPTIMIZED), 0.6, 1e-5);
}



TEST(OLDVERSTION_DCO_BLOCKS, _10x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap10_2.plg",OldPlogMode::DCOOPTIMIZED), 0.266667, 1e-5);
}



TEST(OLDVERSTION_DCO_BLOCKS, _10x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap10_3.plg",OldPlogMode::DCOOPTIMIZED), 0.0833333, 1e-5);
}


TEST(OLDVERSTION_DCO_BLOCKS, _15x1) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap15_1.plg",OldPlogMode::DCOOPTIMIZED), 0.733333 , 1e-5);
}



TEST(OLDVERSTION_DCO_BLOCKS, _15x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap15_2.plg",OldPlogMode::DCOOPTIMIZED), 0.504762, 1e-5);
}



TEST(OLDVERSTION_DCO_BLOCKS, _15x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap15_3.plg",OldPlogMode::DCOOPTIMIZED), 0.318681, 1e-5);
}


TEST(OLDVERSTION_DCO_BLOCKS, _20x1) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_1.plg",OldPlogMode::DCOOPTIMIZED), 0.8, 1e-5);
}



TEST(OLDVERSTION_DCO_BLOCKS, _20x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_2.plg",OldPlogMode::DCOOPTIMIZED), 0.621053, 1e-5);
}




TEST(OLDVERSTION_DCO_BLOCKS, _20x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_3.plg",OldPlogMode::DCOOPTIMIZED), 0.454386, 1e-5);
}




TEST(OLDVERSTION_DCO_BLOCKS, _20x5) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_5.plg",OldPlogMode::DCOOPTIMIZED), 0.191692, 1e-5);
}



TEST(OLDVERSTION_DCO_BLOCKS, _20x7) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_7.plg",OldPlogMode::DCOOPTIMIZED), 0.0549278, 1e-5);
}







int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
