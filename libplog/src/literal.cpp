//
// Created by iensen on 10/14/16.
//

#include<plog/literal.h>
#include<gringo/term.hh>
#include<plog/input/attributedeclaration.h>
using Gringo::FunctionTerm;
using Gringo::ValTerm;


Literal::Literal(Relation rel, UTerm &&lt, UTerm &&rt):rel(rel),lt(std::move(lt)), rt(std::move(rt)) {
}

void Literal::print(std::ostream &out) const {
    throw "not implemented yet";
}

UTerm &Literal::getAttr() {
    return lt;
}

UTerm &Literal::getVal() {
    return rt;
}

// TODO: can we somehow avoid dynamic cast?

Gringo::String Literal::getAttrName() {

    // if the term is a function symbol
    FunctionTerm * fterm = dynamic_cast<FunctionTerm*>(lt.get());
    if(fterm!= nullptr) {
        return fterm->name;
    }

    //if the term is a valterm (constant)
    ValTerm * vterm = dynamic_cast<ValTerm*>(lt.get());
    if(vterm!= nullptr) {
        return vterm->value.name();
    }

    return "";
}

bool Literal::isRelational(const UAttDeclVec &attdecls) {
    FunctionTerm * fterm = dynamic_cast<FunctionTerm*>(lt.get());
    if(!fterm)
        return true;
    for(const UAttDecl &decl: attdecls) {
        if(decl->attname == fterm->name) {
            return false;
        }
    }
    return true;

}

ELiteral::ELiteral(ULit lit, bool neg):lit(std::move(lit)),neg(neg){}

void ELiteral::print(std::ostream &out) const {
    throw "not implemented yet";
}

UTerm &ELiteral::getAttr() {
    return lit->getAttr();
}

UTerm &ELiteral::getVal() {
    return lit->getVal();
}

String ELiteral::getAttrName() {
    return lit->getAttrName();
}

bool ELiteral::isRelational(const UAttDeclVec &attdecls) {
    return lit->isRelational(attdecls);
}

