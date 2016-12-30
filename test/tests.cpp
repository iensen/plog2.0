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


TEST(NEWVERSION, 14) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/rsort.plog"), 0.111111, 1e-5);
}


TEST(OLDVERSION_NAIVE_BLOCKS, _5x1) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap5_1.plg",OldPlogMode::NAIVE), 0.4, 1e-5);
}


TEST(OLDVERSION_NAIVE_BLOCKS, _5x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap5_2.plg",OldPlogMode::NAIVE), 0.0, 1e-5);
}


TEST(OLDVERSION_NAIVE_BLOCKS, _5x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap5_3.plg",OldPlogMode::NAIVE), 0.0, 1e-5);
}


TEST(OLDVERSION_NAIVE_BLOCKS, _10x1) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap10_1.plg",OldPlogMode::NAIVE), 0.6, 1e-5);
}



TEST(OLDVERSION_NAIVE_BLOCKS, _10x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap10_2.plg",OldPlogMode::NAIVE), 0.266667, 1e-5);
}



TEST(OLDVERSION_NAIVE_BLOCKS, _10x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap10_3.plg",OldPlogMode::NAIVE), 0.0833333, 1e-5);
}


TEST(OLDVERSION_NAIVE_BLOCKS, _20x1) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_1.plg",OldPlogMode::NAIVE), 0.8, 1e-5);
}



TEST(OLDVERSION_NAIVE_BLOCKS, _20x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_2.plg",OldPlogMode::NAIVE), 0.621053, 1e-5);
}




TEST(OLDVERSION_NAIVE_BLOCKS, _20x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_3.plg",OldPlogMode::NAIVE), 0.454386, 1e-5);
}

TEST(OLDVERSION_DCO_BLOCKS, _20x1) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_1.plg",OldPlogMode::DCOOPTIMIZED), 0.8, 1e-5);
}


TEST(OLDVERSION_DCO_BLOCKS, _20x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_2.plg",OldPlogMode::DCOOPTIMIZED), 0.621053, 1e-5);
}

TEST(OLDVERSION_DCO_BLOCKS, _20x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_3.plg",OldPlogMode::DCOOPTIMIZED), 0.454386, 1e-5);
}





//TEST(OLDVERSION_NAIVE_BLOCKS, _20x5) {
//    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_5.plg",OldPlogMode::NAIVE), 0.191692, 1e-5);
//}



//TEST(OLDVERSION_NAIVE_BLOCKS, _20x7) {
//    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_7.plg",OldPlogMode::NAIVE), 0.0549278, 1e-5);
//}




TEST(OLDVERSION_DCO_BLOCKS, _5x1) {
ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap5_1.plg",OldPlogMode::DCOOPTIMIZED), 0.4, 1e-5);
}


TEST(OLDVERSION_DCO_BLOCKS, _5x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap5_2.plg",OldPlogMode::DCOOPTIMIZED), 0.0, 1e-5);
}


TEST(OLDVERSION_DCO_BLOCKS, _5x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap5_3.plg",OldPlogMode::DCOOPTIMIZED), 0.0, 1e-5);
}


TEST(OLDVERSION_DCO_BLOCKS, _10x1) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap10_1.plg",OldPlogMode::DCOOPTIMIZED), 0.6, 1e-5);
}



TEST(OLDVERSION_DCO_BLOCKS, _10x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap10_2.plg",OldPlogMode::DCOOPTIMIZED), 0.266667, 1e-5);
}



TEST(OLDVERSION_DCO_BLOCKS, _10x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap10_3.plg",OldPlogMode::DCOOPTIMIZED), 0.0833333, 1e-5);
}

TEST(OLDVERSION_NAIVE_BLOCKS, _15x1) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap15_1.plg",OldPlogMode::NAIVE), 0.733333 , 1e-5);
}



TEST(OLDVERSION_NAIVE_BLOCKS, _15x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap15_2.plg",OldPlogMode::NAIVE), 0.504762, 1e-5);
}





TEST(OLDVERSION_DCO_BLOCKS, _15x1) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap15_1.plg",OldPlogMode::DCOOPTIMIZED), 0.733333 , 1e-5);
}



TEST(OLDVERSION_DCO_BLOCKS, _15x2) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap15_2.plg",OldPlogMode::DCOOPTIMIZED), 0.504762, 1e-5);
}



TEST(OLDVERSION_NAIVE_POKER, _3x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_3_3.txt",OldPlogMode::NAIVE), 0.368182, 1e-5);
}


