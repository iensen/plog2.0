//
// Created by iensen on 6/6/20.
//

#include "gtest/gtest.h"
#include "utils.h"

TEST(NEWVERSION_NAIVE, _simple) {
    ASSERT_NEAR(compute_query("plogapp/tests/rshortwithpratom.plog", NewPlogMode::QUERY_NAIVE), 0.25, 1e-5);
}

TEST(PERF_NEWVERSION_NAIVE_BLOCKS, _20x5) {
    ASSERT_NEAR(compute_query("plogapp/tests/weijuns_testsuite/Blocks/blockmap20_5.plg", NewPlogMode::QUERY_NAIVE), 0.191692, 1e-5);
}

TEST(NEWVERSION_NAIVE, 0) {
    ASSERT_NEAR(compute_query("plogapp/tests/p1.plog", NewPlogMode::QUERY_NAIVE), 0.30, 1e-8);
}

TEST(NEWVERSION_NAIVE, 1) {
    ASSERT_NEAR(compute_query("plogapp/tests/triv0.plog", NewPlogMode::QUERY_NAIVE), 1.0, 1e-8);
}

TEST(NEWVERSION_NAIVE, 2) {
    ASSERT_NEAR(compute_query("plogapp/tests/triv1.plog", NewPlogMode::QUERY_NAIVE), 0.0, 1e-8);
}

TEST(NEWVERSION_NAIVE, 3) {
    ASSERT_NEAR(compute_query("plogapp/tests/rels0.plog",  NewPlogMode::QUERY_NAIVE), 1.0, 1e-8);
}


TEST(NEWVERSION_NAIVE, 4) {
    ASSERT_NEAR(compute_query("plogapp/tests/rels.plog", NewPlogMode::QUERY_NAIVE), 0.5, 1e-8);
}

TEST(NEWVERSION_NAIVE, 5) {
    ASSERT_NEAR(compute_query("plogapp/tests/rshort.plog", NewPlogMode::QUERY_NAIVE), 1.0 / 3.0, 1e-5);
}

TEST(NEWVERSION_NAIVE, 6) {
    ASSERT_NEAR(compute_query("plogapp/tests/obs1.plog", NewPlogMode::QUERY_NAIVE), 1.0, 1e-5);
}


TEST(NEWVERSION_NAIVE, 7) {
    ASSERT_NEAR(compute_query("plogapp/tests/obs2.plog", NewPlogMode::QUERY_NAIVE), 0.0, 1e-5);
}


TEST(NEWVERSION_NAIVE, 8) {
    ASSERT_NEAR(compute_query("plogapp/tests/paper/dice1.plog", NewPlogMode::QUERY_NAIVE), 0.15, 1e-5);
}

TEST(NEWVERSION_NAIVE, 9) {
    ASSERT_NEAR(compute_query("plogapp/tests/paper/dice2.plog", NewPlogMode::QUERY_NAIVE), 0.15, 1e-5);
}

TEST(NEWVERSION_NAIVE, 10) {
    ASSERT_NEAR(compute_query("plogapp/tests/paper/dice3.plog", NewPlogMode::QUERY_NAIVE), 1.0 / 6.0, 1e-5);
}

TEST(NEWVERSION_NAIVE, monty1) {
    ASSERT_NEAR(compute_query("plogapp/tests/paper/monty1.plog", NewPlogMode::QUERY_NAIVE), 0.33333, 1e-5);
}

TEST(NEWVERSION_NAIVE, 12) {
    ASSERT_NEAR(compute_query("plogapp/tests/paper/monty2.plog", NewPlogMode::QUERY_NAIVE), 0.0, 1e-5);
}

TEST(NEWVERSION_NAIVE, 13) {
    ASSERT_NEAR(compute_query("plogapp/tests/paper/monty3.plog", NewPlogMode::QUERY_NAIVE), 0.66666, 1e-5);
}


TEST(NEWVERSION_NAIVE, 14) {
    ASSERT_NEAR(compute_query("plogapp/tests/rsort.plog", NewPlogMode::QUERY_NAIVE), 0.111111, 1e-5);
}

TEST(NEWVERSION_NAIVE, 15) {
    ASSERT_NEAR(compute_query("plogapp/tests/do1.plog", NewPlogMode::QUERY_NAIVE), 0.3, 1e-5);
}

TEST(NEWVERSION_NAIVE, CLINGO_CONSEQUENCES) {
    ASSERT_NEAR(compute_query("plogapp/tests/clingocons.plog", NewPlogMode::QUERY_NAIVE), 0.5, 1e-5);
}

