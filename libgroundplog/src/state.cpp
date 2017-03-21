//
// Created by iensen on 1/17/17.
//
#include <groundplog/state.h>
#include <queue>
#include <iostream>

namespace GroundPlog {

    void State::assignRandom(ATTID attid, ValueRep val) {
        I.assign(attid, val);
        RAT.push_back(attid);
        RDYRAT.erase(std::find(RDYRAT.begin(), RDYRAT.end(), attid));
        for (ATTID dep: randomDeps[attid]) {
            depCounter[dep]--;
            if (depCounter[dep] == 0) {
                DAT.push_back(dep);
            }
        }
        propagateAssignment(attid,val,false);
    }

    void GroundPlog::State::assignNonRandom(ATTID attid, ValueRep val) {
        I.assign(attid, val);
        propagateAssignment(attid,val,false);
    }

    ValueRep GroundPlog::State::getValue(ATTID attid) {
        return I.getVal(attid);
    }

    const std::vector<ATTID> &GroundPlog::State::getReadyAtts() {
        return RDYRAT;
    }


    std::vector<ATTID> GroundPlog::State::getLastLevelDAT() {
        std::vector<ATTID> result;
        int idx = (int) (DAT.size() - 1);
        while (idx >= 0 && idx>=DATLEVEL.back()) {
            result.push_back(DAT[idx]);
            --idx;
        }
        return result;
    }

    void GroundPlog::State::backTrackLevel() {
        ATTID randomATTID = RAT.back();
        backTrackPositiveAssignments();
        backTrackRandomAssignment();
        backTrackImpossibleAssignments();
        backTrackFalsifiedPrAtomBodies();
        backTrackFalsifiedRandomRuleBodies();
        backTrackFalsifiedRegularRuleBodies();
        backTrackRDYrandomAttributeTerms();
        I.backtrackLastLevel();
        RDYRAT.push_back(randomATTID); //??
        --currentLevel;
    }

    void GroundPlog::State::increaseLevel() {
        // save the number of dats:
        DATLEVEL.push_back((unsigned int &&) DAT.size());

        //save the number of ready attribute terms
        RDYRATLEVEL.push_back(RDYRAT.size());

        // save the size of falsified pr atoms trail
        prAtBodyFalsifiedTrailLevel.push_back(prAtBodyFalsifiedTrail.size());

        // save the size of falsified regular rules trail
        regRuleBodyFalsifiedTrailLevel.push_back(regRuleBodyFalsifiedTrail.size());

        // save the size of falsified random rules trail
        randomRuleBodyFalsifiedTrailLevel.push_back(randomRuleBodyFalsifiedTrail.size());
        I.increaseLevel();
        ++currentLevel;
    }

    bool GroundPlog::State::propagateAssignment(ATTID attid, ValueRep val, bool is_impossible) {
        bool smthassigned = false;
        //std::queue<std::tuple<ATTID,ValueRep ,bool> > Q;

        for (unsigned idx : prg->regularRuleBodies[attid]) {
            ATTID headatt = prg->rules[idx].head.attid;
            //if(I.getVal(headatt) != UNASSIGNED && !prg->isRandomAtt[headatt] && I.getLevel(headatt)<currentLevel);
            //    continue;

            for (const Lit_t &lit: prg->rules[idx].body) {


                ValueRep headattval = prg->rules[idx].head.valid;
                if (lit.attid == attid && (!is_impossible || (is_impossible && lit.valid == val))) {
                    if (I.guarantees(lit)) {
                        ++regRuleBodyTrueLitCounter[idx];
                        if (regRuleBodyTrueLitCounter[idx] == prg->rules[idx].body.size()) {
                            if (I.getVal(headatt) == UNASSIGNED && !prg->isRandomAtt[headatt]) {
                                smthassigned = true;
                                I.assign(headatt, headattval);
                                propagateAssignment(headatt, headattval, false);
                            } else if (prg->isRandomAtt[headatt]) {
                                if (I.getVal(headatt) == UNASSIGNED) {
                                    --UNDECIDEDRULECOUNTER[headatt];
                                    if (UNDECIDEDRULECOUNTER[headatt] == 0) {
                                        RDYRAT.push_back(headatt);
                                    }
                                }
                            }
                        }
                    } else {
                        if (!regRuleBodyFalsified[idx]) {
                            regRuleBodyFalsifiedTrail.push_back(idx);
                            regRuleBodyFalsified[idx] = true;

                            if (!prg->isRandomAtt[headatt]) {
                                pvCounter[{headatt, headattval}]--;
                                if (pvCounter[{headatt, headattval}] == 0) {
                                    if (!!I.is_impossible_val(attid, headattval)) {
                                        smthassigned = true;
                                        I.make_impossible(headatt, headattval);
                                        propagateAssignment(headatt, headattval, true);
                                    }
                                }
                            } else {
                                --UNDECIDEDRULECOUNTER[headatt];
                                if (UNDECIDEDRULECOUNTER[headatt] == 0) {
                                    RDYRAT.push_back(headatt);
                                }
                            }
                        }
                    }
                }
            }
        }
        updatePrAtoms(attid, val, is_impossible);
        updateRandomRules(attid, val, is_impossible);
        if(!is_impossible) {
            updateDynRangeCounters(attid);
        }
        return smthassigned;
    }

