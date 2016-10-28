//
// Created by iensen on 9/16/16.
//

#include<plog/programbuilder.h>
#include<gringo/term.hh>
#include<gringo/locatable.hh>
#include <plog/input/attributedeclaration.h>
#include<plog/ploggrammar.tab.hh>

using Gringo::make_locatable;
using Gringo::gringo_make_unique;
using ValTerm = Gringo::ValTerm;
using BinOpTerm = Gringo::BinOpTerm;
using UnOpTerm = Gringo::UnOpTerm;
using FunctionTerm = Gringo::FunctionTerm;
using VarTerm = Gringo::VarTerm;


NonGroundProgramBuilder::NonGroundProgramBuilder(Program &prg, Defines &defs):prg_(prg)
        , defs_(defs)
{

}

IdVecUid NonGroundProgramBuilder::idvec() {
    return idvecs_.emplace();
}

IdVecUid NonGroundProgramBuilder::idvec(IdVecUid uid, Location const &loc, String id) {
    idvecs_[uid].emplace_back(loc, id);
    return uid;
}

void NonGroundProgramBuilder::define(const Location &loc, String name, TermUid value, bool defaultDef, Logger &log) {
    defs_.add(loc, name, terms_.erase(value),defaultDef, log);
}

TermUid NonGroundProgramBuilder::term(Location const &loc, BinOp op, TermUid a, TermUid b) {
    return terms_.insert(make_locatable<BinOpTerm>(loc, op, terms_.erase(a), terms_.erase(b)));
}

TermUid NonGroundProgramBuilder::term(Location const &loc, UnOp op, TermUid a) {
    return terms_.insert(make_locatable<UnOpTerm>(loc, op, terms_.erase(a)));
}



TermUid NonGroundProgramBuilder::term(Location const &loc, Symbol val) {
    return terms_.insert(make_locatable<ValTerm>(loc, val));
}

TermVecUid NonGroundProgramBuilder::termvec(TermVecUid uid, TermUid termUid) {
    termvecs_[uid].emplace_back(terms_.erase(termUid));
    return uid;
}

TermVecUid NonGroundProgramBuilder::termvec() {
    return termvecs_.emplace();
}

TermUid NonGroundProgramBuilder::term(Location const &loc, String name, TermVecUid a) {
    return terms_.insert(make_locatable<FunctionTerm>(loc, name, std::move(termvecs_.erase(a))));
}

TermUid NonGroundProgramBuilder::term(Location const &loc, String name) {

    auto &ret(vals_[name]);
    if (!ret) { ret = std::make_shared<Symbol>(); }
    return terms_.insert(make_locatable<VarTerm>(loc, name, ret));

}

SortExprUid NonGroundProgramBuilder::sortexpr(Location const &loc, TermUid from, TermUid to) {
    return sortexprs_.insert(make_locatable<Range>(loc, std::move(terms_.erase(from)), std::move(terms_.erase(to))));
}

SortExprUid NonGroundProgramBuilder::sortexpr(Location const &loc, TermVecUid tvec) {
    return sortexprs_.insert(make_locatable<CurlyBrackets>(loc, std::move(termvecs_.erase(tvec))));
}

SortExprUid NonGroundProgramBuilder::sortexpr(Location const &loc, SortExprVecUid svec) {
    return sortexprs_.insert(make_locatable<Concatenation>(loc, std::move(sortexprvecs_.erase(svec))));
}

SortExprUid NonGroundProgramBuilder::sortexpr(Location const &loc, Symbol sym) {
    return sortexprs_.insert(make_locatable<SortNameExpr>(loc, sym));
}

SortExprUid NonGroundProgramBuilder::sortexpr(Location const &loc, Symbol smb, VarSortExprVecUid uid, CondUid cond) {
    return sortexprs_.insert(make_locatable<FuncSortExpr>(loc, smb, std::move(varsortexprvecs_.erase(uid)),
                                                          conds_.erase(cond)));

}

SortExprUid NonGroundProgramBuilder::sortexpr(Location const &loc, Symbol smb, VarSortExprVecUid uid) {
    return sortexprs_.insert(make_locatable<FuncSortExpr>(loc, smb, std::move(varsortexprvecs_.erase(uid)),
                                                          nullptr));
}


SortExprVecUid NonGroundProgramBuilder::sortexprvec() {
    return sortexprvecs_.emplace();
}

SortExprVecUid NonGroundProgramBuilder::sortexprvec(SortExprVecUid uid, SortExprUid sExpr) {
    sortexprvecs_[uid].emplace_back(sortexprs_.erase(sExpr));
    return uid;
}

SortExprUid NonGroundProgramBuilder::sortexpr(Location const &loc, SEBinOp op, SortExprUid left, SortExprUid right) {
    return sortexprs_.insert(make_locatable<BinOpSortExpr>(loc, op, std::move(sortexprs_.erase(left)), std::move(sortexprs_.erase(right))));

}

CondUid NonGroundProgramBuilder::cond(Relation rel, String leftvar, String rightvar) {
    return conds_.insert(gringo_make_unique<UnaryCondition>(rel,leftvar,rightvar));
}

CondUid NonGroundProgramBuilder::cond(LogicBinOp rel, CondUid leftcond, CondUid rightcond) {
    return conds_.insert(gringo_make_unique<BinOpCondition>(rel,std::move(conds_.erase(leftcond)), std::move(conds_.erase(rightcond))));
}

