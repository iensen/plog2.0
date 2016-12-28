//
// Created by evgenii on 12/17/16.
//

#include <random>
#include "groundplog/attribute_selection_heuristic.h"

ATTID  AttributeSelectionHeuristic ::select(const std::unordered_set<ATTID> &atts) const {
    /*std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, atts.size()-1);
    int index = uniform_dist(e1);
    auto it = atts.begin();
    std::advance(it,index);
     */
    return *atts.begin();
}
