//
// Created by iensen on 9/3/16.
//

#include <plog/input/utils.h>
#include <groundplog/solve_algorithms.h>
#include<queue>
#include <groundplog/clingo_control.h>
#include <groundplog/util/clingo_model_utils.h>


GroundPlog::SolveResult GroundPlog::ExactDCOSolve::run(GroundPlog::Program *prg, Plog::Program *inputPrg, Clingo::Control *cControl) {
    dg = new DepGraph(prg);
    State s(dg,prg);
    AttributeSelectionHeuristic ash;
    ValueSelectionHeuristic vhs;
    auto p = GetCompletionProb(s, cControl, ash, vhs);
    if(std::get<0>(p)) {
        double num = std::get<1> (p);
        double denum = std::get<2> (p);
        return SolveResult(true, num/denum);
    }
    else
        return SolveResult(false, 0.0);

}


std::tuple<bool, double, double> GroundPlog::ExactDCOSolve::GetCompletionProb( GroundPlog::State &S,
                                                                               Clingo::Control *cControl,
                                                                               const AttributeSelectionHeuristic & heu,
                                                                               const ValueSelectionHeuristic & heuv
) {
    extend(S, cControl);
    // check if any of the value checking axioms is falsified:

    // check actions:
    for(const Action a: S.getProgram()->actions) {
        if(S.getValue(a.attid)!=UNASSIGNED && S.getValue(a.attid)!=a.valid)
            return std::tuple<bool, double, double> {true, 0, 0};
    }
    // check observations:
    for(const Observation o: S.getProgram()->observations) {
        if(o.positive) {
            if(S.getValue(o.attid)!=UNASSIGNED && S.getValue(o.attid)!=o.valid) {
                return std::tuple<bool, double, double> {true, 0, 0};
            }
        } else {
            if(S.getValue(o.attid)!=UNASSIGNED && S.getValue(o.attid)==o.valid) {
                return std::tuple<bool, double, double> {true, 0, 0};
            }
        }
    }

    // if all actions and observations are decided

    bool all_acts_and_obs_decided = true;

    // check actions:
    for(const Action a: S.getProgram()->actions) {
        if(S.getValue(a.attid)==UNASSIGNED)
            all_acts_and_obs_decided = false;
    }
    // check observations:
    for(const Observation o: S.getProgram()->observations) {
        if(S.getValue(o.attid)==UNASSIGNED) {
            all_acts_and_obs_decided = false;
        }
    }

    // lines 23-24
    if(all_acts_and_obs_decided && S.getValue(S.getProgram()->query.attid)!=UNASSIGNED) {
        double p = S.getProgram()->Probability(S.getI());
        if(S.getI().guarantees(S.getProgram()->query)) {
            return std::tuple<bool, double, double> {true, p, p};
        } else {
            return std::tuple<bool, double, double> {true, 0, p};
        }
    }

    std::vector<ATTID> readyatts = S.getRDYRAT();
    std::unordered_set<ATTID> readyattsset(readyatts.begin(), readyatts.end());
    //std:: cout << readyatts.size() << std::endl;
    while(!readyattsset.empty()) {
        ATTID selected = heu.select(readyattsset);
        readyattsset.erase(selected);
        auto res = GetCompletionProbA(S, cControl,heu,heuv,selected);
        if(std::get<0>(res)) {
            return res;
        }
    }
    // backtrack the extend assignment!
    return std::tuple<bool, double, double>{false,0.0,0.0};
}




ClingoModelRep modelToASPIfs(const Clingo::Model &m, Clingo::Control *cControl) {
    ClingoModelRep result;
    const Clingo::SymbolVector &atvec = m.symbols();
    for (const Clingo::Symbol &s : atvec) {
        auto at = cControl->symbolic_atoms().find(s);
        result.push_back(at->literal());
    }
    return result;
}




void GroundPlog::ExactDCOSolve::extend(GroundPlog::State &S, Clingo::Control *cControl) {


    bool updated;
    do {
        updated = false;
        if (!S.hasAssignmentToRandom()) {
            updated|=S.initClosure();
        }
        int U= S.LastLevelUndecidedCount();
        if (U>0) {
            updated|=S.AtMost();
        }
    }while(updated);


    if(S.LastLevelUndecidedCount()>0){
        std::cout << "Warning: Clingo Called!" << std::endl;
        std::unordered_set<unsigned> P_I = P(S);
        Clingo_Result m = call_clingo(cControl, P_I);
        if (!m.unique_model)
            return;
        for (clingo_literal_t clitid: m.m) {
            // if this is a known thing, and it's not in the interpretation already, we need to update
            // the interpretation:
            if (S.getProgram()->clingo_to_plog_lit.find(abs(clitid)) != S.getProgram()->clingo_to_plog_lit.end()) {
                Lit_t plogLit = S.getProgram()->clingo_to_plog_lit[abs(clitid)];
                // we only care about positive literals:
                if (!plogLit.classicNeg && S.getValue(plogLit.attid) == UNASSIGNED)
                    S.assignNonRandom(plogLit.attid, plogLit.valid);
            }
        }
        for (ATTID a : S.getLastLevelDAT()) {
            if (S.getValue(a) == UNASSIGNED)
                S.assignNonRandom(a, UNDEFINED);
        }
    }
}

