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
        return isRandomAtt[aid];
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
        for (const RegularRule &r: rules) {
            result.insert(r.head.attid);
            for (const auto &c : r.body) {
                result.insert(c.attid);
            }
        }

        //add attribute terms from observations
        for (const Observation &obs:observations) {
            result.insert(obs.attid);
        }

        // add the attribute term from the query
        result.insert(query.attid);

        // add the attribute terms from the dynamic range atoms:
        for (const auto &dynatt:dynRangeAtt) {
            result.insert(dynatt.second);
        }

        std::unordered_set<ATTID> ratts = getRandomAttributeTerms();
        std::unordered_set<ATTID> final_result;
        std::copy_if(result.begin(), result.end(), std::inserter(final_result, final_result.begin()),
                     [&ratts](int needle) { return ratts.find(needle) == ratts.end(); });

        return final_result;
    }

    std::unordered_set<unsigned>
    Program::getExternalsForSubprogramConstructedFrom(const std::vector<ATTID> &atts) {
        std::unordered_set<unsigned> attsset(atts.begin(), atts.end());
        std::unordered_set<unsigned> result;

        for (int i = 0; i < rules.size(); i++) {
            if (rules[i].constructedFrom(attsset))
                result.insert(ruleExternals[i]);
        }

        for (int i = 0; i < randomrules.size(); i++) {
            if (randomrules[i].constructedFrom(attsset))
                result.insert(randomRuleExternals[i]);
        }

        for (int i = 0; i < pratoms.size(); i++) {
            if (pratoms[i].constructedFrom(attsset))
                result.insert(prAtomExternals[i]);
        }

        return result;
    }

    std::unordered_set<unsigned> Program::getExternalsForAtomsFrom(const Interpretation &i) const {
        std::unordered_set<unsigned> result;
        // rewrite to iterators:
        std::vector<ATTID> atts = i.getAllAssignAtts();
        for (const ATTID attid:atts) {
            if (atom_to_external.find(Atom_t{attid, i.getVal(attid)}) !=
                atom_to_external.end()) // remove this in future:
                // when redundant attribute terms will be removed
                result.insert(atom_to_external.at(Atom_t{attid, i.getVal(attid)}));
        }
        return result;
    }

    void Program::addAtomExternal(unsigned int att_id, unsigned int val_id, unsigned int ex_atom_id) {
        atom_to_external[Atom_t{att_id, val_id}] = ex_atom_id;
    }

    void Program::registerLiteral(unsigned int att_id, unsigned int val_id, bool pos, unsigned clingo_lit_id) {
        clingo_to_plog_lit[clingo_lit_id] = Lit_t{att_id, val_id, false, !pos};
    }

    double Program::Probability(const Interpretation &I) {
        double answer = 1.0;
        std::vector<ATTID> atts = I.getAllAssignAtts();
        for (ATTID at : atts) {
            if (!isRandom(at))
                continue;
            if (I.getVal(at) == UNDEFINED)
                continue;
            double others_prob = 0.0;
            double prob = -1.0;
            int others_prob_ct = 0;
            for (const PrAtom pr: pratoms) {
                if (pr.head.attid == at && I.guarantees(pr.body)) {
                    if (pr.head.valid == I.getVal(at)) {
                        prob = pr.prob;
                    } else {
                        others_prob += pr.prob;
                        ++others_prob_ct;
                    }
                }
            }
            if (prob > -0.5)
                answer *= prob;
            else { // default probability!
                double defaultProb = (1 - others_prob) / (getPossibleValuesFor(at, I).size() - others_prob_ct);
                answer *= defaultProb;
            }
        }
        return answer;
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
                    bool all_decided, at_least_one_guaranteed;
                    if (r.head.second != UNASSIGNED) {
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

                    if (r.head.second == UNASSIGNED || all_decided && at_least_one_guaranteed) {
                        if (foundRuleType != RuleType::None)
                            return false;
                        foundRuleType = RuleType::Random;
                        rr = &r;
                    }
                }
            }
        }

        // check regular rules:
        for (const unsigned &i : attRules[attid]) {
            RegularRule &r = rules[i];
            if (I.guarantees(r.body)) {
                if (foundRuleType != RuleType::None)
                    return false;
                foundRuleType = RuleType::Regular;
                rg = &r;
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


    std::unordered_set<ValueRep> Program::getPossibleValuesFor(ATTID attid, const Interpretation &interpretation) {
        // this assumes the attribute is ready!
        if (isDisabled(attid, interpretation)) {
            return {UNDEFINED};
        } else {// it's active
            std::unordered_set<ValueRep> result;
            Rule *rr = findUniqueActiveRuleFor(attid, interpretation);
            if (RandomRule *r = dynamic_cast<RandomRule *>(rr)) {
                unsigned int range_sort_id = a_ranges[atfromatt[r->head.first]];
                for (unsigned y: sort_elems[range_sort_id]) {
                    if (r->head.second != UNASSIGNED) {
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

    std::unordered_set<ValueRep> Program::getAttValues(unsigned int attid) {
        return val_candidates[attid];
    }


    void Program::finalize() {
        fill_vall_candidates();
        build_att_occur_map();
        fill_is_random_map();
        build_random_rule_ranges_map();
    }

    void Program::registerTotalAttNum(size_t att_count) {
        this->att_count = att_count;
    }

    void Program::fill_vall_candidates() {
        // fill candidate values
        val_candidates.resize(att_count);

        // from regular rules:
        for (const RegularRule &r:rules) {
            val_candidates[r.head.attid].insert(r.head.valid);
            for (auto body_el:r.body) {
                val_candidates[body_el.attid].insert(body_el.valid);
            }
        }

        // from random selection rules:
        for (const RandomRule &r:randomrules) {
            // get attribute term from the head:
            // for every random selection rule random(a,p) :- B
            // add p(X) -> true as a val candidate for every X in the range of a
            AId atid = atfromatt[r.head.first];
            unsigned int range_sort_id = a_ranges[atid];
            const std::vector<unsigned int> vals = sort_elems[range_sort_id];
            for (ValueRep val: vals) {
                ATTID dyn_range_att = dynRangeAtt[Dyn_Range_Atom{r.head.second, val}];
                val_candidates[dyn_range_att].insert(TRUE_ID);
            }
            for (auto body_el:r.body) {
                val_candidates[body_el.attid].insert(body_el.valid);
            }
        }

        // from pr-atoms
        for (const PrAtom &prat:pratoms) {
            val_candidates[prat.head.attid].insert(prat.head.valid);
            for (auto body_el:prat.body) {
                val_candidates[body_el.attid].insert(body_el.valid);
            }
        }

        // from query
        val_candidates[query.attid].insert(query.valid);

        // from observations
        for (const Observation &obs:observations) {
            val_candidates[obs.attid].insert(obs.valid);
        }

        // from actions:
        for (const Action &act : actions) {
            val_candidates[act.attid].insert(act.valid);
        }

    }

    void Program::build_att_occur_map() {
        prAtBodies.assign(att_count, {});
        randomRuleBodies.assign(att_count, {});
        regularRuleBodies.assign(att_count, {});
        attRules.assign(att_count, {});
        attRandomRules.assign(att_count, {});
        std::unordered_set<ATTID> was;
        for (int i = 0; i < pratoms.size(); i++) {
            const PrAtom &pr = pratoms[i];
            for (const auto &body_el:  pr.body) {
                if(was.find(body_el.attid)==was.end())
                prAtBodies[body_el.attid].push_back(i);
                was.insert(body_el.attid);
            }
            was.clear();
        }


        for (int i = 0; i < rules.size(); i++) {
            const RegularRule &r = rules[i];
            for (const auto &body_el:  r.body) {
                if(was.find(body_el.attid)==was.end())
                regularRuleBodies[body_el.attid].push_back(i);
                was.insert(body_el.attid);
            }
            was.clear();
            attRules[rules[i].head.attid].push_back(i);
        }


        for (int i = 0; i < randomrules.size(); i++) {
            const RandomRule &r = randomrules[i];
            for (const auto &body_el:  r.body) {
                if(was.find(body_el.attid)==was.end())
                randomRuleBodies[body_el.attid].push_back(i);
                was.insert(body_el.attid);
            }
            was.clear();
            attRandomRules[r.head.first].push_back(i);
        }
    }

    void Program::fill_is_random_map() {
        isRandomAtt.assign(att_count, false);
        for (const RandomRule &r :randomrules) {
            isRandomAtt[r.head.first] = true;
        }
    }

    void Program::build_random_rule_ranges_map() {
        dynRangeAttFor.assign(att_count,{});
        for (int i = 0; i < randomrules.size(); i++) {
            const RandomRule &r = randomrules[i];
            unsigned int range_sort_id = a_ranges[atfromatt[r.head.first]];
            for (unsigned y: sort_elems[range_sort_id]) {
                if (r.head.second != UNASSIGNED) {
                    ATTID attid = dynRangeAtt[{r.head.second, y}];
                    dynRangeAttFor[attid].push_back(i);
                }
            }
        }
    }
}

