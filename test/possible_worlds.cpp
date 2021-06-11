//
// Created by iensen on 6/13/20.
//

#include "gtest/gtest.h"
#include "utils.h"
#include "plog/plog.h"

// assert that two possible worlds in output (computed by P-log solver) are the same as in the manually
// defined output string
static void assert_eq(const std::vector<std::pair<std::string, double>> &output, const std::string& expected, Format format = text) {

    auto expected_output = format == text? parse_possible_worlds(expected): parse_possible_worlds_json(expected);
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


TEST(NEWVERSION_POSSIBLEWORLDS, 1) {
    std::string expected = "[\n"
                           "  {\n"
                           "    \"possible_world\" :\n"
                           "    [\n"
                           "      {\n"
                           "        \"attribute_term\" : \"hidden_in\",\n"
                           "        \"value\" : \"p1\"\n"
                           "      },\n"
                           "      {\n"
                           "        \"attribute_term\" : \"found(2)\",\n"
                           "        \"value\" : \"true\"\n"
                           "      }\n"
                           "    ],\n"
                           "    \"probability\" : 0.100000\n"
                           "  },\n"
                           "  {\n"
                           "    \"possible_world\" :\n"
                           "    [\n"
                           "      {\n"
                           "        \"attribute_term\" : \"hidden_in\",\n"
                           "        \"value\" : \"p2\"\n"
                           "      },\n"
                           "      {\n"
                           "        \"attribute_term\" : \"found(2)\",\n"
                           "        \"value\" : \"false\"\n"
                           "      }\n"
                           "    ],\n"
                           "    \"probability\" : 0.500000\n"
                           "  },\n"
                           "  {\n"
                           "    \"possible_world\" :\n"
                           "    [\n"
                           "      {\n"
                           "        \"attribute_term\" : \"hidden_in\",\n"
                           "        \"value\" : \"p1\"\n"
                           "      },\n"
                           "      {\n"
                           "        \"attribute_term\" : \"found(2)\",\n"
                           "        \"value\" : \"false\"\n"
                           "      }\n"
                           "    ],\n"
                           "    \"probability\" : 0.400000\n"
                           "  }\n"
                           "]";

    assert_eq(compute_possible_worlds_json("plogapp/tests/simple"), expected, json);
}

TEST(NEWVERSION_POSSIBLEWORLDS, FuncSort) {
    std::string expected = "Possible Worlds:\n"
                           "1: {p(f(1,1)), p(f(1,2)), p(f(2,1)), p(f(2,2)), p(f(3,1)), p(f(3,2))}\n"
                           "\n\nProbabilities:\n"
                           "1: 1.0\n";

    assert_eq(compute_possible_worlds("plogapp/tests/funcSort.plog"), expected);
}

TEST(NEWVERSION_POSSIBLEWORLDS, BinOpSort) {
    std::string expected = "Possible Worlds:\n"
                           "1: {p(2), q(1), q(2), q(3), r(1)}\n"
                           "\n\nProbabilities:\n"
                           "1: 1.0\n";

    assert_eq(compute_possible_worlds("plogapp/tests/binopSort.plog"), expected);
}


