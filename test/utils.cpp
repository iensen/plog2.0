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

static double parse_new_plog_output(const std::string &out) {
    int index = 0;
    while(out[index]!='a') ++ index;
    while(!isdigit(out[index])) ++ index;
    return std::stod(out.substr(index));
}

double run_plog(const std::string& file, NewPlogMode mode) {
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
            app.main(2, argv);
            break;
        }
        default:
            assert(mode == NewPlogMode::QUERY_NAIVE);
            const std::string naiveAlgoOption = "--algo=naive";
            argv[2] = const_cast<char*>(naiveAlgoOption.c_str());
            app.main(3, argv);
    }
    std::string output = testing::internal::GetCapturedStdout();
    delete[] argv[0];
    delete[] argv[1];
    delete[] argv;
    return parse_new_plog_output(output);
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
