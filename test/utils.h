//
// Created by iensen on 12/23/16.
//

#pragma once

#include<string>
#include<vector>

enum class OldPlogMode {
    NAIVE, DCOOPTIMIZED
};

enum class NewPlogMode {
    QUERY_DCO, QUERY_NAIVE,POSSIBLE_WORLDS,CAUSES
};


double compute_query(const std::string& file, const NewPlogMode mode = NewPlogMode::QUERY_DCO);

// returns a (sorted) vector of possible worlds of a program in the format <"a_1=y_n,...,a_n=y_n", P>,
// where {a_1 = y_1, ...,a_n = y_n} is a possible world and P is its probability
std::vector<std::pair<std::string, double>> compute_possible_worlds(const std::string& file);

// returns possible worlds in the same format as compute_possible_worlds, but obtains them from
// a string solver might output (used for testing).
std::vector<std::pair<std::string, double>> parse_possible_worlds(const std::string& out);

// the two functions behave similarly to the ones without 'json' suffix, but they use json format instead
std::vector<std::pair<std::string, double>> parse_possible_worlds_json(const std::string& out);
std::vector<std::pair<std::string, double>> compute_possible_worlds_json(const std::string& file);

double run_old_plog(std::string file, OldPlogMode mode);

std::string get_error(const std::string& file);