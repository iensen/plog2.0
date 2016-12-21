//
// Created by evgenii on 12/17/16.
//

#include "groundplog/value_selection_heuristic.h"

ValueRep ValueSelectionHeuristic::select(const std::unordered_set<ValueRep> &vals) const {
    return *vals.begin();
}
