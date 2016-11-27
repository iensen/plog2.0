//
// Created by iensen on 10/2/16.
//

#include "plog/sortexpression.h"
#include<plog/input/utils.h>

Range::Range(UTerm &&from, UTerm &&to):from(std::move(from)), to(std::move(to)) {

}

void Range::print(std::ostream &out) const {
    throw "not implemented yet";
}

std::vector<Clingo::AST::Term> Range::generate() {
    throw "not implemented";
}

Concatenation::Concatenation(USortExprVec vec):sexprvec(std::move(vec)) {

}

void Concatenation::print(std::ostream &out) const {
    throw "not implemented yet";
}

std::vector<Clingo::AST::Term> Concatenation::generate() {
    throw "not implemented yet";
}

void BinOpSortExpr::print(std::ostream &out) const {
    throw "not implemented yet";
}

std::vector<Clingo::AST::Term> BinOpSortExpr::generate() {
    throw "not implemented yet";
}

void FuncSortExpr::print(std::ostream &out) const {
    throw "not implemented yet";
}

std::vector<Clingo::AST::Term> FuncSortExpr::generate() {
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

std::vector<Clingo::AST::Term> SortNameExpr::generate() {
    throw "not implemented";
}

void CurlyBrackets::print(std::ostream &out) const {
    throw "not implemented yet";
}

std::vector<Clingo::AST::Term> CurlyBrackets::generate() {
    std::vector<Clingo::AST::Term> result;
    for(const UTerm& term: termvec) {
        result.emplace_back(termToClingoTerm(term));
    }
    return result;
}

void VarSortExpression::print(std::ostream &out) const {
    throw "not implemented yet";
}
