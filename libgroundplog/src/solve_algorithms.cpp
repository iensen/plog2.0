//
// Created by iensen on 9/3/16.
//


#include <groundplog/solve_algorithms.h>
#include<queue>

GroundPlog::SolveResult GroundPlog::ExactDCOSolve::run(GroundPlog::Program *prg, Clingo::Control *cControl) {
    dg = new DepGraph(prg);
    Interpretation I;
    AttributeSelectionHeuristic ash;
    ValueSelectionHeuristic vhs;
    auto p = GetCompletionProb(prg, cControl, I,dg, ash, vhs);
    if(std::get<0>(p)) {
        double num = std::get<1> (p);
        double denum = std::get<2> (p);
        return SolveResult(true, num/denum);
    }
    else
        return SolveResult(false, 0.0);

}


std::tuple<bool, double, double> GroundPlog::ExactDCOSolve::GetCompletionProb(GroundPlog::Program *prg,
                                                                              Clingo::Control *cControl,
                                                                              Interpretation &I,
                                                                              DepGraph *dg,
                                                                              const AttributeSelectionHeuristic & heu,
                                                                              const ValueSelectionHeuristic & heuv
) {
    extend(I, prg, cControl, dg);
    // check if any of the value checking axioms is falsified:

    // check actions:
    for(const Action a: prg->actions) {
        if(I.getVal(a.attid)!=UNASSIGNED && I.getVal(a.attid)!=a.valid)
            return std::tuple<bool, double, double> {true, 0, 0};
    }
    // check observations:
    for(const Observation o: prg->observations) {
        if(o.positive) {
            if(I.getVal(o.attid)!=UNASSIGNED && I.getVal(o.attid)!=o.valid) {
                return std::tuple<bool, double, double> {true, 0, 0};
            }
        } else {
            if(I.getVal(o.attid)!=UNASSIGNED && I.getVal(o.attid)==o.valid) {
                return std::tuple<bool, double, double> {true, 0, 0};
            }
        }
    }

    // if all actions and observations are decided

    bool all_acts_and_obs_decided = true;

    // check actions:
    for(const Action a: prg->actions) {
        if(I.getVal(a.attid)==UNASSIGNED)
            all_acts_and_obs_decided = false;
    }
    // check observations:
    for(const Observation o: prg->observations) {
        if(I.getVal(o.attid)==UNASSIGNED) {
            all_acts_and_obs_decided = false;
        }
    }

    // lines 23-24
    if(all_acts_and_obs_decided && I.getVal(prg->query.attid)!=UNASSIGNED) {
        double p = prg->Probability(I);
        if(I.guarantees(prg->query)) {
            return std::tuple<bool, double, double> {true, p, p};
        } else {
            return std::tuple<bool, double, double> {true, 0, p};
        }
    }

    std::unordered_set<ATTID> readyatts = prg->getReadyAtts(I);
    //std:: cout << readyatts.size() << std::endl;
    while(!readyatts.empty()) {
        ATTID selected = heu.select(readyatts);
        readyatts.erase(selected);
        auto res = GetCompletionProbA(prg, cControl,I,dg,heu,heuv,selected);
        if(std::get<0>(res)) {
            return res;
        }
    }
    // backtrack the extend assignment!
    return std::tuple<bool, double, double>{false,0.0,0.0};
}


/*
ClingoModelRep modelToASPIfs(const Clingo::Model &m, Clingo::Control *cControl) {
    //std::cout <<"MODEL HERE:"<< m << std::endl;
    ClingoModelRep result;
    Clingo::SymbolicAtoms ats = cControl->symbolic_atoms();
    const Clingo::SymbolVector &atvec = m.symbols();
    for (const Clingo::Symbol &s : atvec) {
        for (auto it = ats.begin(); it != ats.end(); it++) {
            if (s.to_c() == it->symbol().to_c()) {
                result.push_back(it->literal());
            }
        }
    }
    return result;
}
 */




