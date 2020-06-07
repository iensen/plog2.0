//
// Created by iensen on 6/6/20.
//

#include "gtest/gtest.h"
#include "utils.h"


/* Tests for the version of P-log deveoped by Weijun Zhu for his dissertation */

TEST(OLDVERSION_NAIVE_BLOCKS_2, _5x1) {
    ASSERT_NEAR(run_old_plog("oldplog/Examples/BlockWorld/blockmap5_1.plg",OldPlogMode::NAIVE), 0.4, 1e-5);
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


TEST(OLDVERSION_NAIVE_BLOCKS, _20x4) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_4.plg",OldPlogMode::NAIVE), 0.308153, 1e-5);
}



TEST(PERF_OLDVERSION_NAIVE_NASA, _l4) {
    ASSERT_NEAR(run_old_plog("oldplog/Examples/NASA/A4_prmod.plog",OldPlogMode::NAIVE), 0.059235, 1e-5);
}



TEST(PERF_OLDVERSION_NAIVE_NASA, _fgl4) {
    ASSERT_NEAR(run_old_plog("oldplog/Examples/NASA/Fprmod.plog",OldPlogMode::NAIVE), 0.905719, 1e-5);
}

TEST(OLDVERSION_NAIVE_NASA, _fgl4rdn) {
    ASSERT_NEAR(run_old_plog("oldplog/Examples/NASA/Fprmod2.plog",OldPlogMode::NAIVE), 0.905719, 1e-5);
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

TEST(OLDVERSION_DCO_BLOCKS, _20x4) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_4.plg",OldPlogMode::DCOOPTIMIZED), 0.308153, 1e-5);
}

TEST(PERF_OLDVERSION_NAIVE_BLOCKS, _20x5) {
    ASSERT_NEAR(run_old_plog("oldplog/Examples/BlockWorld/blockmap20_5.plg",OldPlogMode::NAIVE), 0.191692, 1e-5);
}


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
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_3_3.txt",OldPlogMode::NAIVE), 0.490908, 1e-5);
}


TEST(OLDVERSION_NAIVE_POKER, _3x4) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_3_4.txt",OldPlogMode::NAIVE), 0.514286, 1e-5);
}

TEST(OLDVERSION_NAIVE_POKER, _3x5) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_3_5.txt",OldPlogMode::NAIVE), 0.526316, 1e-5);
}




TEST(OLDVERSION_DCO_POKER, _3x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_3_3.txt",OldPlogMode::DCOOPTIMIZED), 0.490908, 1e-5);
}


TEST(OLDVERSION_DCO_POKER, _3x4) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_3_4.txt",OldPlogMode::DCOOPTIMIZED), 0.514286, 1e-5);
}

TEST(OLDVERSION_DCO_POKER, _3x5) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_3_5.txt",OldPlogMode::DCOOPTIMIZED), 0.526316, 1e-5);
}




TEST(OLDVERSION_NAIVE_POKER, _5x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_5_3.txt",OldPlogMode::NAIVE), 0.454544, 1e-5);
}


TEST(OLDVERSION_NAIVE_POKER, _5x4) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_5_4.txt",OldPlogMode::NAIVE), 0.417582, 1e-5);
}

TEST(OLDVERSION_NAIVE_POKER, _5x5) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_5_5.txt",OldPlogMode::NAIVE), 0.399897, 1e-5);
}




TEST(OLDVERSION_NAIVE_POKER, _5x6) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_5_6.txt",OldPlogMode::NAIVE), 0.547344, 1e-5);
}

TEST(PERF_OLDVERSION_NAIVE_POKER, _5x4x36) {
    ASSERT_NEAR(run_old_plog("oldplog/Examples/Poker/poker_5_4_36.txt",OldPlogMode::NAIVE), 0.372804, 1e-5);
}



TEST(OLDVERSION_DCO_POKER, _5x3) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_5_3.txt",OldPlogMode::DCOOPTIMIZED), 0.454544, 1e-5);
}


TEST(OLDVERSION_DCO_POKER, _5x4) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_5_4.txt",OldPlogMode::DCOOPTIMIZED), 0.417582, 1e-5);
}

TEST(OLDVERSION_DCO_POKER, _5x5) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_5_5.txt",OldPlogMode::DCOOPTIMIZED), 0.399897, 1e-5);
}


TEST(OLDVERSION_DCO_POKER, _5x6) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_5_6.txt",OldPlogMode::DCOOPTIMIZED), 0.547344, 1e-5);
}


//TEST(OLDVERSION_DCO_POKER, _5x4x36) {
//    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Poker/poker_5_4_36.txt",OldPlogMode::DCOOPTIMIZED), 0.547344, 1e-5);
//}
//TEST(OLDVERSION_NAIVE_BLOCKS, _20x7) {
//    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_7.plg",OldPlogMode::NAIVE), 0.0549278, 1e-5);
//}

TEST(OLDVERSION_DCO_BLOCKS, _20x5) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/BlockWorld/blockmap20_5.plg",OldPlogMode::DCOOPTIMIZED), 0.191692, 1e-5);
}

TEST(OLDVERSION_DCO_SQ, _1) {
    ASSERT_NEAR(run_old_plog("../../plog/oldplog/Examples/Squirrel/pr.plog", OldPlogMode::DCOOPTIMIZED), 0.152380, 1e-4);
}

TEST(PERF_OLDVERSION_NAIVE_SQ, _1) {
    ASSERT_NEAR(run_old_plog("oldplog/Examples/Squirrel/pr.plog",OldPlogMode::NAIVE),0.152380, 1e-4);
}
