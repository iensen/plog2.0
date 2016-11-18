//
// Created by iensen on 9/16/16.
//

#ifndef PLOG_STATEMENT_H_H
#define PLOG_STATEMENT_H_H

#include <gringo/printable.hh>
#include <gringo/locatable.hh>
#include <plog/literal.h>
#include <gringo/input/types.hh>
#include <gringo/input/literals.hh>
#include "types.h"

#include<gringo/input/literals.hh>
#include<gringo/input/programbuilder.hh>
#include<gringo/input/aggregates.hh>
#include<clingo.hh>

enum class StatementType { RULE, PR_ATOM, QUERY};
using Gringo::Input::ToGroundArg;
using UGLit = std::unique_ptr<Gringo::Input::Literal>;
using Gringo::Input::UHeadAggr ;
using UGStm = Gringo::Input::UStm ;
using Gringo::Input::UBodyAggrVec ;
using Gringo::Input::UBodyAggr;

struct Statement : Gringo::Printable, Gringo::Locatable {
    Statement(ULit &&query);
    Statement(ULit &&head, ULitVec &&body);
    Statement(ULit &&head, ULitVec &&body,UProb && prob);

    virtual void print(std::ostream &out) const;
    virtual void check(Logger &log) const;
    virtual void replace(Defines &dx);
    // this should ground the statement and store the result in stms (collection of gringo statements!)
    virtual void toGround(ToGroundArg &x, UStmVec &stms) const;
    virtual ~Statement();
    Clingo::AST::Statement toGringoAST();
    StatementType  getType();

private:
    Clingo::AST::BodyLiteral  gringobodyelast(ULit &lit);
    std::vector<Clingo::AST::BodyLiteral> gringobodyast();
    std::pair<Gringo::UTerm,bool> term(ULit && lit);


    Clingo::AST::Statement prAtomToGringoAST();
    Clingo::AST::Statement queryToGringoAST();
    Clingo::AST::Statement ruleToGringoAST();

    ULit     head_;
    ULitVec  body_;
    UProb probability_;
    StatementType type_;
    char *numbuf;
    char *denumbuf;
};

#endif //PLOG_STATEMENT_H_H
