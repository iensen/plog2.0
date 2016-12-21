//
// Created by iensen on 8/21/16.
//

#ifndef PLOG_SOLVE_ALGORITHM_H
#define PLOG_SOLVE_ALGORITHM_H

#include <groundplog/solver_strategies.h>
#include <clingo.hh>
#include "program_types.h"
#include "solvingres.h"
#include "dependency_graph.h"
#include "interpretation.h"
#include "attribute_selection_heuristic.h"
#include "value_selection_heuristic.h"
#include <unordered_set>


using ClingoModelRep= std::vector<clingo_literal_t>;

namespace GroundPlog {


    struct Clingo_Result {
        bool unique_model;
        ClingoModelRep m;
    };

    class SolveAlgorithm {
    public:
       virtual SolveResult run(Program *ctl, Clingo::Control *pControl) = 0;
    };



    class ExactDCOSolve : public SolveAlgorithm {
    private:
        DepGraph *dg;
        AttributeSelectionHeuristic heur; // later this will be specified by options

    public:
        ExactDCOSolve(){};
        virtual SolveResult run(Program *pr, Clingo::Control *pControl) override;
        static void extend(Interpretation &i, GroundPlog::Program *pr, Clingo::Control *cControl, DepGraph *dg);
        static std::unordered_set<ATTID> RAT(const Interpretation &i, Program *pr);
        static std::unordered_set<ATTID> DAT(const Interpretation &i, GroundPlog::Program *pr, DepGraph *dg);
        static std::unordered_set<ATTID> bfs(const std::unordered_set<ATTID> &init,DepGraph *dg);
        static std::unordered_set<unsigned int> P(Interpretation &interpretation, Program *pProgram, DepGraph *pGraph);
        static Clingo_Result call_clingo(Clingo::Control *c, std::unordered_set<unsigned> activeRules);
        static std::tuple<bool, double, double> GetCompletionProb(GroundPlog::Program *prg,
                                                                  Clingo::Control *cControl,
                                                                  Interpretation &I,
                                                                  DepGraph *dg,
                                                                  const AttributeSelectionHeuristic & heu,
                                                                  const ValueSelectionHeuristic & heuv);

        static std::tuple<bool, double, double> GetCompletionProbA(GroundPlog::Program *prg,
                                                                  Clingo::Control *cControl,
                                                                  Interpretation &I,
                                                                  DepGraph *dg,
                                                                  const AttributeSelectionHeuristic & heu,
                                                                  const ValueSelectionHeuristic & heuv,
                                                                  ATTID selectedATT);
    };
}

#endif //PLOG_SOLVE_ALGORITHM_H
