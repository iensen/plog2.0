//
// Created by iensen on 6/13/20.
//

#include "gtest/gtest.h"
#include "utils.h"

// assert that two possible worlds in output (computed by P-log solver) are the same as in the manually
// defined output string
static void assert_eq(const std::vector<std::pair<std::string, double>> &output, const std::string& expected) {
    auto expected_output = parse_possible_worlds(expected);
    ASSERT_EQ(expected_output.size(), output.size());
    for(size_t i = 0; i < output.size(); i++) {
        EXPECT_EQ(output[i].first, expected_output[i].first);
        EXPECT_NEAR(output[i].second, expected_output[i].second, 1e-5);
    }
}
TEST(NEWVERSION_POSSIBLEWORLDS, 0) {
    std::string expected = "Possible Worlds:\n"
                           "1: {insomnia = false, act = work, possible(work), possible(sleep)}\n"
                           "2: {insomnia, act = work, possible(sleep) = false, possible(work)}\n"
                           "3: {insomnia = false, act = sleep, possible(work), possible(sleep)}"
                           "\n\nProbabilities:\n"
                           "1: 0.21\n"
                           "2: 0.3\n"
                           "3: 0.49\n";

   assert_eq(compute_possible_worlds("plogapp/tests/insomnia_noquery.plog"), expected);
}
