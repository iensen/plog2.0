//
// Created by evgenii on 12/17/16.
//

#ifndef PLOG_VALUE_SELECTION_HEURISTIC_H
#define PLOG_VALUE_SELECTION_HEURISTIC_H

#include<groundplog/value_selection_heuristic.h>
#include<groundplog/program_types.h>

using GroundPlog::ValueRep ;

class ValueSelectionHeuristic {
public:
    ValueRep select(const std::unordered_set<ValueRep> &vals) const;
};


#endif //PLOG_VALUE_SELECTION_HEURISTIC_H