std::unordered_set<ATTID> GroundPlog::ExactDCOSolve::bfs(const std::unordered_set<ATTID> & init, GroundPlog::DepGraph *dg) {
    std::unordered_set<ATTID> result = init;
    std::queue<ATTID> Q;
    for(ATTID attid: init)
        Q.push(attid);
    while(!Q.empty()) {
        ATTID c = Q.front();
        Q.pop();
        for(ATTID n:dg->children(c)) {
            if(result.find(n) == result.end()) {
                result.insert(n);
                Q.push(n);
            }
        }
    }
    return result;
}


std::unordered_set<unsigned int> GroundPlog::ExactDCOSolve::P(const State &S) {
    std::vector<ATTID> ats = S.getRAT();
    std::vector<ATTID> datats = S.getDAT();
    ats.insert(ats.end(), datats.begin(),datats.end());
    std::unordered_set<unsigned> rule_ext_ids = S.getProgram() -> getExternalsForSubprogramConstructedFrom(ats);
    std::unordered_set<unsigned> atom_ext_ids = S.getProgram() -> getExternalsForAtomsFrom(S.getI());
    atom_ext_ids.insert(rule_ext_ids.begin(), rule_ext_ids.end());
    return atom_ext_ids;
}

GroundPlog::Clingo_Result
GroundPlog::ExactDCOSolve::call_clingo(Clingo::Control *clingoCtrl, std::unordered_set<unsigned> activeRules) {
    std::function<bool(unsigned int)> isRuleActive = [&activeRules](unsigned int externAtomId) {
        return activeRules.find(externAtomId) != activeRules.end();
    };
    auto control = PlogClingoControl(clingoCtrl, isRuleActive);

    auto modelIterator = control.getModels();
    // find the first model:
    auto const &  m1 = modelIterator.next();
    bool hadFirstModel = bool(m1);

    // this ClingoModelRep construction has to
    // occur here because right after we call .next()
    // m1 will be destroyed!
    ClingoModelRep mr = modelToASPIfs(m1, clingoCtrl);
    auto const & m2 = modelIterator.next();
    return Clingo_Result{hadFirstModel &&  !m2, mr};
}


std::tuple<bool, double, double>
GroundPlog::ExactDCOSolve::GetCompletionProbA( State &S,Clingo::Control *cControl,
                                              const AttributeSelectionHeuristic &heu,
                                              const ValueSelectionHeuristic &heuv, ATTID selectedATT) {
    double satsum = 0.0;
    double totalsum = 0.0;
    std::unordered_set<ValueRep> pvals= S.getProgram()->getPossibleValuesFor(selectedATT, S.getI());
    //std::cout << "size: " << pvals.size() << std::endl;
    while(!pvals.empty()) {
        ValueRep selectedVal = heuv.select(pvals);
        pvals.erase(selectedVal);
        S.increaseLevel();
        S.assignRandom(selectedATT,selectedVal);
        std::tuple<bool, double, double> comp = GetCompletionProb(S,cControl,heu,heuv);
        S.backTrackLevel();
        if(!std::get<0>(comp)) {
            return std::tuple<bool, double, double>{false,0,0};
        }
        satsum += std::get<1> (comp);
        totalsum += std::get<2> (comp);
    }
    return std::tuple<bool, double, double>{true, satsum, totalsum};
}

std::pair<bool, double> GroundPlog::NaiveSolve::computeProbabilityFromModels(Clingo::SolveHandle models, Plog::Program* inputProgram) {
    double totalProbability = 0.0;
    double queryProbability = 0.0;
    bool status = true;
    for(auto const & model : models) {
       // std::cout << model << std::endl;
        // don't care about 'intermediate' models computed by clingo
        // when optimize statement is present (ie., when the original program had cr-rules)
        if(!model.optimality_proven() && !model.cost().empty()) {
            continue;
        }
        ModelStats stats = getModelStats(model, inputProgram);
        totalProbability += stats.probability;
        if(stats.isQueryTrue) {
            queryProbability += stats.probability;
        }
    }
    if(totalProbability == 0.0) {
        status = false;
    }
    return {status, queryProbability/totalProbability};
}

GroundPlog::SolveResult GroundPlog::NaiveSolve::run(GroundPlog::Program *groundProgram, Plog::Program* inputProgram, Clingo::Control *cControl) {
    std::function<bool(unsigned int)> isRuleActive = [](unsigned int) {
        return false;
    };
    auto control = PlogClingoControl(cControl, isRuleActive);
    std::pair<bool, double> result = computeProbabilityFromModels(control.getModels(), inputProgram);
    return {result.first, result.second};
}
