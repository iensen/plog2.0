//
// Created by iensen on 10/14/16.
//
#include<plog/input/statement.h>
#include<gringo/input/statement.hh>
#include<gringo/locatable.hh>
#include<src/input/nongroundgrammar/grammar.hh>


using Gringo::make_locatable;
using Gringo::gringo_make_unique;
using Gringo::FunctionTerm;
using Gringo::ValTerm;
using Gringo::Symbol;
using Gringo::Location;
using Gringo::make_locatable;
using Gringo::Input::PredicateLiteral;
using Gringo::Input::UBodyAggrVec ;
using GStatement = Gringo::Input::Statement;
using GStatementType = Gringo::Input::StatementType ;
using Gringo::Input::SimpleHeadLiteral;
using USimpleHeadLit = std::unique_ptr<SimpleHeadLiteral>;

Statement::Statement(ULit &&head, ULitVec &&body):head_(std::move(head)),body_(std::move(body)),type_(StatementType::RULE){
}

Statement::Statement(ULit &&head, ULitVec &&body, UProb &&prob):head_(std::move(head)),body_(std::move(body)),type_(StatementType::PR_ATOM){
}

Statement::Statement(ULit &&query):head_(std::move(query)),type_(StatementType::QUERY) {
}

void Statement::print(std::ostream &out) const {
    throw "not implemented yet";
}

void Statement::check(Logger &log) const {
    throw "not implemented yet";
}

void Statement::replace(Defines &dx) {
    throw "not implemented yet";
}

void Statement::toGround(ToGroundArg &x, UStmVec &stms) const {
    throw "not implemented yet";
}

Statement::~Statement() {
    throw "not implemented yet";
}

UGStm Statement::toGringo() {
   switch(type_) {
       case StatementType::PR_ATOM: return prAtomToGringo();
       case StatementType::QUERY:   return queryToGringo();
       default: return ruleToGringo();
   }
}

// given a pr-atom pr(a(t) = y|B) = x/y, form a rule
//                   pr(a(t),y,"x","y"):- B
UGStm Statement::prAtomToGringo() {
    return nullptr;
}

// for a(t) = y, return <a(t,y), true>
// for a(t) != y, return <a(t,y), false>

std::pair<Gringo::UTerm,bool>  Statement::term(ULit && lit) {
    FunctionTerm * fterm = dynamic_cast<FunctionTerm*>(lit->lt.get());
    String name = fterm->name;
    UTermVec args = std::move(fterm->args);
    // node, this destroys lit->rt
    args.push_back(std::move(lit->rt));
    Gringo::UTerm term = make_locatable<FunctionTerm>(DefaultLocation(), name,std::move(args));
    bool pos = lit->rel==Relation::EQ;
    return {std::move(term),pos};
}

Gringo::UTerm Statement::gringovalterm(String rep) {
    Symbol sym=  Symbol::createId(rep);
    UTerm term = make_locatable<ValTerm>(DefaultLocation(), sym);
    return term;
}

UHeadAggr Statement::head(UGLit && lit) {
    return gringo_make_unique<SimpleHeadLiteral>(std::move(lit));
}


// form  a rule (query(a(t,y),pos/neg))
UGStm Statement::queryToGringo() {

    String name = String("query"); // query should go as an argument inside
    auto   queryargs = term(std::move(head_));
    UTermVec  vec;
    vec.push_back(std::move(queryargs.first));
    vec.push_back(gringovalterm(queryargs.second?"true":"false"));
    UTerm  fterm =    make_locatable<FunctionTerm>(DefaultLocation(), name,std::move(vec));
    UGLit   predLit = make_locatable<PredicateLiteral>(DefaultLocation(), Gringo::NAF ::POS,std::move(fterm));
    UHeadAggr h = head(std::move(predLit));
    UBodyAggrVec b;
    return make_locatable<GStatement>(DefaultLocation(), std::move(h),std::move(b),GStatementType::RULE);
}

UGStm Statement::ruleToGringo() {
   // return nullptr;
    printf("NOT IMPLEMENTED YET");
}

StatementType Statement::getType() {
    return type_;
}
