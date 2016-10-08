//
// Created by iensen on 9/6/16.
//

#ifndef PLOG_PROGRAMXBUILDER_H
#define PLOG_PROGRAMXBUILDER_H

#include <string>
#include <gringo/locatable.hh>
#include <gringo/output/output.hh>
#include <plog/term.h>
#include <gringo/indexed.hh>
#include <gringo/symbol.hh>
#include <groundplog/logger.h>
#include <gringo/term.hh>
#include <gringo/base.hh>
#include <plog/sortexpression.h>

using BinOp = Gringo::BinOp ;
using UnOp = Gringo::UnOp ;
using String = Gringo::String;
using Symbol = Gringo::Symbol;
using Relation = Gringo::Relation;

template <class T, class R = unsigned>
using Indexed = Gringo::Indexed<T,R>;
using UTermVec  = Gringo::UTermVec ;

using Location = Gringo::Location;
using IdVec = std::vector<std::pair<Location, String>>;
using Logger = Plog::Logger;
class Program;
class Defines;

enum IdVecUid           : unsigned { };
enum TermUid            : unsigned { };
enum TermVecUid         : unsigned { };
enum SortExprUid        : unsigned { };
enum SortExprVecUid     : unsigned { };
enum VarSortExprVecUid  : unsigned { };
enum VarSortExprUid     : unsigned { };
enum CondUid            : unsigned { };
using UTerm = Gringo::UTerm ;

using IdVecs           = Indexed<IdVec, IdVecUid>;
using Terms            = Indexed<UTerm , TermUid>;
using TermVecs         = Indexed<UTermVec, TermVecUid>;
using SortExprs        = Indexed<USortExpr, SortExprUid>;
using SortExprVecs     = Indexed<USortExprVec, SortExprVecUid>;
using VarSortExprs     = Indexed<UVarSortExpr, VarSortExprUid>;
using VarSortExprVecs  = Indexed<UVarSortExprVec, VarSortExprVecUid >;
using Conditions  = Indexed<UCond, CondUid>;

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

    // sort expressions:
    SortExprUid  sortexpr(Location const &loc, TermUid from, TermUid to);
    SortExprUid  sortexpr(Location const &loc, TermVecUid tvec);
    SortExprUid  sortexpr(Location const &loc, SortExprVecUid tvec);
    SortExprUid  sortexpr(Location const &loc, Symbol tvec);
    SortExprUid  sortexpr(Location const &loc, Symbol smb, VarSortExprVecUid uid);
    SortExprUid  sortexpr(Location const &loc, Symbol smb, VarSortExprVecUid uid, CondUid cond);
    SortExprUid  sortexpr(Location const &loc, SEBinOp op, SortExprUid left, SortExprUid right);
    VarSortExprUid varsortexpr(SortExprUid seid, String var);


    // sort expression vectors:
    SortExprVecUid  sortexprvec(SortExprVecUid uid,  SortExprUid sExpr);
    SortExprVecUid  sortexprvec();
    VarSortExprVecUid varsortexprvec();
    VarSortExprVecUid varsortexprvec(VarSortExprVecUid vec, VarSortExprUid exp);


    // conditions:
    CondUid  cond(Relation rel, String leftvar, String rightvar);
    CondUid  cond(LogicBinOp rel, CondUid leftcond, CondUid rightcond);

private:
    Program             &prg_;
    Defines             &defs_;
    IdVecs              idvecs_;
    Terms               terms_;
    TermVecs            termvecs_;
    SortExprs           sortexprs_;
    SortExprVecs        sortexprvecs_;
    VarSortExprs        varsortexprs_;
    VarSortExprVecs     varsortexprvecs_;
    Conditions          conds_;
};


#endif //PLOG_PROGRAMXBUILDER_H