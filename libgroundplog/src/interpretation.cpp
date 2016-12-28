//
// Created by evgenii on 12/16/16.
//

#include "groundplog/interpretation.h"

std::vector<ATTID> Interpretation::getAllAssignAtts() const {
    std::vector<ATTID> result;
    for(ATTID i=0; i< values.size();i++) {
        if(values[i]!=UNASSIGNED)
            result.push_back(i);
    }
    return result;
}

ValueRep Interpretation::getVal(const ATTID attid) const {
    if(attid >= values.size())
        return UNASSIGNED;
    else
    return values[attid];
}

void Interpretation::assign(ATTID attid, ValueRep val) {
     grow(attid);
     values[attid] = val;
     level[attid] = current_level;
     trail.push_back(attid);
}

// implement the rules from section 5.4.1 of the dissertation:
bool Interpretation::guarantees(const Lit_t &lit) const {
    if(!lit.classicNeg && !lit.defaultNeg)
        return getVal(lit.attid)==lit.valid;
    if(lit.classicNeg && !lit.defaultNeg)
        return getVal(lit.attid)!=UNASSIGNED && getVal(lit.attid)!=lit.valid && getVal(lit.attid)!=UNDEFINED;
    if(lit.defaultNeg && !lit.classicNeg)
        return getVal(lit.attid) !=UNASSIGNED && getVal(lit.attid)!=lit.valid;
    if(lit.classicNeg && lit.defaultNeg)
        return getVal(lit.attid) == UNDEFINED || getVal(lit.attid) == lit.valid;
}

bool Interpretation::guarantees(const std::vector<Lit_t> &body) const {
    for(const Lit_t &lit: body)
        if(!guarantees(lit))
            return false;
    return true;
}

bool Interpretation::falsifies(const Lit_t &lit) const {
    if(!lit.classicNeg && !lit.defaultNeg) {
        return getVal(lit.attid)!=UNASSIGNED && getVal(lit.attid)!=lit.valid;
    }
    if(lit.classicNeg && !lit.defaultNeg) {
        return getVal(lit.attid)==lit.valid || getVal(lit.attid) == UNDEFINED;
    }
    if(!lit.classicNeg && lit.defaultNeg) {
        return getVal(lit.attid) == lit.valid;
    }
    if(lit.classicNeg && lit.defaultNeg) {
        return getVal(lit.attid)!=UNASSIGNED && getVal(lit.attid)!=lit.valid && getVal(lit.attid)!=UNDEFINED;
    }
}

bool Interpretation::falsifies(const std::vector<Lit_t> &body) const {
    for(const Lit_t &lit : body) {
        if(falsifies(lit))
            return true;
    }
    return false;
}

bool Interpretation::decides(const Lit_t &lit) const {
    return guarantees(lit) || falsifies(lit);
}

bool Interpretation::decides(const std::vector<Lit_t> &body) const {
    return guarantees(body) || falsifies(body);
}

void Interpretation::increaseLevel() {
   ++current_level;
}

void Interpretation::backtrackLastLevel() {
    while(level[trail.back()]==current_level) {
        trail.pop_back();
        values[trail.back()] = UNASSIGNED;
    }
    --current_level;
}

void Interpretation::grow(unsigned index) {
      if(index>=values.size()) {
          values.resize(2 * index + 1,UNASSIGNED);
          level.resize(2*index+1);
      }
}