    bool GroundPlog::State::hasAssignmentToRandom() {
        return RAT.size() != 0;
    }

    bool GroundPlog::State::initClosure() {
        bool assigned = false;
        for (int i = 0; i < prg->rules.size(); i++) {
            const RegularRule &r = prg->rules[i];
            if (r.body.size() == regRuleBodyTrueLitCounter[i] && !prg->isRandom(r.head.attid))
                if (I.getVal(r.head.attid) == UNASSIGNED) {
                    assigned = true;
                    I.assign(r.head.attid, r.head.valid);
                    propagateAssignment(r.head.attid, r.head.valid, false);
                }
        }
        return assigned;
    }

    unsigned GroundPlog::State::LastLevelUndecidedCount() {
        std::vector<ATTID> lastLevelDat = getLastLevelDAT();
        unsigned ct = 0;
        for (const ATTID a: lastLevelDat) {
            if (getValue(a) == UNASSIGNED)
                ++ct;
        }
        return ct;
    }

    std::unordered_map<ATTID, std::unordered_set<ValueRep>> toMap(std::vector<std::vector<char>> v, std::vector<ATTID> last_dat) {
        std::unordered_map<ATTID, std::unordered_set<ValueRep>> result;
        for(int i: last_dat) {
            for(int j=0; j < v[i].size();j++) {
                if(v[i][j])
                    result[i].insert(j);
            }
        }
        return result;
    };

    /*
    bool GroundPlog::State::AtMost() {
        std::vector<ATTID> last_dat = getLastLevelDAT();
        std::unordered_map<ATTID, std::unordered_set<ValueRep> > posibVals;
        bool iteration_needed = true;
        std::unordered_set<size_t> ruleFired;
        std::vector<ATTID> last_dat_unassigned;
        for(ATTID a : last_dat) {
            if(I.getVal(a)==UNASSIGNED) {
                last_dat_unassigned.push_back(a);
            }
        }
        //int iterations = 0;
        while (iteration_needed) {
          //  ++iterations;
            iteration_needed = false;
            for (ATTID a: last_dat_unassigned) {
                    for (unsigned i : prg->attRules[a]) {
                        const RegularRule &r = prg->rules[i];
                        if (!regRuleBodyFalsified[i] &&
                            ruleFired.find(i) == ruleFired.end() &&  I.weakly_satisfies(r.body, posibVals) ) {
                            ruleFired.insert(i);
                            iteration_needed = true;
                            posibVals[r.head.attid].insert(r.head.valid);
                        }

                }
            }
        }

        //std::cout << iterations << std::endl;
        bool something_assigned = false;

        for (ATTID id:last_dat_unassigned) {
            {

                    if (posibVals.find(id) == posibVals.end() && I.getVal(id)!=UNDEFINED) {
                        something_assigned = true;
                        // std::cout <<"MADE_UNDEF:" << id << std::endl;
                        I.assign(id, UNDEFINED);
                        propagateAssignment(id,UNDEFINED,false);
                    } else {
                        const size_t valCount = prg->getAttValuesCount(id); //error
                        for (ValueRep val=0; val < valCount;val++) {
                            if (std::find(posibVals[id].begin(), posibVals[id].end(), val) == posibVals[id].end() &&
                                !I.is_impossible_val(id, val)) {
                                something_assigned = true;
                                //std::cout <<"MADE_OMPOS:" << id << " "<<val << std::endl;
                                I.make_impossible(id, val);
                                propagateAssignment(id,val,true);
                            }
                        }
                    }
                }

        }
        return something_assigned;

    }
     */

