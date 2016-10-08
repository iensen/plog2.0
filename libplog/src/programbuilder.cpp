//
// Created by iensen on 9/16/16.
//

#include<plog/programbuilder.h>
#include<gringo/term.hh>
#include<gringo/locatable.hh>


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
        auto ret = std::make_shared<Symbol>();
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




//void NonGroundProgramBuilder::block(Location const &loc, String name, IdVecUid args) {
    //prg_.begin(loc, name, idvecs_.erase(args));
    // let's leave this empty for now and see what happens
//}
