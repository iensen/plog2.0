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
#include <plog/input/program.h>
#include "state.h"

using ClingoModelRep= std::vector<clingo_literal_t>;

namespace GroundPlog {

    struct Clingo_Result {
        bool unique_model;
        ClingoModelRep m;
    };

    class SolveAlgorithm {
    public:
       virtual SolveResult run(GroundPlog::Program *groundProgram, Plog::Program* inputProgram, Clingo::Control *cControl) = 0;
    };



    class ExactDCOSolve : public SolveAlgorithm {
    private:
        DepGraph *dg;
        AttributeSelectionHeuristic heur; // later this will be specified by options

    public:
        ExactDCOSolve(){};
        virtual SolveResult run(GroundPlog::Program *groundProgram, Plog::Program* inputProgram, Clingo::Control *cControl) override;
        static void extend(GroundPlog::State &S, Clingo::Control *cControl);
        static std::unordered_set<ATTID> bfs(const std::unordered_set<ATTID> &init,DepGraph *dg);
        static std::unordered_set<unsigned int> P(const State &S);
        static Clingo_Result call_clingo(Clingo::Control *c, std::unordered_set<unsigned> activeRules);
        static std::tuple<bool, double, double> GetCompletionProb(GroundPlog::State &S,
                                                                  Clingo::Control *cControl,
                                                                  const AttributeSelectionHeuristic & heu,
                                                                  const ValueSelectionHeuristic & heuv);

        static std::tuple<bool, double, double> GetCompletionProbA(State &S,Clingo::Control *cControl,
                                                                   const AttributeSelectionHeuristic &heu,
                                                                   const ValueSelectionHeuristic &heuv,
                                                                   ATTID selectedATT);
    };

    class NaiveSolve : public SolveAlgorithm {
    private:
        std::map<std::string,size_t> attributeRangeElemCountCache;
        std::pair<bool, double> computeProbabilityFromModels(Clingo::SolveHandle models, Plog::Program* inputProgram);
        size_t getAttributeRangeElemCount(const std::string& attribute, const std::string & dynRangeAtt,
                                          std::unordered_map<std::string, std::string> &modelAttValue, Plog::Program* inputProgram);
    public:
        NaiveSolve(){};

        virtual SolveResult run(GroundPlog::Program *groundProgram, Plog::Program* inputProgram, Clingo::Control *cControl) override;
    };
}

#endif //PLOG_SOLVE_ALGORITHM_H
