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
using GStatement = Gringo::Input::Statement;
using GStatementType = Gringo::Input::StatementType ;
using Gringo::Input::SimpleHeadLiteral;
using Gringo::Input::SimpleBodyLiteral;
using USimpleHeadLit = std::unique_ptr<SimpleHeadLiteral>;


Statement::Statement(ULit &&head, ULitVec &&body):head_(std::move(head)),body_(std::move(body)),type_(StatementType::RULE){

}

Statement::Statement(ULit &&head, ULitVec &&body, UProb &&prob):head_(std::move(head)),body_(std::move(body)),probability_(std::move(prob)),type_(StatementType::PR_ATOM){

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
    // need to remove numbuf and denumbuf if they were created!
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
    // construct head:
    String prName = String("pr");
    UTermVec vec;
    vec.push_back(std::move(head_->lt));
    vec.push_back(std::move(head_->rt));
    numbuf = new char[12];
    denumbuf = new char [12];
    sprintf(numbuf, "%d", probability_->getNum());
    sprintf(denumbuf, "%d", probability_->getDenum());
    vec.push_back(std::move(gringostrterm(numbuf)));
    vec.push_back(std::move(gringostrterm(denumbuf)));
    UTerm  fterm =    make_locatable<FunctionTerm>(DefaultLocation(), prName,std::move(vec));
    UGLit   predLit = make_locatable<PredicateLiteral>(DefaultLocation(), Gringo::NAF ::POS,std::move(fterm));
    UHeadAggr h = head(std::move(predLit));
    UBodyAggrVec b = gringobody();
    return make_locatable<GStatement>(DefaultLocation(), std::move(h),std::move(b),GStatementType::RULE);
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


Gringo::UTerm Statement::gringostrterm(const char *s) {
    Symbol sym=  Symbol::createStr(String(s));
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
    // construct head:
    auto    fterm = term(std::move(head_));
    UGLit   predLit = make_locatable<PredicateLiteral>(DefaultLocation(), Gringo::NAF ::POS,std::move(fterm.first));
    UHeadAggr h = head(std::move(predLit));
    UBodyAggrVec b = gringobody();
    return make_locatable<GStatement>(DefaultLocation(), std::move(h),std::move(b),GStatementType::RULE);

}

StatementType Statement::getType() {
    return type_;
}

UBodyAggrVec Statement::gringobody() {
    UBodyAggrVec resvec;
    for (auto& lit: body_) {
        resvec.push_back(gringobodyel(lit));
    }
    return resvec;
}

//a(t) = y becomes a(t,y)
//a(t) !=y) becomes -a(t,y)
UBodyAggr Statement::gringobodyel(ULit &lit) {
    ELiteral* elit = dynamic_cast<ELiteral*>(lit.get());
    Gringo::NAF naf = elit->neg?Gringo::NAF::NOT:Gringo::NAF ::POS;
    printf("%d\n",naf);
    std::pair<Gringo::UTerm,bool> termb = term(std::move(elit->lit));
    // need simple body literal constructed form ulit!
    // first, construct ULIT:
    if(!termb.second){
        termb.first = make_locatable<Gringo::UnOpTerm>(DefaultLocation(),Gringo::UnOp::NEG,std::move(termb.first));
    }
    UGLit   predLit = make_locatable<PredicateLiteral>(DefaultLocation(), naf,std::move(termb.first));
    return gringo_make_unique<SimpleBodyLiteral>(std::move(predLit));
}

