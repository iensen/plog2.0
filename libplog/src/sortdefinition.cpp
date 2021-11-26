//
// Created by iensen on 10/9/16.
//

#include <plog/input/sortdefinition.h>

void SortDefinition::print(std::ostream &out) const {
    throw "not implemented yet";
}

const String SortDefinition::getSortName() const {
    return sortName;
}

const USortExpr &SortDefinition::getSortExpr() const {
    return sexpr;
}