ClingoModelRep modelToASPIfs(const Clingo::Model &m, Clingo::Control *cControl) {
    ClingoModelRep result;
    const Clingo::SymbolVector &atvec = m.symbols();
    for (const Clingo::Symbol &s : atvec) {
        auto at = cControl->symbolic_atoms().find(s);
        result.push_back(at->literal());
    }
    return result;
}



/*
void GroundPlog::ExactDCOSolve::extend(Interpretation &i, GroundPlog::Program *pr, Clingo::Control *cControl, DepGraph *dg) {
    std::unordered_set<unsigned> P_I= P(i,pr,dg);
    Clingo_Result m = call_clingo(cControl,P_I);
    if(!m.unique_model)
        return;
    for (clingo_literal_t clitid: m.m) {
        // if this is a known thing, and it's not in the interpretation already, we need to update
        // the interpretation:
        if (pr->clingo_to_plog_lit.find(abs(clitid)) != pr->clingo_to_plog_lit.end()) {
            Lit_t plogLit = pr->clingo_to_plog_lit[abs(clitid)];
            // we only care about positive literals:
            if (!plogLit.classicNeg && i.getVal(plogLit.attid)==UNASSIGNED)
                i.assign(plogLit.attid, plogLit.valid);
        }
    }

    std::unordered_set<ATTID> ids = DAT(i,pr,dg);
    for(ATTID a : ids) {
        if(i.getVal(a)==UNASSIGNED)
            i.assign(a,UNDEFINED);
    }
}



*/


void GroundPlog::ExactDCOSolve::extend(Interpretation &i, GroundPlog::Program *pr, Clingo::Control *cControl, DepGraph *dg) {

    // avoid calling clingo if unnecessary!
    std::unordered_set<ATTID> ids = DAT(i,pr,dg);
    std::unordered_set<ATTID> rPr = pr->getRandomAttributeTerms();
    //std::cout << ids.size() << std::endl;
    std::unordered_set<ATTID> att_unclear;

    x:
    bool need_to_search = true;

    while(need_to_search) {
        need_to_search = false;
        std::unordered_set<ATTID> has_rule;
        std::unordered_map<ATTID, std::unordered_set<ValueRep >> imposValues_candidates;
        std::unordered_map<ATTID, std::unordered_set<ValueRep >> posValues_candidates;
        for(const RegularRule &r: pr->rules) {
            if(i.getVal(r.head.attid)==UNASSIGNED){
                if(i.guarantees(r.body)) {
                    i.assign(r.head.attid, r.head.valid);
                    need_to_search = true;
                } else {
                    if(!i.falsifies(r.body)) {
                        has_rule.insert(r.head.attid);
                        posValues_candidates[r.head.attid].insert(r.head.valid);
                    } else {
                        imposValues_candidates[r.head.attid].insert(r.head.valid);
                    }
                }
            }
            for(Lit_t t:r.body) {
                if(i.getVal(t.attid)==UNASSIGNED && rPr.find(t.attid)==rPr.end())
                   imposValues_candidates[t.attid].insert(t.valid);
            }
        }


        for(auto c : imposValues_candidates) {
            for(auto val : c.second) {
                if(posValues_candidates[c.first].find(val)==posValues_candidates[c.first].end()) {
                    if(!i.is_impossible_val(c.first,val) && i.getVal(c.first)==UNASSIGNED) {
                        i.make_impossible(c.first, val);
                        need_to_search = true;
                    }
                }
            }
        }


        for(ATTID a: ids) {
            if(i.getVal(a)==UNASSIGNED && has_rule.find(a) == has_rule.end()) {
                i.assign(a, UNDEFINED);
                need_to_search = true;
            }
        }

    }

    bool need = AtMost(pr,i,ids);
    if(need) goto x;


    for(const RegularRule &r: pr->rules) {
        if (ids.find(r.head.attid) != ids.end() && i.getVal(r.head.attid)==UNASSIGNED)
            att_unclear.insert(r.head.attid);
    }




    // check that everything from datt is there
    bool all_dats_assigned = true;
    for(ATTID a: ids) {
        if(i.getVal(a)==UNASSIGNED && att_unclear.find(a)!=att_unclear.end()) {
            //std::cout <<"AAAA:" << a << std::endl;
            all_dats_assigned = false;
        }
    }
    if(!all_dats_assigned) {
        std::cout << "AAAA" << std::endl;
        std::unordered_set<unsigned> P_I = P(i, pr, dg);
        Clingo_Result m = call_clingo(cControl, P_I);
        if (!m.unique_model)
            return;
        for (clingo_literal_t clitid: m.m) {
            // if this is a known thing, and it's not in the interpretation already, we need to update
            // the interpretation:
            if (pr->clingo_to_plog_lit.find(abs(clitid)) != pr->clingo_to_plog_lit.end()) {
                Lit_t plogLit = pr->clingo_to_plog_lit[abs(clitid)];
                // we only care about positive literals:
                if (!plogLit.classicNeg && i.getVal(plogLit.attid) == UNASSIGNED)
                    i.assign(plogLit.attid, plogLit.valid);
            }
        }

    }


    for (ATTID a : ids) {
        if (i.getVal(a) == UNASSIGNED)
            i.assign(a, UNDEFINED);
    }
}