    bool GroundPlog::State::AtMost() {
        std::vector<ATTID> last_dat = getLastLevelDAT();
        //std::unordered_map<ATTID, std::unordered_set<ValueRep> > posibVals;
        for(const ATTID at : last_dat) {
            posibVals[at].assign(prg->val_candidates_vects[at].size(), false);
        }

        bool iteration_needed = true;
        std::unordered_set<size_t> ruleFired;
        std::vector<ATTID> last_dat_unassigned;
        for(ATTID a : last_dat) {
            if(I.getVal(a)==UNASSIGNED) {
                last_dat_unassigned.push_back(a);
            }
        }
        //int iterations = 0;
        while (iteration_needed) {
             // ++iterations;
            iteration_needed = false;
            for (ATTID a: last_dat_unassigned) {
                for (unsigned i : prg->attRules[a]) {
                    const RegularRule &r = prg->rules[i];

                    if (!regRuleBodyFalsified[i] && !posibVals[a][r.head.valid]
                        &&  I.weakly_satisfies(r.body, posibVals) ) {
                        //ruleFired.insert(i);
                        iteration_needed = true;
                        posibVals[r.head.attid][r.head.valid] = true;
                    }

                }
            }
        }

        //std::cout << iterations << std::endl;
        bool something_assigned = false;

        for (ATTID id:last_dat_unassigned) {

            const size_t valCount = prg->getAttValuesCount(id);
            bool hasPosibValueForId = false;

            for(ValueRep val = 0 ; val < valCount; val++) {
                if(posibVals[id][val]) {
                    hasPosibValueForId = true;
                    break;
                }
            }

            if (!hasPosibValueForId && I.getVal(id)==UNASSIGNED) {
                something_assigned = true;
                // std::cout <<"MADE_UNDEF:" << id << std::endl;
                I.assign(id, UNDEFINED);
                propagateAssignment(id, UNDEFINED, false);
            }
            else {
                for (ValueRep val = 0; val < valCount; val++) {
                    if (!posibVals[id][val] && !I.is_impossible_val(id, val)) {
                        something_assigned = true;
                        //std::cout <<"MADE_OMPOS:" << id << " "<<val << std::endl;
                        I.make_impossible(id, val);
                        propagateAssignment(id, val, true);
                    }
                }
            }


        }


        return something_assigned;

    }



    const Interpretation &GroundPlog::State::getI() const {
        return I;
    }

    const std::vector<ATTID> &GroundPlog::State::getRAT() const {
        return RAT;
    }

    const std::vector<ATTID> &GroundPlog::State::getDAT() const {
        return DAT;
    }

    GroundPlog::Program *GroundPlog::State::getProgram() const {
        return prg;
    }

    DepGraph *GroundPlog::State::getDepGraph() const {
        return depGraph;
    }

    const std::vector<ATTID> &GroundPlog::State::getRDYRAT() const {
        return RDYRAT;
    }

    void GroundPlog::State::initRandomDeps() {
        randomDeps.assign(prg->att_count, {});
        //std::cout << prg->att_count << std::endl;
        depCounter.assign(prg->att_count,0);
        for (int i = 0; i < prg->att_count; i++) {
            if (prg->isRandomAtt[i]) {
                std::unordered_set<ATTID> deps = findDeps(i);
                randomDeps[i] = std::vector<ATTID>(deps.begin(), deps.end());
                for (ATTID id: randomDeps[i]) {
                    if (!prg->isRandomAtt[id])
                        depCounter[id]++;
                }
            }
        }

        DATLEVEL.push_back(0);
        for(int i=0;i<prg->att_count;i++) {
            if(!prg->isRandomAtt[i] && depCounter[i]==0) {
                DAT.push_back(i);
            }
        }
    }

    std::unordered_set<ATTID> GroundPlog::State::findDeps(ATTID id) {
        std::unordered_set<ATTID> result;
        result.insert(id);
        std::queue<ATTID> Q;
        Q.push(id);
        while (!Q.empty()) {
            ATTID c = Q.front();
            Q.pop();
            for (ATTID n:depGraph->children(c)) {
                if (result.find(n) == result.end()) {
                    result.insert(n);
                    Q.push(n);
                }
            }
        }
        return result;
    }


