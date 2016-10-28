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

enum class StatementType { RULE, PR_ATOM, QUERY};
using Gringo::Input::ToGroundArg;
using UGLit = std::unique_ptr<Gringo::Input::Literal>;
using Gringo::Input::UHeadAggr ;
using UGStm = Gringo::Input::UStm ;

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
    UGStm toGringo();
    StatementType  getType();

private:
    Gringo::UTerm gringovalterm(String rep);
    UHeadAggr head(UGLit && lit);
    std::pair<Gringo::UTerm,bool> term(ULit && lit);
    UGStm prAtomToGringo();
    UGStm queryToGringo();
    UGStm ruleToGringo();
    ULit     head_;
    ULitVec  body_;
    UProb probability_;
    StatementType type_;
};

#endif //PLOG_STATEMENT_H_H
