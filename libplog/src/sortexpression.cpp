//
// Created by iensen on 10/2/16.
//

#include <plog/sortexpression.h>
#include<plog/input/utils.h>
#include<plog/input/sortdefinition.h>

Range::Range(UTerm &&from, UTerm &&to):from(std::move(from)), to(std::move(to)) {

}


std::vector<Clingo::AST::Term> Range::generate( const USortDefVec &sortDefVec) {
    bool undefined;
    Gringo::Logger log;

    int n_from = from->toNum(undefined,log);
    int n_to =  to->toNum(undefined,log);

    std::vector<Clingo::AST::Term> result;
    for(int i=n_from;i<=n_to;i++) {
        Clingo::Symbol sym = Clingo::Number(i);
        result.push_back({defaultLoc,sym});
    }
    return result;

}

std::string Range::toString() const{
    throw "not implemented yet";
}

Concatenation::Concatenation(USortExprVec vec):sexprvec(std::move(vec)) {

}


std::vector<Clingo::AST::Term> Concatenation::generate( const USortDefVec &sortDefVec) {
    throw "not implemented yet";
}

std::string Concatenation::toString() const {
    return std::__cxx11::string();
}


std::vector<Clingo::AST::Term> BinOpSortExpr::generate( const USortDefVec &sortDefVec) {
    throw "not implemented yet";
}

std::string BinOpSortExpr::toString() const{
    return std::__cxx11::string();
}


std::vector<Clingo::AST::Term> FuncSortExpr::generate( const USortDefVec &sortDefVec) {
    throw "not implemented yet";
}

std::string FuncSortExpr::toString() const {
    throw "not implemented yet";
}

void BinOpCondition::print(std::ostream &out) const {
    throw "not implemented yet";
}

void UnaryCondition::print(std::ostream &out) const {
    throw "not implemented yet";
}


std::vector<Clingo::AST::Term> SortNameExpr::generate( const USortDefVec &sortDefVec) {
    for(const USortDef& def : sortDefVec) {
        if(def->getSortName()==this->name) {
            return def->getSortExpr()->generate(sortDefVec);
        }
    }
}

std::string SortNameExpr::toString() const {
    return std::string(name.c_str());
}

std::vector<Clingo::AST::Term> CurlyBrackets::generate( const USortDefVec &sortDefVec) {
    std::vector<Clingo::AST::Term> result;
    for(const UTerm& term: termvec) {
        result.emplace_back(termToClingoTerm(term));
    }
    return result;
}

std::string CurlyBrackets::toString() const {
    throw "not implemented yet";

}

void SortExpression::print(std::ostream &out) const {
   out << toString();
}
