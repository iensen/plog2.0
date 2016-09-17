//
// Created by iensen on 9/16/16.
//

#ifndef PLOG_STATEMENT_H_H
#define PLOG_STATEMENT_H_H

#include <gringo/printable.hh>
#include <gringo/locatable.hh>
#include<gringo/input/types.hh>
#include "types.h"

enum class StatementType { RULE, PR_ATOM};
using Gringo::Input::ToGroundArg;



struct Statement : Gringo::Printable, Gringo::Locatable {
    Statement(UHead &&head, UBody &&body);
    Statement(UHead &&head, UBody &&body,UProb && prob);

    virtual UStmVec unpool(bool beforeRewrite);
    virtual void print(std::ostream &out) const;
    virtual bool hasPool(bool beforeRewrite) const;
    virtual void check(Logger &log) const;
    virtual void replace(Defines &dx);
    // this should ground the statement and store the result in stms (collection of gringo statements!)
    virtual void toGround(ToGroundArg &x, UStmVec &stms) const;
    virtual ~Statement();

    UHead     head;
    UBody  body;
    UProb probability;
    StatementType type;
};

#endif //PLOG_STATEMENT_H_H
