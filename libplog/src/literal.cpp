//
// Created by iensen on 10/14/16.
//

#include<plog/literal.h>


Literal::Literal(Relation rel, UTerm &&lt, UTerm &&rt):rel(rel),lt(std::move(lt)), rt(std::move(rt)) {}

void Literal::print(std::ostream &out) const {
    throw "not implemented yet";
}

ELiteral::ELiteral(ULit lit, bool neg):lit(std::move(lit)),neg(neg){}

void ELiteral::print(std::ostream &out) const {
    throw "not implemented yet";
}

