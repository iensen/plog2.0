//
// Created by iensen on 10/2/16.
//

#include "plog/sortexpression.h"

Range::Range(UTerm &&from, UTerm &&to):from(std::move(from)), to(std::move(to)) {

}

void Range::print(std::ostream &out) const {
    throw "not implemented yet";
}

Concatenation::Concatenation(USortExprVec vec):sexprvec(std::move(vec)) {

}

void Concatenation::print(std::ostream &out) const {
    throw "not implemented yet";
}

void BinOpSortExpr::print(std::ostream &out) const {
    throw "not implemented yet";
}

void FuncSortExpr::print(std::ostream &out) const {
    throw "not implemented yet";
}

void BinOpCondition::print(std::ostream &out) const {
    throw "not implemented yet";
}

void UnaryCondition::print(std::ostream &out) const {
    throw "not implemented yet";
}

void SortNameExpr::print(std::ostream &out) const {
    throw "not implemented yet";
}

void CurlyBrackets::print(std::ostream &out) const {
    throw "not implemented yet";
}

void VarSortExpression::print(std::ostream &out) const {
    throw "not implemented yet";
}