TEST(NEWVERSION_NAIVE, CONSTRAINT) {
    ASSERT_NEAR(compute_query("plogapp/tests/constraint.plog", NewPlogMode::QUERY_NAIVE), 0.5, 1e-5);
}

TEST(PERF_NEWVERSION_NAIVE_NASA, _l4) {
    ASSERT_NEAR(compute_query("plogapp/tests/nasa/A4n.plog", NewPlogMode::QUERY_NAIVE), 0.059235, 1e-5);
}


TEST(PERF_NEWVERSION_NAIVE_NASA, _fgl4) {
    ASSERT_NEAR(compute_query("plogapp/tests/nasa/F.plog", NewPlogMode::QUERY_NAIVE), 0.905719, 1e-5);
}


TEST(PERF_NEWVERSION_NAIVE_NASA, _fgl4rdn) {
    ASSERT_NEAR(compute_query("plogapp/tests/nasa/F2.plog", NewPlogMode::QUERY_NAIVE), 0.905719, 1e-5);
}

TEST(NEWVERSION_NAIVE_BLOCKS, _20x1) {
    ASSERT_NEAR(compute_query("plogapp/tests/weijuns_testsuite/Blocks/blockmap20_1.plg",NewPlogMode::QUERY_NAIVE), 0.8, 1e-5);
}

TEST(NEWVERSION_NAIVE_BLOCKS, _20x2) {
    ASSERT_NEAR(compute_query("plogapp/tests/weijuns_testsuite/Blocks/blockmap20_2.plg",NewPlogMode::QUERY_NAIVE), 0.621053, 1e-5);
}

TEST(NEWVERSION_NAIVE, _CR_RULE) {
    ASSERT_NEAR(compute_query("plogapp/tests/weijuns_testsuite/Blocks/blockmap20_2.plg",NewPlogMode::QUERY_NAIVE), 0.621053, 1e-5);
}

TEST(PERF_NEWVERSION_NAIVE_BLOCKS, _20x3) {
    ASSERT_NEAR(compute_query("plogapp/tests/weijuns_testsuite/Blocks/blockmap20_3.plg",NewPlogMode::QUERY_NAIVE), 0.454386, 1e-5);
}


TEST(PERF_NEWVERSION_NAIVE_BLOCKS, _20x4) {
    ASSERT_NEAR(compute_query("plogapp/tests/simplecrrule.plog",NewPlogMode::QUERY_NAIVE), 0.5, 1e-5);
}

TEST(NEWVERSION_NAIVE_POKER, _5x3) {
    ASSERT_NEAR(compute_query("plogapp/tests/weijuns_testsuite/Poker/poker_5_3.txt",NewPlogMode::QUERY_NAIVE), 0.545455, 1e-5);
}


TEST(PERF_NEWVERSION_NAIVE_POKER, _5x4) {
    ASSERT_NEAR(compute_query("plogapp/tests/weijuns_testsuite/Poker/poker_5_4.txt",NewPlogMode::QUERY_NAIVE), 0.417582, 1e-5);
}

TEST(PERF_NEWVERSION_NAIVE_POKER, _5x5) {
    ASSERT_NEAR(compute_query("plogapp/tests/weijuns_testsuite/Poker/poker_5_5.txt",NewPlogMode::QUERY_NAIVE), 0.399897, 1e-5);
}

TEST(PERF_NEWVERSION_NAIVE_POKER, _5x6) {
    ASSERT_NEAR(compute_query("plogapp/tests/weijuns_testsuite/Poker/poker_5_6.txt",NewPlogMode::QUERY_NAIVE), 0.547344, 1e-5);
}

TEST(PERF_NEWVERSION_NAIVE_POKER, _5x4x36) {
    ASSERT_NEAR(compute_query("plogapp/tests/weijuns_testsuite/Poker/poker_5_4_36.txt",NewPlogMode::QUERY_NAIVE), 0.372804, 1e-5);
}


TEST(PERF_NEWVERSION_NAIVE_SQ, _1) {
    ASSERT_NEAR(compute_query("plogapp/tests/squirrel.plog",NewPlogMode::QUERY_NAIVE), 0.152380, 1e-4);
}

TEST(NEWVERSION_NAIVE, _dostmt) {
    ASSERT_NEAR(compute_query("plogapp/tests/donaive.plog",NewPlogMode::QUERY_NAIVE), 1.0, 1e-4);
}

TEST(NEWVERSION_NAIVE, _issue18) {
    ASSERT_NEAR(compute_query("plogapp/tests/multipleabdsupports.plog",NewPlogMode::QUERY_NAIVE), 0.5, 1e-4);
}

