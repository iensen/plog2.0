//
// Created by iensen on 9/3/16.
//

#include <plog/input/utils.h>
#include <groundplog/solve_algorithms.h>
#include<queue>
#include <groundplog/clingo_control.h>


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

static bool startswith(const char* src, const char* pattern) {
    while(*pattern !=0) {
        if(*src == 0){
            return false;
        }
        if(*pattern != *src) {
            return false;
        }
        ++src;
        ++pattern;
    }
    return true;

}

// Computes the number of possible values of a given attribute term in a given model
// @param dynRangeAtt is the name of the attribute term which is used to specify dynamic range of the attribute term
// in a given model. If there is no dynamic range, dynRangeAtt is empty.
// @param modelAttValue represents a model. modelAttvalue[a(t)] = y iff a(t) = y in a given model.
// @param inputProgram is the program for which the model was computed
size_t GroundPlog::NaiveSolve::getAttributeRangeElemCount(const std::string &attribute, const std::string &dynRangeAtt,
                                                          std::unordered_map<std::string, std::string> &modelAttValue,
                                                          Plog::Program *inputProgram) {
    if (dynRangeAtt.empty()) {
        auto cache = attributeRangeElemCountCache.find(attribute);
        if (cache != attributeRangeElemCountCache.end()) {
            return cache->second;
        } else {
            return attributeRangeElemCountCache[attribute] = inputProgram->getAttributeRangeElements(attribute).size();
        }
    }
    auto attributeValues = inputProgram->getAttributeRangeElements(attribute);
    return std::count_if(attributeValues.begin(), attributeValues.end(),
                         [&](const Clingo::AST::Term &value) {
                             auto att =  dynRangeAtt + "(" + term_to_string(value) + ")";
                             auto it =  modelAttValue.find(att);
                             return it != modelAttValue.end() && it->second == "true";
                         });

}

static bool isTrueInModel(const std::string& att, const  std::unordered_map<std::string, std::string> modelAttValue)  {
    auto it = modelAttValue.find(att);
    if(it!=modelAttValue.end()) {
        return it->second == "true";
    }
}
// Compute statistics for the given model.
GroundPlog::NaiveSolve::ModelStats GroundPlog::NaiveSolve::getModelStats(const Clingo::Model & model,  Plog::Program* inputProgram) {
    const Clingo::SymbolVector &atvec = model.symbols();
    // trulyRandomAtts[i].first is the attribute name, trylyRandomAtts[i].second is the name of dynamic range
    // if there is no dynamic range, stores empty string.
    std::vector<std::pair<std::string, std::string>> trulyRandomAtts;
    // modelAttValue[a] = y if and only if the model contains atom a = y
    std::unordered_map<std::string, std::string> modelAttValue;
    // knownProbs[a][y] is c if and only if the model has satisfied pr-atom pr(a = y) = c
    std::unordered_map<std::string, std::unordered_map<std::string, double>> knownProbs;

    bool isQueryTrue = false;

    for (const Clingo::Symbol &s : atvec) {
        auto const name = s.name();
        // truly_random:
        if(startswith(name,"__t")) {
            if(s.arguments().size() == 1) {
                trulyRandomAtts.emplace_back(std::make_pair<std::string, std::string>(s.arguments()[0].to_string(),""));
            } else {
                trulyRandomAtts.emplace_back(std::make_pair<std::string, std::string>(s.arguments()[0].to_string(),s.arguments()[1].to_string()));
            }

            continue;
        }
        if(startswith(name,"__q")) {
            isQueryTrue = true;
            continue;
        }
        //pr-atom
        if(startswith(name, "__pr")) {
            auto const attribute_term = s.arguments()[0].to_string();
            auto const value = s.arguments()[1].to_string();
            auto const numQuotedString = s.arguments()[2].to_string();
            auto const num = std::stoi(numQuotedString.substr(1,numQuotedString.size()-2));
            auto const denumQuotedString = s.arguments()[3].to_string();
            auto const denum = std::stoi(denumQuotedString.substr(1,denumQuotedString.size()-2));
            knownProbs[attribute_term][value] = double(num)/denum;
            continue;
        }

        if(!startswith(name, "_")) {
            std::string attribute_term = name;
            if(s.arguments().size() > 1) {
                attribute_term += "(";
                for(size_t i = 0; i < s.arguments().size()-1; i++) {
                    if(i != 0) {
                        attribute_term +=",";
                    }
                    attribute_term += s.arguments()[i].to_string();
                }
                attribute_term +=")";
            }
            auto const& value = s.arguments().back().to_string();
            modelAttValue[attribute_term] = value;
        }
    }

    double probability = 1.0;
    for(auto const & truly_random_att_pair : trulyRandomAtts){
        auto const & truly_random_att = truly_random_att_pair.first;
        auto const & dyn_range_att = truly_random_att_pair.second;
        auto const & value = modelAttValue.at(truly_random_att);
        // defined probability:
        auto knownProbsForAtt = knownProbs.find(truly_random_att);
        if(knownProbsForAtt != knownProbs.end()) {
            auto knownProbForAttValue = knownProbsForAtt->second.find(value);
            if(knownProbForAttValue != knownProbsForAtt->second.end()) {
                probability *= knownProbForAttValue->second;
                continue;
            }
        }

        // default probability:
        if(knownProbsForAtt != knownProbs.end()) {
            double sumKnownProb = 0.0;
            // the number of values for which we have a defined probability
            size_t definedProbValueCount = 0;
            for(auto const & attProb: knownProbsForAtt->second) {
                // only add this probability if it belongs to dynamic range
                if(dyn_range_att.empty() || isTrueInModel(dyn_range_att + "(" + value + ")", modelAttValue)) {
                    sumKnownProb += attProb.second;
                    ++ definedProbValueCount;
                }
            }
            std::string attName;
            auto lParenPos = truly_random_att.find('(');
            if( lParenPos == std::string::npos) {
                attName = truly_random_att;
            } else {
                attName = truly_random_att.substr(0,lParenPos);
            }
            // assume no dyhnamic range
            probability *=(1.0 - sumKnownProb)/(getAttributeRangeElemCount(attName, dyn_range_att, modelAttValue, inputProgram) - definedProbValueCount);
            continue;
        }
    }
    return {probability, isQueryTrue};
}

std::pair<bool, double> GroundPlog::NaiveSolve::computeProbabilityFromModels(Clingo::SolveHandle models, Plog::Program* inputProgram) {
    double totalProbability = 0.0;
    double queryProbability = 0.0;
    bool status = true;
    for(auto const & model : models) {
        //std::cout << model << std::endl;
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
