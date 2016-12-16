//
// Created by iensen on 8/21/16.
//

#ifndef PLOG_SOLVE_ALGORITHM_H
#define PLOG_SOLVE_ALGORITHM_H

#include <groundplog/solver_strategies.h>
#include <clingo.hh>
#include "literal.h"
#include "program_types.h"
#include "solvingres.h"

namespace GroundPlog {



    class SolveAlgorithm {
    public:
        virtual SolveResult run(Program *ctl, Clingo::Control *pControl) = 0;
    };



    class ExactDCOSolve : public SolveAlgorithm {
    public:
        SolveResult run(Program *ctl, Clingo::Control *pControl) override;

    };

}

#endif //PLOG_SOLVE_ALGORITHM_H
