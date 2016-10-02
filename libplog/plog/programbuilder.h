//
// Created by iensen on 9/6/16.
//

#ifndef PLOG_PROGRAMXBUILDER_H
#define PLOG_PROGRAMXBUILDER_H

#include <string>
#include <gringo/locatable.hh>
#include <gringo/output/output.hh>
#include <plog/term.h>
#include<gringo/indexed.hh>
#include<gringo/symbol.hh>
#include <groundplog/logger.h>
#include <gringo/term.hh>

using BinOp = Gringo::BinOp ;
using UnOp = Gringo::UnOp ;
using String = Gringo::String;
using Symbol = Gringo::Symbol;

template <class T, class R = unsigned>
using Indexed = Gringo::Indexed<T,R>;
using UTerm  = Gringo::UTerm ;
using UTermVec  = Gringo::UTermVec ;
using Location = Gringo::Location;
using IdVec = std::vector<std::pair<Location, String>>;
using Logger = Plog::Logger;
class Program;
class Defines;

enum IdVecUid           : unsigned { };
enum TermUid            : unsigned { };
enum TermVecUid :         unsigned { };
using IdVecs           = Indexed<IdVec, IdVecUid>;
using Terms             = Indexed<UTerm , TermUid>;
using TermVecs         = Indexed<UTermVec, TermVecUid>;

class NonGroundProgramBuilder {

public:
    NonGroundProgramBuilder(Program &prg, Defines &defs);
    IdVecUid idvec(IdVecUid uid, Location const &loc, String id);
    IdVecUid idvec();


    virtual void define(Location const &loc, String name, TermUid value, bool deafaultDef, Logger &log);
  //  void block(Location const &loc, String name, IdVecUid args);
    TermUid term(Location const &loc, BinOp op, TermUid a, TermUid b);
    TermUid term(Location const &loc, UnOp op, TermUid a);
    TermUid term(Location const &loc, Symbol val);
    TermUid term(Location const &loc, String name, TermVecUid a);
    TermUid term(Location const &loc, String name);
    TermVecUid termvec(TermVecUid uid, TermUid termUid);
    TermVecUid termvec();



private:
    Program             &prg_;
    Defines             &defs_;
    IdVecs              idvecs_;
    Terms               terms_;
    TermVecs            termvecs_;
};


#endif //PLOG_PROGRAMXBUILDER_H