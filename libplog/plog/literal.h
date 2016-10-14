//
// Created by iensen on 10/14/16.
//

#ifndef PLOG_NGRLITERAL_H
#define PLOG_NGRLITERAL_H

#include <gringo/printable.hh>
#include <gringo/locatable.hh>
#include <gringo/base.hh>

using Relation = Gringo::Relation ;
using UTerm = Gringo::UTerm ;
struct Literal;


struct Literal : public Gringo::Printable, public Gringo::Locatable {

    Literal() {}
    Literal(Relation rel, UTerm &&left, UTerm &&right);
    virtual void print(std::ostream &out) const;
    Relation rel;
    UTerm lt;
    UTerm rt;
};


using ULit = std::unique_ptr<Literal>;
using ULitVec = std::vector<ULit>;

struct ELiteral : public Literal {

    ELiteral(ULit lit, bool neg);
    virtual void print(std::ostream &out) const;
    ULit lit;
    bool neg;

};

#endif //PLOG_NGRLITERAL_H