    void GroundPlog::State::initUndecidedRuleCounter() {
        UNDECIDEDRULECOUNTER.assign(prg->att_count, 0);
        for (const RandomRule &r : prg->randomrules) {
            if (r.body.size() > 0 ||r.head.second!=UNASSIGNED)
                ++UNDECIDEDRULECOUNTER[r.head.first];
        }

        for (const RegularRule &r:prg->rules) {
            if (r.body.size() > 0) {
                ++UNDECIDEDRULECOUNTER[r.head.attid];
            }
        }

        for (const PrAtom &p :prg->pratoms) {
            if (p.body.size() > 0)
                ++UNDECIDEDRULECOUNTER[p.head.attid];
        }
    }

    void GroundPlog::State::initBodyTrueLitCounters() {
        prAtBodyTrueLitCounter.assign(prg->pratoms.size(), 0);
        randomRuleBodyTrueLitCounter.assign(prg->randomrules.size(), 0);
        regRuleBodyTrueLitCounter.assign(prg->rules.size(), 0);
    }

    void GroundPlog::State::initBodyFalsifiedFlags() {
        prAtBodyFalsified.assign(prg->pratoms.size(), false);
        randomRuleBodyFalsified.assign(prg->randomrules.size(), false);
        regRuleBodyFalsified.assign(prg->rules.size(), false);
    }

    void GroundPlog::State::initPvCounter() {
        for (const RegularRule &r: prg->rules) {
            pvCounter[{r.head.attid, r.head.valid}]++;
        }
    }

    void GroundPlog::State::updateRandomRules(ATTID attid, ValueRep val, bool is_impossible) {
        for (unsigned idx: prg->randomRuleBodies[attid]) {
            for (const Lit_t &lit: prg->randomrules[idx].body) {
                ATTID headatt = prg->randomrules[idx].head.first;
                if (lit.attid == attid && !is_impossible || (is_impossible && lit.valid == val)) {
                    if (I.guarantees(lit)) {
                        ++randomRuleBodyTrueLitCounter[idx]; // counter increased!
                        if (randomRuleBodyTrueLitCounter[idx] == prg->randomrules[idx].body.size() && undecidedDynRangeAttFor[idx]==0) {
                            --UNDECIDEDRULECOUNTER[headatt];
                            if (UNDECIDEDRULECOUNTER[headatt] == 0) {
                                RDYRAT.push_back(headatt);
                            }
                        }
                    } else {
                        if (!randomRuleBodyFalsified[idx]) {
                            randomRuleBodyFalsified[idx] = true;
                            randomRuleBodyFalsifiedTrail.push_back(idx);
                            --UNDECIDEDRULECOUNTER[headatt];
                            if (UNDECIDEDRULECOUNTER[headatt] == 0) {
                                RDYRAT.push_back(headatt);
                            }
                        }
                    }
                }
            }
        }
    }

    void GroundPlog::State::updatePrAtoms(ATTID attid, ValueRep val, bool is_impossible) {
        for (unsigned idx: prg->prAtBodies[attid]) {
            for (const Lit_t &lit: prg->pratoms[idx].body) {
                ATTID headatt = prg->pratoms[idx].head.attid;
                if (lit.attid == attid && !is_impossible || (is_impossible && lit.valid == val)) {
                    if (I.guarantees(lit)) {
                        ++prAtBodyTrueLitCounter[idx]; // counter increased!
                        if (prAtBodyTrueLitCounter[idx] == prg->pratoms[idx].body.size()) {
                            --UNDECIDEDRULECOUNTER[headatt];
                            if (UNDECIDEDRULECOUNTER[headatt] == 0) {
                                RDYRAT.push_back(headatt);
                            }
                        }
                    } else {
                        if (!prAtBodyFalsified[idx]) {
                            prAtBodyFalsified[idx] = true;
                            prAtBodyFalsifiedTrail.push_back(idx);
                            --UNDECIDEDRULECOUNTER[headatt];
                            if (UNDECIDEDRULECOUNTER[headatt] == 0) {
                                RDYRAT.push_back(headatt);
                            }
                        }
                    }
                }
            }
        }
    }

    void GroundPlog::State::backTrackRandomAssignment() {

        ATTID rndAtt = RAT.back();
        RAT.pop_back();

        for (ATTID dep: randomDeps[rndAtt]) {
            depCounter[dep]++;
            if (depCounter[dep] == 1) {
                DAT.pop_back();
            }
        }

    }

