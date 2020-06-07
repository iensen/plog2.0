//
// Created by iensen on 12/23/16.
//

#pragma once

#include<string>


enum class OldPlogMode {
    NAIVE, DCOOPTIMIZED
};

enum class NewPlogMode {
    QUERY_DCO, QUERY_NAIVE,POSSIBLE_WORLDS,CAUSES
};


double run_plog(const std::string& file, NewPlogMode mode = NewPlogMode::QUERY_DCO);
double run_old_plog(std::string file, OldPlogMode mode);