TEST(OLDVERSION_NAIVE_POKER, _3x4) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_3_4.txt",OldPlogMode::NAIVE), 0.514286, 1e-5);
}

TEST(OLDVERSION_NAIVE_POKER, _3x5) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_3_5.txt",OldPlogMode::NAIVE), 0.526316, 1e-5);
}




TEST(OLDVERSION_DCO_POKER, _3x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_3_3.txt",OldPlogMode::DCOOPTIMIZED), 0.368182, 1e-5);
}


TEST(OLDVERSION_DCO_POKER, _3x4) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_3_4.txt",OldPlogMode::DCOOPTIMIZED), 0.514286, 1e-5);
}

TEST(OLDVERSION_DCO_POKER, _3x5) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_3_5.txt",OldPlogMode::DCOOPTIMIZED), 0.526316, 1e-5);
}




TEST(OLDVERSION_NAIVE_POKER, _5x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_5_3.txt",OldPlogMode::NAIVE), 0.545455, 1e-5);
}


TEST(OLDVERSION_NAIVE_POKER, _5x4) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_5_4.txt",OldPlogMode::NAIVE), 0.417582, 1e-5);
}

TEST(OLDVERSION_NAIVE_POKER, _5x5) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_5_5.txt",OldPlogMode::NAIVE), 0.399897, 1e-5);
}




TEST(OLDVERSION_DCO_POKER, _5x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_5_3.txt",OldPlogMode::DCOOPTIMIZED), 0.545455, 1e-5);
}


TEST(OLDVERSION_DCO_POKER, _5x4) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_5_4.txt",OldPlogMode::DCOOPTIMIZED), 0.417582, 1e-5);
}

TEST(OLDVERSION_DCO_POKER, _5x5) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_5_5.txt",OldPlogMode::DCOOPTIMIZED), 0.399897, 1e-5);
}



TEST(NEWVERSION_BLOCKS, _5x1) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Blocks/blockmap5_1.plg"), 0.4, 1e-5);
}


TEST(NEWVERSION_BLOCKS, _5x2) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Blocks/blockmap5_2.plg"), 0.0, 1e-5);
}


TEST(NEWVERSION_BLOCKS, _5x3) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Blocks/blockmap5_3.plg"), 0.0, 1e-5);
}


TEST(NEWVERSION_BLOCKS, _10x1) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Blocks/blockmap10_1.plg"), 0.6, 1e-5);
}

TEST(NEWVERSION_BLOCKS, _10x2) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Blocks/blockmap10_2.plg"), 0.266667, 1e-5);
}

TEST(NEWVERSION_BLOCKS, _10x3) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Blocks/blockmap10_3.plg"), 0.0833333, 1e-5);
}


TEST(NEWVERSION_BLOCKS, _20x1) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Blocks/blockmap20_1.plg"), 0.8, 1e-5);
}

TEST(NEWVERSION_BLOCKS, _20x2) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Blocks/blockmap20_2.plg"), 0.621053, 1e-5);
}

TEST(NEWVERSION_BLOCKS, _20x3) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Blocks/blockmap20_3.plg"), 0.454386, 1e-5);
}






TEST(NEWVERSION_BLOCKS, _15x1) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Blocks/blockmap15_1.plg"), 0.733333 , 1e-5);
}

TEST(NEWVERSION_BLOCKS, _15x2) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Blocks/blockmap15_2.plg"), 0.504762 , 1e-5);
}

TEST(NEWVERSION_POKER, _3x3) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Poker/poker_3_3.txt"), 0.368182, 1e-5);
}


TEST(NEWVERSION_POKER, _3x4) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Poker/poker_3_4.txt"), 0.514286, 1e-5);
}

TEST(NEWVERSION_POKER, _3x5) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Poker/poker_3_5.txt"), 0.526316, 1e-5);
}



TEST(NEWVERSION_POKER, _5x3) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Poker/poker_5_3.txt"), 0.545455, 1e-5);
}


TEST(NEWVERSION_POKER, _5x4) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Poker/poker_5_4.txt"), 0.417582, 1e-5);
}

TEST(NEWVERSION_POKER, _5x5) {
    ASSERT_NEAR(run_plog("../../plog/plogapp/tests/weijuns_testsuite/Poker/poker_5_5.txt"), 0.399897, 1e-5);
}








int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(filter) = "OLDVERSION_NAIVE_POKER*";
    return RUN_ALL_TESTS();
}
