//
// Created by evgenii on 12/16/16.
//

#ifndef PLOG_INTERPRETATION_H
#define PLOG_INTERPRETATION_H

#include<vector>
#include<groundplog/program_types.h>
#include<limits>

using GroundPlog::ATTID ;
using GroundPlog::ValueRep ;
using GroundPlog::Lit_t;

const ValueRep UNDEFINED = std::numeric_limits<ValueRep>::max();
const ValueRep UNASSIGNED = std::numeric_limits<ValueRep>::max()-1;

class Interpretation {
    std::vector<ValueRep> values;
    std::vector<unsigned> level;
    std::vector<ATTID > trail;
    unsigned current_level = 0;
public:
    void assign(ATTID attid,ValueRep val);
    ValueRep getVal(const ATTID attid) const;
    std::vector<ATTID> getAllAssignAtts() const;
    bool guarantees(const Lit_t &lit) const;
    bool falsifies (const Lit_t &lit) const;
    bool decides (const Lit_t &lit) const;
    bool guarantees(const std::vector<Lit_t> &body) const ;
    bool falsifies(const std::vector<Lit_t> &body) const ;
    bool decides(const std::vector<Lit_t> &body) const ;
    void increaseLevel();
    void backtrackLastLevel();
private:
    void grow(unsigned index);
};


#endif //PLOG_INTERPRETATION_H