    void GroundPlog::State::backTrackPositiveAssignments() {
        int tidx = (int) (I.trail.size() - 1);
        while (tidx >= 0 && I.level[I.trail[tidx]] == I.current_level) {
            int attid = I.trail[tidx];
            // todo : rewrite this using metaprogramming:
            // backtrack counters in  regular rules:
            for (unsigned idx : prg->regularRuleBodies[attid]) {
                for (const Lit_t &lit: prg->rules[idx].body) {
                    ATTID headatt = prg->rules[idx].head.attid;
                    if (I.guarantees(lit) && lit.attid == attid ) {
                        --regRuleBodyTrueLitCounter[idx];
                        if (regRuleBodyTrueLitCounter[idx] == prg->rules[idx].body.size() - 1 &&
                            prg->isRandomAtt[headatt]) {
                            if (I.getVal(headatt) == UNASSIGNED) {
                                ++UNDECIDEDRULECOUNTER[headatt];
                            }
                        }
                    }
                }
            }

            // backtrack counters in random selection rules:
            for(unsigned idx:prg->randomRuleBodies[attid]) {
                for (const Lit_t &lit: prg->randomrules[idx].body) {
                    ATTID headatt = prg->randomrules[idx].head.first;
                    if (I.guarantees(lit) && lit.attid == attid ) {
                        --randomRuleBodyTrueLitCounter[idx];
                        if (randomRuleBodyTrueLitCounter[idx] == prg->randomrules[idx].body.size() - 1 &&
                            undecidedDynRangeAttFor[idx]==0) {
                            if (I.getVal(headatt) == UNASSIGNED) {
                                ++UNDECIDEDRULECOUNTER[headatt];
                            }
                        }
                    }
                }
            }
            // backtrackcounters in pr-atoms:
            for(unsigned idx:prg->prAtBodies[attid]) {
                for (const Lit_t &lit: prg->pratoms[idx].body) {
                    ATTID headatt = prg->pratoms[idx].head.attid;
                    if (I.guarantees(lit) && lit.attid == attid ) {
                        --prAtBodyTrueLitCounter[idx];
                        if (prAtBodyTrueLitCounter[idx] == prg->pratoms[idx].body.size() - 1) {
                            if (I.getVal(headatt) == UNASSIGNED) {
                                ++UNDECIDEDRULECOUNTER[headatt];
                            }
                        }
                    }
                }
            }

            // backtrack counters for dynamic ranges:

            for(unsigned ridx: prg->dynRangeAttFor[attid]) {
                undecidedDynRangeAttFor[ridx]++;
                if(undecidedDynRangeAttFor[ridx]==1 && randomRuleBodyTrueLitCounter[ridx] == prg->randomrules[ridx].body.size()) {
                    ++UNDECIDEDRULECOUNTER[prg->randomrules[ridx].head.first];
                }
            }

            --tidx;
        }
    }

    void GroundPlog::State::backTrackImpossibleAssignments() {
        //backtrack impossible assignments:

        int tidx = I.trailOnImposVals.size()-1;
        while (tidx >= 0 && I.levelOnImposVals[tidx] == I.current_level) {
            ATTID attid = I.trailOnImposVals[tidx].first;
            ValueRep val = I.trailOnImposVals[tidx].second;

            // todo : rewrite this using metaprogramming:
            // backtrack counters in  regular rules:
            for (unsigned idx : prg->regularRuleBodies[attid]) {
                for (const Lit_t &lit: prg->rules[idx].body) {
                    ATTID headatt = prg->rules[idx].head.attid;
                    if (I.guarantees(lit) && lit.valid == val && lit.attid == attid ) {
                        --regRuleBodyTrueLitCounter[idx];
                        if (regRuleBodyTrueLitCounter[idx] == prg->rules[idx].body.size() - 1 &&
                            prg->isRandomAtt[headatt]) {
                            if (I.getVal(headatt) == UNASSIGNED) {
                                ++UNDECIDEDRULECOUNTER[headatt];
                            }
                        }
                    }
                }
            }

            // backtrack counters in random selection rules:
            for(unsigned idx:prg->randomRuleBodies[attid]) {
                for (const Lit_t &lit: prg->randomrules[idx].body) {
                    ATTID headatt = prg->randomrules[idx].head.first;
                    if (I.guarantees(lit)&&  lit.valid == val && lit.attid == attid ) {
                        --randomRuleBodyTrueLitCounter[idx];
                        if (randomRuleBodyTrueLitCounter[idx] == prg->randomrules[idx].body.size() - 1 &&
                            prg->isRandomAtt[headatt]) {
                            if (I.getVal(headatt) == UNASSIGNED) {
                                ++UNDECIDEDRULECOUNTER[headatt];
                            }
                        }
                    }
                }
            }
            // backtrackcounters in pr-atoms:
            for(unsigned idx:prg->prAtBodies[attid]) {
                for (const Lit_t &lit: prg->pratoms[idx].body) {
                    ATTID headatt = prg->pratoms[idx].head.attid;
                    if (I.guarantees(lit) && lit.valid == val && lit.attid == attid ) {
                        --prAtBodyTrueLitCounter[idx];
                        if (prAtBodyTrueLitCounter[idx] == prg->pratoms[idx].body.size() - 1) {
                            if (I.getVal(headatt) == UNASSIGNED) {
                                ++UNDECIDEDRULECOUNTER[headatt];
                            }
                        }
                    }
                }
            }
            --tidx;
        }
    }

