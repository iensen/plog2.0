//
// Created by iensen on 6/6/20.
//

#include "utils.h"

#include <gtest/internal/gtest-port.h>
#include <Program.h>
#include <TrEngine.h>
#include "../plogapp/src/plog_app.h"

#include <Parse.h>
#include <Query.h>
#include <global.h>
#include <Grounder.h> //temporay
#include <pgEngine.h>
#include<cmath>
#include <regex>
//Vu's
#include <iostream>

static double parse_old_plog_output(std::string out) {
    const std::string pr_str ="probability";
    std::size_t pr_idx = out.find(pr_str);
    if(pr_idx ==std::string::npos) {
        return nan("");
    }
    std::size_t pr_start_idx = pr_idx + pr_str.length() + 2;
    std::size_t pr_end_idx = pr_start_idx;
    while(isdigit(out[pr_end_idx]) || out[pr_end_idx]=='.')
        ++pr_end_idx;
    return std::stod(out.substr(pr_start_idx,pr_end_idx-pr_start_idx+1));
}

static double parse_new_plog_query_output(const std::string &out) {
    int index = 0;
    while(out[index]!='a') ++ index;
    while(!isdigit(out[index])) ++ index;
    return std::stod(out.substr(index));
}

// Given a line 1: {insomnia = false, act = work, possible(work), possible(sleep)}
// Returns a "compressed" representation of the form "act=work,insomnia=false,possible(sleep),possible(work)",
// where atoms are sorted by
static std::string getPossibleWorldAtoms(const std::string& line) {
    std::vector<std::string> atoms;
    size_t currentIndex = 0;
    while(line[currentIndex] != '{') ++currentIndex;
    ++currentIndex;
    while(currentIndex < line.length()) {
        // get next atom:
        size_t openedParenthesis = 0;
        size_t prevIndex = currentIndex;
        while (openedParenthesis!=0 || (line[currentIndex] != ',' && line[currentIndex] != '}')) {
           if(line[currentIndex]=='(') ++ openedParenthesis;
           else if(line[currentIndex]==')') -- openedParenthesis;
           ++currentIndex;
        }
        atoms.push_back(line.substr(prevIndex,currentIndex-prevIndex));
        ++currentIndex;
    }
    std::sort(atoms.begin(), atoms.end());
    std::stringstream ss;
    std::regex spaceRegex("\\s+");
    for(size_t i = 0 ; i < atoms.size();i++) {
        if(i!=0) ss << ",";
        ss << std::regex_replace(atoms[i],spaceRegex,"");
    }
    return ss.str();
}

// given a line of the form i: Prob, where i is an itneger and Prob is a double, return Prob
static double getPossibleWorldProbability(const std::string &line) {
     int currentIndex = 0;
     while(line[currentIndex]!=':') ++currentIndex;
     ++currentIndex;
     return std::stod(line.substr(currentIndex));
}
// given output from possible words in json format, returns a set of pairs of the form
// <"a_1(t)=v_1,...,a_n(t_n)=v_n",p>, where a_1(t)=v_1,...,a_n(t_n)=v_n are atoms
// of the corresponding possible world, sorted in lexicographical order, and p is its probability
std::vector<std::pair<std::string, double>> parse_possible_worlds_json(const std::string & out) {
    std::stringstream ss(out);
    std::string line;

    std::vector<std::string> data;
    std::vector<std::string> possibleWorlds;
    std::vector<double> probabilities;

    std::vector<std::vector<std::string>> test_possibleWorlds;
    std::vector<std::string> current_possibleWorld;
    std::vector<std::string> test_probabilities;
    while (std::getline(ss, line, '\"')) {
        data.push_back(line);
    }

    for (int i=0; i<data.size(); ++i) {
        std::stringstream atom;

        if (data[i] == "possible_world") {
            if (!current_possibleWorld.empty()) {
                std::sort(current_possibleWorld.begin(), current_possibleWorld.end());
                test_possibleWorlds.push_back(current_possibleWorld);
                current_possibleWorld.clear();
            }
            continue;
        }

        if (data[i] == "attribute_term") {
            i+=2;
            atom << data[i] << " = ";
            i+=2;
            if (data[i] == "value") {
                i+=2;
                atom << data[i];
            }
            current_possibleWorld.push_back(atom.str());
        }


        if (data[i] == "probability") {
            i++;
            std::remove_if(data[i].begin(), data[i].end(), isspace);
            int pos = data[i].find('}') - 1;
            test_probabilities.push_back(data[i].substr(1, pos));
        }
    }
    test_possibleWorlds.push_back(current_possibleWorld);
    for(auto const & test_possibleWorld: test_possibleWorlds) {
        std::string possibleWorld;
        for(int i = 0; i < test_possibleWorld.size(); i++) {
            if(i!=0) {
                possibleWorld.push_back(',');
            }
            possibleWorld += test_possibleWorld.at(i);
        }
        possibleWorlds.push_back(possibleWorld);
    }

    for(auto const& test_probability: test_probabilities) {
        probabilities.push_back(std::stod(test_probability));
    }

    std::vector<std::pair<std::string, double>> result;
    assert(probabilities.size() == possibleWorlds.size());
    for (size_t i = 0; i < probabilities.size(); i++) {
        result.push_back({possibleWorlds[i], probabilities[i]});
    }
    std::sort(result.begin(), result.end());
    return result;
}

