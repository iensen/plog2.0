//
// Created by iensen on 10/14/16.
//

#include<plog/literal.h>
#include<gringo/term.hh>
#include<plog/input/attributedeclaration.h>
#include<plog/input/utils.h>
using Gringo::FunctionTerm;
using Gringo::ValTerm;

namespace  Plog {

    Literal::Literal(Relation rel, UTerm &&lt, UTerm &&rt) : rel(rel), lt(std::move(lt)), rt(std::move(rt)) {
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

    Gringo::String Literal::getAttrName() {
        return ::getAttrName(lt);
    }

    bool Literal::isRelational(const UAttDeclVec &attdecls) {

        String attrName = getAttrName();
        if (attrName == "")
            return true;
        if(attrName == "obs" || attrName == "do") { // allow do and obs in bodies
            return false;
        }
        for (const UAttDecl &decl: attdecls) {
            if (decl->attname == attrName) {
                return false;
            }
        }
        return true;
    }

    ELiteral::ELiteral(ULit lit, bool neg) : lit(std::move(lit)), neg(neg) {}

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
}

