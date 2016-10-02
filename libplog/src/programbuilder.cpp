//
// Created by iensen on 9/16/16.
//

#include<plog/programbuilder.h>
#include<gringo/term.hh>
#include<gringo/locatable.hh>

using Gringo::make_locatable;

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

//void NonGroundProgramBuilder::block(Location const &loc, String name, IdVecUid args) {
    //prg_.begin(loc, name, idvecs_.erase(args));
    // let's leave this empty for now and see what happens
//}