VarSortExprUid NonGroundProgramBuilder::varsortexpr(SortExprUid seid, String var) {
    return varsortexprs_.insert(gringo_make_unique<VarSortExpression>(std::move(sortexprs_.erase(seid)),var));
}

VarSortExprVecUid NonGroundProgramBuilder::varsortexprvec() {
    return varsortexprvecs_.emplace();
}

VarSortExprVecUid NonGroundProgramBuilder::varsortexprvec(VarSortExprVecUid vec, VarSortExprUid exp) {
    varsortexprvecs_[vec].emplace_back(varsortexprs_.erase(exp));
    return vec;
}

void NonGroundProgramBuilder::attdecl(Location const &loc, String name, SortExprVecUid svec, SortExprUid sExpr) {
    prg_.add(make_locatable<AttributeDeclaration>(loc, name, sortexprvecs_.erase(svec),sortexprs_.erase(sExpr)));
}

void NonGroundProgramBuilder::sortdef(Location const &loc, String name, SortExprUid se) {
    prg_.add(make_locatable<SortDefinition>(loc, name, sortexprs_.erase(se)));

}

TermUid NonGroundProgramBuilder::boolterm(bool val) {
    String sval = val?String("true"):String("false");
    return term(DefaultLocation(), Symbol::createId(sval));
}

LitUid NonGroundProgramBuilder::lit(Location const &loc, String id, TermVecUid tvec) {
    TermUid lt  = term(DefaultLocation(),id,tvec);
    TermUid rt = boolterm(true);
    return lits_.insert(make_locatable<Literal>(loc, Relation::EQ, terms_.erase(lt),terms_.erase(rt)));
}

LitUid NonGroundProgramBuilder::lit(Location const &loc, String id, TermVecUid tvec, TermUid tid) {
    TermUid lt  = term(DefaultLocation(),id,tvec);
    return lits_.insert(make_locatable<Literal>(loc, Relation::EQ, terms_.erase(lt),terms_.erase(tid)));

}

LitUid NonGroundProgramBuilder::lit(Location const &loc, String id, TermUid tid) {
    TermUid lt  = term(DefaultLocation(),id);
    return lits_.insert(make_locatable<Literal>(loc, Relation::EQ, terms_.erase(lt),terms_.erase(tid)));

}

LitUid NonGroundProgramBuilder::lit(Location const &loc, String att_name, String range_name) {
    TermUid lt  = term(DefaultLocation(),String("random"),termvec(att_name,range_name));
    return lits_.insert(make_locatable<Literal>(loc, Relation::EQ, terms_.erase(lt),terms_.erase(boolterm(true))));

}

LitUid NonGroundProgramBuilder::lit(Location const &loc, TermUid t) {
    return lits_.insert(make_locatable<Literal>(loc, Relation::EQ, terms_.erase(t),terms_.erase(boolterm(true))));

}

LitUid NonGroundProgramBuilder::lit(Location const &loc, TermUid t1, Relation rel, TermUid t2) {
    return lits_.insert(make_locatable<Literal>(loc, rel, terms_.erase(t1),terms_.erase(t2)));
}


LitUid NonGroundProgramBuilder::lit(bool type) {
     return lit(DefaultLocation(), term(DefaultLocation(), Symbol::createNum(0)),
                type ? Relation::EQ : Relation::NEQ, term(DefaultLocation(), Symbol::createNum(0)));
}



LitUid NonGroundProgramBuilder::elit(Location const &loc, LitUid lit, bool negative) {
    return lits_.insert(make_locatable<ELiteral>(loc, lits_.erase(lit),negative));
}

TermVecUid NonGroundProgramBuilder::termvec(String el1, String el2) {
    TermVecUid  tvec = termvec();
    termvec(tvec,term(DefaultLocation(),el1));
    termvec(tvec,term(DefaultLocation(),el2));
    return tvec;
}

BdLitVecUid NonGroundProgramBuilder::body() {
    return bodies_.emplace();
}

BdLitVecUid NonGroundProgramBuilder::body(BdLitVecUid bid, LitUid elit) {
    bodies_[bid].emplace_back(lits_.erase(elit));
    return bid;
}

void NonGroundProgramBuilder::rule(Location const &loc, LitUid head, BdLitVecUid body) {
    prg_.add(make_locatable<Statement>(loc, lits_.erase(head), bodies_.erase(body)));
}

void NonGroundProgramBuilder::rule(Location const &loc, LitUid head) {
    rule(loc, head, body());
}

void NonGroundProgramBuilder::pratom(Location const &loc, LitUid head, BdLitVecUid body, ProbUid prob) {
    prg_.add(make_locatable<Statement>(loc, lits_.erase(head), bodies_.erase(body),probs_.erase(prob)));
}

ProbUid NonGroundProgramBuilder::prob(Location const &loc, int num, int denum) {
    return probs_.insert(make_locatable<Probability>(loc, num,denum));
}

void NonGroundProgramBuilder::query(const Location &loc, LitUid query) {
    prg_.add(make_locatable<Statement>(loc, lits_.erase(query)));

}





//void NonGroundProgramBuilder::block(Location const &loc, String name, IdVecUid args) {
    //prg_.begin(loc, name, idvecs_.erase(args));
    // let's leave this empty for now and see what happens
//}
