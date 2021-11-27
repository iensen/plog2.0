//
// Created by iensen on 10/8/16.
//

#ifndef PLOG_ATTRIBUTEDECLARATION_H
#define PLOG_ATTRIBUTEDECLARATION_H


#include <gringo/printable.hh>
#include <gringo/locatable.hh>
#include<plog/input/types.h>
#include<plog/sortexpression.h>

using Gringo::String;

struct AttributeDeclaration : Gringo::Printable, Gringo::Locatable {

    AttributeDeclaration(String attname, USortExprVec && svec, USortExpr &&se):
            attname(attname),svec(std::move(svec)),se(std::move(se)) {
    }


    virtual void print(std::ostream &out) const;

    virtual ~AttributeDeclaration();

    const String attname;
    USortExprVec     svec;
    USortExpr se;
};


#endif //PLOG_ATTRIBUTEDECLARATION_H
