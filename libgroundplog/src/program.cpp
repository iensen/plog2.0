//
// Created by iensen on 9/2/16.
//

#include<groundplog/program.h>
#include<clasp/util/misc_types.h>
#include <iostream>
#include<unordered_set>


namespace GroundPlog {
    using DestroyObject= Clasp::DestroyObject;


    Program::Program() {

    }

    void Program::setOptions(const Program::PrepOptions &opts) {
        opts_ = opts;
    }

    Program::~Program() {

    }


    Atom_t Program::newAtom() {
        throw "not implemented yet";
    }


    Program &Program::addRule(Atom_t head, std::vector<Lit_t> body, int ex_id) {
        // need to change this to add the dependency (and do not add the whole body)
        rules.emplace_back(RegularRule(head, body));
        ruleExternals.push_back(ex_id);
        return *this;
    }

    Program &Program::addRandomRule(std::pair<ATTID, AId> head, const std::vector<Lit_t> body, int ex_id) {
        randomrules.emplace_back(RandomRule(head, body));
        randomRuleExternals.push_back(ex_id);
        return *this;
    }

    Program &Program::addPratom(Atom_t head, const std::vector<Lit_t> body, double prob, int ex_id) {
        pratoms.emplace_back(PrAtom{head, body, prob});
        prAtomExternals.push_back(ex_id);
        return *this;
    }

    Program &Program::addQuery(Lit_t query) {
        this->query = query;
        return *this;
    }

    void Program::addAttributeMap(std::vector<unsigned int> vector) {
        this->attmap = vector;
    }

    void Program::addSortElem(unsigned int sort_id, unsigned int sort_elem_id) {
        if (sort_elems.size() <= sort_id)
            sort_elems.resize(sort_id + 1, {});
        sort_elems[sort_id].push_back(sort_elem_id);
    }

    void Program::addAtRangeSort(unsigned int a_id, unsigned int sort_id) {
        if (a_ranges.size() <= a_id)
            a_ranges.resize(a_id + 1);
        a_ranges[a_id] = sort_id;
    }

    void Program::addObservation(unsigned int att_id, unsigned int val_id, bool positive) {
        observations.emplace_back(Observation{att_id, val_id, positive});
    }

    void Program::addAction(unsigned int att_id, unsigned int val_id) {
        actions.emplace_back(Action{att_id, val_id});
    }

    bool Program::isRandom(ATTID aid) {
        for (RandomRule r: randomrules) {
            if (r.head.first == aid)
                return true;
        }
        return false;
    }

    std::unordered_set<ATTID> Program::getRandomAttributeTerms() {
        std::unordered_set<ATTID> result;
        for (RandomRule r: randomrules) {
            result.insert(r.head.first);
        }
        return result;
    }

    std::unordered_set<ATTID> Program::getNonRandomAttributeTerms() {
        // gett all attribute terms:
        // add attribute terms from regular rules
        // note that looking at heads is sufficient
        std::unordered_set<ATTID> result;
        for (RegularRule r: rules) {
            result.insert(r.head.attid);
        }

        //add attribute terms from observations
        for (const Observation &obs:observations) {
            result.insert(obs.attid);
        }

        // add the attribute term from the query
        result.insert(query.attid);

        // add the attribute terms from the dynamic range atoms:
        for(const auto &dynatt:dynRangeAtt) {
            result.insert(dynatt.second);
        }

        std::unordered_set<ATTID> ratts = getRandomAttributeTerms();
        std::unordered_set<ATTID> final_result;
        std::copy_if(result.begin(), result.end(), std::inserter(final_result,final_result.begin()),
                     [&ratts] (int needle) { return ratts.find(needle) == ratts.end(); });

        return final_result;
    }

    std::unordered_set<unsigned>
    Program::getExternalsForSubprogramConstructedFrom(const std::unordered_set<ATTID> &atts) {
        std::unordered_set<unsigned> result;

        for (int i = 0; i < rules.size(); i++) {
            if (rules[i].constructedFrom(atts))
                result.insert(ruleExternals[i]);
        }

        for (int i = 0; i < randomrules.size(); i++) {
            if (randomrules[i].constructedFrom(atts))
                result.insert(randomRuleExternals[i]);
        }

        for(int i=0;i<pratoms.size();i++) {
            if(pratoms[i].constructedFrom(atts))
                result.insert(prAtomExternals[i]);
        }

        return result;
    }

    std::unordered_set<unsigned> Program::getExternalsForAtomsFrom(const Interpretation &i) {
        std::unordered_set<unsigned> result;
        // rewrite to iterators:
        std::vector<ATTID> atts = i.getAllAssignAtts();
        for (const ATTID &attid:atts) {
            result.insert(atom_to_external[Atom_t{attid, i.getVal(attid)}]);
        }
        return result;
    }

    void Program::addAtomExternal(unsigned int att_id, unsigned int val_id, unsigned int ex_atom_id) {
        atom_to_external[Atom_t{att_id, val_id}] = ex_atom_id;
    }

    void Program::registerLiteral(unsigned int att_id, unsigned int val_id, bool pos, unsigned clingo_lit_id) {
        clingo_to_plog_lit[clingo_lit_id] = Lit_t{att_id, val_id, false, !pos};
    }