std::unordered_set<ATTID> GroundPlog::ExactDCOSolve::RAT(const Interpretation &i, GroundPlog::Program *pr) {
    std::unordered_set<ATTID> result;
    for(ATTID a:i.getAllAssignAtts()) {
        if(pr->isRandom(a)) result.insert(a);
    }
    return result;
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

std::unordered_set<ATTID> GroundPlog::ExactDCOSolve::DAT(const Interpretation &i, GroundPlog::Program *pr, DepGraph *dg) {
    // run bfs from all attribute R - RAT. Whatever is left is the output
    std::unordered_set<ATTID> rat = RAT(i, pr);
    std::unordered_set<ATTID> ratP = pr->getRandomAttributeTerms();
    std::unordered_set<ATTID> leftrat;
    std::copy_if(ratP.begin(), ratP.end(), std::inserter(leftrat,leftrat.begin()),
                 [&rat] (int needle) { return rat.find(needle) == rat.end(); });

    // run bfs from the difference:
    // find all attribute terms which depend on at least one of the random attribute terms
    // not decided in given interpretation i
    std::unordered_set<ATTID> covered_att = bfs(leftrat,dg);
    std::unordered_set<ATTID> all_att = pr->getNonRandomAttributeTerms();
    std::unordered_set<ATTID> result;

    std::copy_if(all_att.begin(), all_att.end(), std::inserter(result,result.begin()),
                 [&covered_att] (int needle) { return covered_att.find(needle) == covered_att.end(); });


    return result;

}

std::unordered_set<unsigned int> GroundPlog::ExactDCOSolve::P(Interpretation &interpretation, GroundPlog::Program *pProgram,
                                                              GroundPlog::DepGraph *pGraph) {
    std::unordered_set<ATTID> ats = RAT(interpretation, pProgram);
    //std::cout << "RAT: " << ats.size() << std::endl;
    std::unordered_set<ATTID> datats = DAT(interpretation, pProgram, pGraph);
    //std:: cout << "DAT: " << datats.size() << std::endl;
    ats.insert(datats.begin(), datats.end());
    std::unordered_set<unsigned> rule_ext_ids = pProgram -> getExternalsForSubprogramConstructedFrom(ats);
    std::unordered_set<unsigned> atom_ext_ids = pProgram -> getExternalsForAtomsFrom(interpretation);
    atom_ext_ids.insert(rule_ext_ids.begin(), rule_ext_ids.end());
    return atom_ext_ids;
}

GroundPlog::Clingo_Result
GroundPlog::ExactDCOSolve::call_clingo(Clingo::Control *clingoCtrl, std::unordered_set<unsigned> activeRules) {
    //std::cout <<"CLINGO CALLED" << std::endl;
    // assign externals:
    Clingo::SymbolicAtoms ats = clingoCtrl->symbolic_atoms();

    std::vector<Clingo::Symbol> assignedSymbols;
    for(auto it = ats.begin(); it!=ats.end();it++) {
        if(activeRules.find(abs(it->literal()))!=activeRules.end()) {
            assignedSymbols.push_back(it->symbol());
            clingoCtrl->assign_external(it->symbol(), Clingo::TruthValue::True);
        }
    }


    // find the first model:
    Clingo::SolveIteratively solveit = clingoCtrl->solve_iteratively();
    Clingo::Model m1 = solveit.next();
    ClingoModelRep mr = modelToASPIfs(m1, clingoCtrl);
    Clingo::Model m2 = solveit.next();
    solveit.close();
    // assign the externals back to FREE:
    for(const Clingo::Symbol &s: assignedSymbols) {
        clingoCtrl->assign_external(s, Clingo::TruthValue::False);
    }
    // std::cout << "MODEL3: " << m1 << std::endl;


    if(!m1 || m2) { // we don't have exactly one model!
        return Clingo_Result{false, mr};
    } else {
        // here we have exactly one model m1
        return Clingo_Result{true, mr};
    }
}


std::tuple<bool, double, double>
GroundPlog::ExactDCOSolve::GetCompletionProbA(GroundPlog::Program *prg, Clingo::Control *cControl, Interpretation &I,
                                              GroundPlog::DepGraph *dg, const AttributeSelectionHeuristic &heu,
                                              const ValueSelectionHeuristic &heuv, ATTID selectedATT) {
    double satsum = 0.0;
    double totalsum = 0.0;
    std::unordered_set<ValueRep> pvals= prg->getPossibleValuesFor(selectedATT, I);
    //std::cout << "size: " << pvals.size() << std::endl;
    while(!pvals.empty()) {
        ValueRep selectedVal = heuv.select(pvals);
        pvals.erase(selectedVal);
        I.increaseLevel();
        I.assign(selectedATT,selectedVal);
        std::tuple<bool, double, double> comp = GetCompletionProb(prg,cControl,I,dg,heu,heuv);
        I.backtrackLastLevel();
        if(!std::get<0>(comp)) {
            return std::tuple<bool, double, double>{false,0,0};
        }
        satsum += std::get<1> (comp);
        totalsum += std::get<2> (comp);

    }
    return std::tuple<bool, double, double>{true, satsum, totalsum};
}

bool GroundPlog::ExactDCOSolve::AtMost(GroundPlog::Program *prg, Interpretation &I, const std::unordered_set<ATTID> &cur_dat) {
    // compute the fixed point G from page 43 of Weijun's dissertation
    //I.increaseLevel();
    std::unordered_map<ATTID, std::unordered_set<ValueRep > > posibVals;
    bool iteration_needed = true;
    std::unordered_set<size_t> ruleFired;
    while(iteration_needed) {
        iteration_needed = false;
        for(size_t i=0;i< prg->rules.size();i++) {
            const RegularRule &r = prg->rules[i];
            if(cur_dat.find(r.head.attid) != cur_dat.end()) {
                if(I.weakly_satisfies(r.body, posibVals) && I.getVal(r.head.attid) == UNASSIGNED && ruleFired.find(i) == ruleFired.end() && !I.is_impossible_val(r.head.attid, r.head.valid)) {
                    ruleFired.insert(i);
                    iteration_needed = true;
                    posibVals[r.head.attid].insert(r.head.valid);
                }
            }
        }
    }

    bool something_assigned = false;

    for(ATTID id:cur_dat) {
        {
            if (I.getVal(id) == UNASSIGNED) {
                 if(posibVals.find(id)==posibVals.end()) {
                     something_assigned = true;
                    // std::cout <<"MADE_UNDEF:" << id << std::endl;
                     I.assign(id,UNDEFINED);
                 } else {
                     const std::unordered_set<ValueRep > &all_vals = prg->getAttValues(id);
                     for(const ValueRep val:all_vals) {
                         if(std::find(posibVals[id].begin(),posibVals[id].end(),val)==posibVals[id].end() && !I.is_impossible_val(id,val)) {
                             something_assigned = true;
                             //std::cout <<"MADE_OMPOS:" << id << " "<<val << std::endl;
                             I.make_impossible(id,val);
                         }
                     }
                 }
            }
        }
    }
    return something_assigned;
}
