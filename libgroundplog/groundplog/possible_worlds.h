//
// Created by iensen on 8/21/16.
//

#pragma  once

#include <groundplog/solver_strategies.h>
#include <clingo.hh>
#include "program_types.h"
#include "solvingres.h"
#include "dependency_graph.h"
#include "interpretation.h"
#include "attribute_selection_heuristic.h"
#include "value_selection_heuristic.h"
#include <unordered_set>
#include <plog/input/program.h>
#include "state.h"

namespace GroundPlog {
    class PossibleWorldsComputer {
     public:
        PossibleWorldsComputer(GroundPlog::Program *groundProgram, Plog::Program* inputProgram, Clingo::Control *cControl);
        void run();
    private:
        const GroundPlog::Program *groundProgram;
        const Plog::Program* nonGroundProgram;
        Clingo::Control* cControl;
        void printModel(const Clingo::Model&);
        // stores how many models were printed
        size_t modelsPrinted = 0;
    };
}