    double Program::Probability(Interpretation &I) {
        double answer = 1.0;
        std::vector<ATTID > atts =I.getAllAssignAtts();
        for(ATTID at : atts) {
            if(!isRandom(at))
                continue;
            if(I.getVal(at)==UNDEFINED)
                continue;
            double others_prob = 0.0;
            double prob = -1.0;
            int others_prob_ct = 0;
            for (const PrAtom pr: pratoms) {
                if (pr.head.attid == at && I.guarantees(pr.body)) {
                    if(pr.head.valid == I.getVal(at)) {
                        prob = pr.prob;
                    } else {
                        others_prob += pr.prob;
                        ++others_prob_ct;
                       }
                }
            }
            if(prob>-0.5)
                answer *= prob;
            else { // default probability!
                double defaultProb = (1 - others_prob) / (getPossibleValuesFor(at, I).size() - others_prob_ct);
                answer *= defaultProb;
            }
        }
        return answer;
    }

    std::unordered_set<ATTID> Program::getReadyAtts(const Interpretation &I) {
        std::unordered_set<ATTID> result;
        // optimize this not to look for every one?
        for (RandomRule r: randomrules) {
            if (isReady(r.head.first, I))
                result.insert(r.head.first);
        }
        return result;
    }

    bool Program::isReady(ATTID attid, const Interpretation &I) {
        return isDisabled(attid, I) || isActive(attid, I);
    }

    enum class RuleType {
        None, Random, Regular
    };


    bool Program::isActive(ATTID attid, const Interpretation &I) {
        if (I.getVal(attid) != UNASSIGNED)
            return false;

        Rule *r = findUniqueActiveRuleFor(attid, I);


        if (r != nullptr) {
            // check pr-atoms
            for (const PrAtom &prAtom: pratoms) {
                if (prAtom.head.attid == attid) {
                    if (!I.decides(prAtom.body))
                        return false;
                }
            }
            return true;
        } else {
           return false;
        }
    }


    // maybe this should be a method of I? who knows%) probably I is better
    bool Program::isDisabled(ATTID attid, const Interpretation &I) {
        if (I.getVal(attid) != UNASSIGNED)
            return false;

        // check random selection rules:
        for (const RandomRule &r:randomrules) {
            if (r.head.first == attid) {
                if (!I.falsifies(r.body))
                    return false;
            }
        }

        // check regular rules:
        for (const RegularRule &r: rules) {
            if (r.head.attid == attid) {
                if (!I.falsifies(r.body))
                    return false;
            }
        }

        return true;
    }

    void Program::registerDynRangeAtom(unsigned int a_id, unsigned int arg_id, unsigned int att_id) {
        dynRangeAtt[{a_id, arg_id}] = att_id;
    }

    void Program::registerTrueAtId(unsigned int true_id) {
        TRUE_ID = true_id;
    }

    // this looks ugly
    Rule *Program::findUniqueActiveRuleFor(ATTID attid, const Interpretation &I) {
        RandomRule *rr;
        RegularRule *rg;
        RuleType foundRuleType = RuleType::None;
        // this could be optimized if we only look at rules with the att in the head!
        // check random rules:
        for (RandomRule &r: randomrules) {
            if (r.head.first == attid) {
                if (I.guarantees(r.body)) {
                    // check that for every y in the range of a, p(y) is decided:
                    // and that for at least one y p(y) is guaranteed!
                    bool all_decided,at_least_one_guaranteed;
                    if(r.head.second!=UNASSIGNED) {
                        AId atid = atfromatt[r.head.first];
                        unsigned int range_sort_id = a_ranges[atid];
                        all_decided = true;
                        at_least_one_guaranteed = false;
                        for (unsigned y: sort_elems[range_sort_id]) {
                            ATTID attid = dynRangeAtt[{r.head.second, y}];
                            if (I.getVal(attid) == UNASSIGNED) {
                                all_decided = false;
                                break;
                            }
                            if (I.guarantees(Lit_t(attid, TRUE_ID, false, false))) {
                                at_least_one_guaranteed = true;
                            }
                        }
                    }

                    if (r.head.second==UNASSIGNED || all_decided && at_least_one_guaranteed) {
                        if (foundRuleType != RuleType::None)
                            return false;
                        foundRuleType = RuleType::Random;
                        rr = &r;
                    }
                }
            }
        }

        // check regular rules:
        for (RegularRule &r : rules) {
            if (r.head.attid == attid) {
                if (I.guarantees(r.body)) {
                    if (foundRuleType != RuleType::None)
                        return false;
                    foundRuleType = RuleType::Regular;
                    rg = &r;
                }
            }
        }

        switch (foundRuleType) {
            case RuleType::Regular:
                return rg;
            case RuleType::Random:
                return rr;
            case RuleType::None :
                return nullptr;
        }

    }

    std::unordered_set<ValueRep> Program::getPossibleValuesFor(ATTID attid, Interpretation &interpretation) {
        // this assumes the attribute is ready!
        if (isDisabled(attid, interpretation)) {
            return {UNDEFINED};
        } else {// it's active
            std::unordered_set<ValueRep> result;
            Rule *rr = findUniqueActiveRuleFor(attid, interpretation);
            if (RandomRule *r = dynamic_cast<RandomRule *>(rr)) {
                unsigned int range_sort_id = a_ranges[atfromatt[r->head.first]];
                for (unsigned y: sort_elems[range_sort_id]) {
                    if(r->head.second!=UNASSIGNED) {
                        ATTID attid = dynRangeAtt[{r->head.second, y}];
                        if (interpretation.guarantees(Lit_t(attid, TRUE_ID, false, false))) {
                            result.insert(y);
                        }
                    } else {
                        result.insert(y);
                    }

                }
            }

            if (RegularRule *r = dynamic_cast<RegularRule *>(rr)) {
                result.insert(r->head.valid);
            }
            return result;
        }

    }

    void Program::storeatttoatmap(unsigned int attid, unsigned int aid) {
        atfromatt[attid] = aid;
    }
}