// given output from possible words, returns a set of pairs of the form
// <"a_1(t)=v_1,...,a_n(t_n)=v_n",p>, where a_1(t)=v_1,...,a_n(t_n)=v_n are atoms
// of the corresponding possible world, sorted in lexicographical order, and p is its probability
std::vector<std::pair<std::string, double>> parse_possible_worlds(const std::string &out) {
    std::stringstream ss(out);
    std::string line;
    bool gettingPossibleWorlds = false;
    bool gettingProbabilities = false;

    std::vector<std::string> possibleWorlds;
    std::vector<double> probabilities;
    std::regex versionLine("Plog\\s+\\d+\\.\\d+");
    while (std::getline(ss, line, '\n')) {
        if (line.empty()) continue;
        if(std::regex_match(line.c_str(), versionLine)) continue;

        if (line == "Possible Worlds:") {
            gettingPossibleWorlds = true;
        } else if (line == "Probabilities:") {
            gettingProbabilities = true;
            gettingPossibleWorlds = false;
        } else {
            if (gettingPossibleWorlds) {
                possibleWorlds.push_back(getPossibleWorldAtoms(line));
            } else {
                assert(gettingProbabilities);
                probabilities.push_back(getPossibleWorldProbability(line));
            }
        }
    }
    std::vector<std::pair<std::string, double>> result;
    assert(probabilities.size() == possibleWorlds.size());
    for (size_t i = 0; i < probabilities.size(); i++) {
        result.push_back({std::move(possibleWorlds[i]), probabilities[i]});
    }
    std::sort(result.begin(), result.end());
    return result;
}

double compute_query(const std::string& file, const NewPlogMode mode) {
    PlogApp app;
    char ** argv = new char*[4];
    argv[1] = new char[file.length() + 1];
    argv[0] = new char[5];
    argv[2] = nullptr;
    // our parser requires that argv[end] is nullptr
    argv[3] = nullptr;
    strcpy(argv[0], "plog");
    strcpy(argv[1], file.c_str());
    testing::internal::CaptureStdout();
    switch(mode) {
        case NewPlogMode::QUERY_DCO: {
            const std::string dcoAlgoOption = "--algo=dco";
            argv[2] = const_cast<char *>(dcoAlgoOption.c_str());
            app.main(3, argv);
            break;
        }
        default: {
            assert(mode == NewPlogMode::QUERY_NAIVE);
            const std::string naiveAlgoOption = "--algo=naive";
            argv[2] = const_cast<char *>(naiveAlgoOption.c_str());
            app.main(3, argv);
            break;
        }
    }
    std::string output = testing::internal::GetCapturedStdout();
    delete[] argv[0];
    delete[] argv[1];
    delete[] argv;
    return parse_new_plog_query_output(output);
}

std::vector<std::pair<std::string, double>> compute_possible_worlds(const std::string& file) {
    PlogApp app;
    char ** argv = new char*[4];
    argv[1] = new char[file.length() + 1];
    argv[0] = new char[5];
    argv[2] = nullptr;
    // our parser requires that argv[end] is nullptr
    argv[3] = nullptr;
    strcpy(argv[0], "plog");
    strcpy(argv[1], file.c_str());
    testing::internal::CaptureStdout();
    const std::string possibleWorldsOption = "--mode=pw";
    argv[2] = const_cast<char *>(possibleWorldsOption.c_str());
    app.main(3, argv);
    std::string output = testing::internal::GetCapturedStdout();
    delete[] argv[0];
    delete[] argv[1];
    delete[] argv;
    return parse_possible_worlds(output);
}
std::vector<std::pair<std::string, double>> compute_possible_worlds_json(const std::string& file) {
    PlogApp app;
    char ** argv = new char*[5];
    argv[1] = new char[file.length() + 1];
    argv[0] = new char[5];
    argv[2] = nullptr;

    argv[3] = nullptr;
    // our parser requires that argv[end] is nullptr
    argv[4] = nullptr;
    strcpy(argv[0], "plog");
    strcpy(argv[1], file.c_str());
    testing::internal::CaptureStdout();
    const std::string possibleWorldsOption = "--mode=pw";
    argv[2] = const_cast<char *>(possibleWorldsOption.c_str());
    const std::string jsonFormatOption = "--format=json";
    argv[3] = const_cast<char *>(jsonFormatOption.c_str());
    app.main(4, argv);
    std::string output = testing::internal::GetCapturedStdout();
    delete[] argv[0];
    delete[] argv[1];
    delete[] argv;
    return parse_possible_worlds_json(output);
}



double run_old_plog(std::string file, OldPlogMode mode){
    Program p;
    Query q;
    CParse parse(&p,&q);
    testing::internal::CaptureStdout();

    parse.SyntaxAnalysis(file);
    if(mode==OldPlogMode::NAIVE){
        TrEngine tr(&p,&q,"lp");
        tr.Solve();
    }
    else if(mode==OldPlogMode::DCOOPTIMIZED){
        pgEngine pg(&p,&q);
        pg.Run();
    }
    std::string output = testing::internal::GetCapturedStdout();
    return parse_old_plog_output(output);
}