    void State::backTrackFalsifiedPrAtomBodies() {
        while(prAtBodyFalsifiedTrail.size()>prAtBodyFalsifiedTrailLevel.back()) {
            unsigned ridx = prAtBodyFalsifiedTrail.back();
            prAtBodyFalsified[ridx] = false;
            ++UNDECIDEDRULECOUNTER[ridx];
            prAtBodyFalsifiedTrail.pop_back();
        }
        prAtBodyFalsifiedTrailLevel.pop_back();
    }

    void State::backTrackFalsifiedRandomRuleBodies() {
         while(randomRuleBodyFalsifiedTrail.size()>randomRuleBodyFalsifiedTrailLevel.back()) {
             unsigned ridx = randomRuleBodyFalsifiedTrail.back();
             randomRuleBodyFalsified[ridx] = false;
             ++UNDECIDEDRULECOUNTER[ridx];
             randomRuleBodyFalsifiedTrail.pop_back();
         }
        randomRuleBodyFalsifiedTrailLevel.pop_back();
    }

    void State::backTrackFalsifiedRegularRuleBodies() {
        while(regRuleBodyFalsifiedTrail.size()>regRuleBodyFalsifiedTrailLevel.back()) {
            unsigned ridx = regRuleBodyFalsifiedTrail.back();
            regRuleBodyFalsified[ridx] = false;
            ATTID headatt = prg->rules[ridx].head.attid;
            ValueRep valid = prg->rules[ridx].head.valid;
            if(!prg->isRandomAtt[headatt]) {
                pvCounter[{headatt, valid}]++;
            } else {
                ++UNDECIDEDRULECOUNTER[ridx];
            }
            regRuleBodyFalsifiedTrail.pop_back();
        }
        regRuleBodyFalsifiedTrailLevel.pop_back();
    }

    void State::backTrackRDYrandomAttributeTerms() {
         RDYRAT.resize(RDYRATLEVEL.back()-1);
         RDYRATLEVEL.pop_back();
    }

    void State::initReadyRandomAttributeTerms() {
       for(ATTID i=0;i<prg->att_count;i++) {
           if(prg->isRandomAtt[i]) {
               if(UNDECIDEDRULECOUNTER[i]==0) {
                   RDYRAT.push_back(i);
               }
           }
       }
    }

    void State::initDynRangeDecidedAttCounter() {
        undecidedDynRangeAttFor.assign(prg->randomrules.size(),0);

        for(ATTID i=0;i<prg->att_count;i++) {
            for(unsigned ridx: prg->dynRangeAttFor[i]) {
                undecidedDynRangeAttFor[ridx]++;
            }
        }

    }

    void State::updateDynRangeCounters(ATTID attid) {
        for(unsigned ridx: prg->dynRangeAttFor[attid]) {
            undecidedDynRangeAttFor[ridx]--;
            if(undecidedDynRangeAttFor[ridx]==0 && randomRuleBodyTrueLitCounter[ridx]==prg->randomrules[ridx].body.size()) {
                unsigned headatt = prg->randomrules[ridx].head.first;
                --UNDECIDEDRULECOUNTER[headatt];
                if (UNDECIDEDRULECOUNTER[headatt] == 0) {
                    RDYRAT.push_back(headatt);
                }
            }
        }

    }

    void State::initInterpretation() {

    }

    State::State(GroundPlog::DepGraph *dg, GroundPlog::Program *pr):I(*pr) {
        this->prg = pr;
        this->depGraph = dg;
        currentLevel = 0;
        posibVals.assign(pr->att_count,{});
        initRandomDeps();
        initUndecidedRuleCounter();
        initBodyTrueLitCounters();
        initBodyFalsifiedFlags();
        initPvCounter();
        initReadyRandomAttributeTerms();
        initDynRangeDecidedAttCounter();
        initInterpretation();


    }
}
