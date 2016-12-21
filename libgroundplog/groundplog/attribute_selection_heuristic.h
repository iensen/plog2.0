//
// Created by evgenii on 12/17/16.
//

#ifndef PLOG_ATTRIBUTESELECTIONHEURISTIC_H
#define PLOG_ATTRIBUTESELECTIONHEURISTIC_H


#include <unordered_set>
#include<groundplog/program_types.h>

using GroundPlog::ATTID ;

class AttributeSelectionHeuristic {
     public:
     ATTID select(const std::unordered_set<ATTID> &atts) const;
};




#endif //PLOG_ATTRIBUTESELECTIONHEURISTIC_H
