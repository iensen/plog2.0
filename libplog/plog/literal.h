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
using Gringo::String;
struct Literal;


struct Literal : public Gringo::Printable, public Gringo::Locatable {

    Literal() {}
    Literal(Relation rel, UTerm &&left, UTerm &&right);
    virtual void print(std::ostream &out) const;
    Relation rel;
    UTerm lt;
    UTerm rt;
    virtual UTerm & getAttr();
    virtual UTerm & getVal();
    virtual String getAttrName();

};


using ULit = std::unique_ptr<Literal>;
using ULitVec = std::vector<ULit>;

// change this to either use composition or inheritance
// currently, two copies of lt/rt are stored..

struct ELiteral :public Literal {

    ELiteral(ULit lit, bool neg);
    virtual void print(std::ostream &out) const;
    ULit lit;
    bool neg;
    UTerm & getAttr() override;
    UTerm & getVal() override;
    String getAttrName() override ;


};

#endif //PLOG_NGRLITERAL_H
