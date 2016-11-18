//
// Created by iensen on 10/14/16.
//
#include<plog/input/statement.h>
#include<gringo/input/statement.hh>
#include<gringo/locatable.hh>
#include<src/input/nongroundgrammar/grammar.hh>
#include <sstream>

using Gringo::make_locatable;
using Gringo::gringo_make_unique;
using Gringo::FunctionTerm;
using Gringo::ValTerm;
using Gringo::VarTerm;
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


// for a(t) = y, return <a(t,y), true>
// for a(t) != y, return <a(t,y), false>
// to do: get rid of this and construct clingo terms directly
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





StatementType Statement::getType() {
    return type_;
}



Clingo::AST::Statement Statement::toGringoAST() {
    switch(type_) {
        case StatementType::PR_ATOM: return prAtomToGringoAST();
        case StatementType::QUERY:   return queryToGringoAST();
        default: return ruleToGringoAST();
    }
}

Clingo::AST::Term termToClingoTerm(const UTerm & term) {
    std::stringstream stream;
    term.get()->print(stream);

    Clingo::Location loc("<test>", "<test>", 1, 1, 1, 1);

    // if it is a function term:
    FunctionTerm * fterm = dynamic_cast<FunctionTerm*>(term.get());

    if (fterm) {
        String name = fterm->name;
        UTermVec fargs = std::move(fterm->args);
        std::vector<Clingo::AST::Term> args;
        for(const UTerm &t: fargs) {
            args.push_back(termToClingoTerm(t));
        }
        auto f_ = Clingo::AST::Function{name.c_str(), args};
        return {loc,f_};
    }

    // if term is a variable

    VarTerm * varT = dynamic_cast<VarTerm*>(term.get());

    if (varT) {
        String name = varT->name;
        //printf("%s\n",varT->name.c_str());
        auto f_ = Clingo::AST::Variable{name.c_str()};
        return {loc,f_};
    }

    // if term is a valterm:

    ValTerm * valT = dynamic_cast<ValTerm*>(term.get());

    if (valT) {
        std::stringstream ss;
        valT->print(ss);
        Clingo::Symbol sym = Clingo::parse_term(stream.str().c_str());
        return {loc,sym};
    }

    // bin op and un op terms go here

    throw std::logic_error("cannot convert a term");

}

Clingo::AST::Statement Statement::prAtomToGringoAST() {
    // construct head:
    Clingo::Location loc("<test>", "<test>", 1, 1, 1, 1);
    std::vector<Clingo::AST::Term> args;
    args.push_back(termToClingoTerm(head_->lt));
    args.push_back(termToClingoTerm(head_->rt));
    std::stringstream stream;
    stream << probability_->getNum();
    args.push_back(Clingo::AST::Term{loc,Clingo::String(stream.str().c_str())});
    stream.str("");
    stream << probability_->getDenum();
    args.push_back(Clingo::AST::Term{loc,Clingo::String(stream.str().c_str())});
    Clingo::AST::Function f_ = {"pr", args};
    Clingo::AST::Term f_t{loc, f_};
    Clingo::AST::Literal f_l{loc, Clingo::AST::Sign::None, f_t};
    Clingo::AST::Rule f_r{{loc, f_l}, gringobodyast()};
    return {loc, f_r};

}

Clingo::AST::Statement Statement::queryToGringoAST() {
    Clingo::Location loc("<test>", "<test>", 1, 1, 1, 1);
    std::vector<Clingo::AST::Term> args;
    auto   queryargs = term(std::move(head_));
    args.push_back(termToClingoTerm(queryargs.first));
    args.push_back(queryargs.second?Clingo::AST::Term{loc,Clingo::Id("true")}:Clingo::AST::Term{loc,Clingo::Id("false")});
    Clingo::AST::Function f_ = {"query", args};
    Clingo::AST::Term f_t{loc, f_};
    Clingo::AST::Literal f_l{loc, Clingo::AST::Sign::None, f_t};
    Clingo::AST::Rule f_r{{loc, f_l}, std::vector<Clingo::AST::BodyLiteral>()};
    return {loc, f_r};
}

Clingo::AST::Statement Statement::ruleToGringoAST() {
    Clingo::Location loc("<test>", "<test>", 1, 1, 1, 1);
    auto    fterm = term(std::move(head_));
    Clingo::AST::Term f_ = termToClingoTerm(fterm.first);
    Clingo::AST::Literal f_l{loc, Clingo::AST::Sign::None, f_};
    Clingo::AST::Rule f_r{{loc, f_l}, gringobodyast()};
    //std::cout << f_r << std::endl;
    return {loc, f_r};
}

std::vector<Clingo::AST::BodyLiteral> Statement::gringobodyast() {
    std::vector<Clingo::AST::BodyLiteral> resvec;
    for (auto& lit: body_) {
        resvec.push_back(gringobodyelast(lit));
    }
    return resvec;
}

Clingo::AST::BodyLiteral Statement::gringobodyelast(ULit &lit) {
    Clingo::Location loc("<test>", "<test>", 1, 1, 1, 1);
    ELiteral* elit = dynamic_cast<ELiteral*>(lit.get());
    std::pair<Gringo::UTerm,bool> termb = term(std::move(elit->lit));
    Clingo::AST::Term f_t = termToClingoTerm(termb.first);
    if(!termb.second) {
        throw "not implemented yet";
        // negate f_t
    }

    Clingo::AST::Literal alit{loc, Clingo::AST::Sign::None, f_t};
    return Clingo::AST::BodyLiteral{loc, elit->neg?Clingo::AST::Sign::Negation:Clingo::AST::Sign::None, alit};
}

