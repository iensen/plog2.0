//
// Created by iensen on 10/8/16.
//

#ifndef PLOG_SORTDEFINITION_H
#define PLOG_SORTDEFINITION_H

#include <gringo/printable.hh>
#include <gringo/locatable.hh>
#include <plog/sortexpression.h>

class SortDefinition: Gringo::Printable, public Gringo::Locatable{
public:
    SortDefinition(String sortname, USortExpr && sortExpr): sortName(sortname), sexpr(std::move(sortExpr)){}
    virtual void print(std::ostream &out) const;
    const String getSortName() const;
    const USortExpr & getSortExpr() const;
private:
    String sortName;
    USortExpr  sexpr;
};
#endif //PLOG_SORTDEFINITION_H
