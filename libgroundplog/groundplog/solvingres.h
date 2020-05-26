//
// Created by evgenii on 12/16/16.
//

#ifndef PLOG_SOLVINGRES_H
#define PLOG_SOLVINGRES_H
#include<groundplog/util/platform.h>
/////////////////////////////////////////////////////////////////////////////////////////
// GroundPlogFacade
/////////////////////////////////////////////////////////////////////////////////////////
//! Result of a solving
namespace GroundPlog {

struct SolveResult {
    bool success;
    double prob;
    SolveResult(bool success, double prob):success(success), prob(prob){}
};
}
#endif //PLOG_SOLVINGRES_H
