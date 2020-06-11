//
// Created by iensen on 9/16/16.
//

#ifndef PLOG_STATEMENT_H_H
#define PLOG_STATEMENT_H_H

#include <gringo/printable.hh>
#include <gringo/locatable.hh>
#include <plog/literal.h>
#include <gringo/input/types.hh>
#include <gringo/input/literals.hh>
#include "types.h"

#include<gringo/input/literals.hh>
#include<gringo/input/programbuilder.hh>
#include<gringo/input/aggregates.hh>
#include<clingo.hh>
#include <plog/plogparser.h>
#include <plog/plog.h>


enum class StatementType { RULE, CRRULE, PR_ATOM, QUERY};
using Gringo::Input::ToGroundArg;
using UGLit = std::unique_ptr<Gringo::Input::Literal>;
using Gringo::Input::UHeadAggr ;
using UGStm = Gringo::Input::UStm ;
using Gringo::Input::UBodyAggrVec ;
using Gringo::Input::UBodyAggr;

struct Statement : Gringo::Printable, Gringo::Locatable {
    Statement(Plog::ULit &&query);
    Statement(Plog::ULit &&head, Plog::ULitVec &&body, bool isCrRule = false);
    Statement(Plog::ULit &&head, Plog::ULitVec &&body,UProb && prob);

    virtual void print(std::ostream &out) const;
    virtual void check(Logger &log) const;
    virtual void replace(Defines &dx);
    // this should ground the statement and store the result in stms (collection of gringo statements!)
    virtual void toGround(ToGroundArg &x, UStmVec &stms) const;
    virtual ~Statement();
    std::vector<Clingo::AST::Statement> toGringoAST(const UAttDeclVec & attdecls, const USortDefVec &sortDefVec, AlgorithmKind algo);
    StatementType  getType();

private:
    Clingo::AST::ComparisonOperator getComparisonOpFromRelation(Gringo::Relation rel);

    Clingo::AST::BodyLiteral  gringobodyexlit(Plog::ULit &lit,const UAttDeclVec &attdecls);
    std::vector<Clingo::AST::BodyLiteral> gringobody(const UAttDeclVec &attdecls, const USortDefVec &sortDefVec, bool solvingDCO);
    std::pair<Gringo::UTerm,bool> term(Plog::ULit & lit);

    std::unordered_set<std::string> getVariables();
    std::unordered_set<std::string> getVariables(const UTerm &term);

    std::vector<Clingo::AST::Statement> prAtomToGringoAST(const UAttDeclVec & attdecls, const USortDefVec &sortDefVec, AlgorithmKind algo);
    std::vector<Clingo::AST::Statement>queryToGringoAST(const UAttDeclVec & attdecls,  AlgorithmKind algo);
    std::vector<Clingo::AST::Statement> ruleToGringoAST(const UAttDeclVec & attdecls, const USortDefVec &sortDefVec, AlgorithmKind algo);

    static int rule_id;
    Plog::ULit     head_;
    Plog::ULitVec  body_;
    UProb probability_;
    StatementType type_;
    std::vector<Clingo::AST::BodyLiteral> getSortAtoms(const Plog::ULit &lit,const USortDefVec &sortDefVec,const UAttDeclVec & attdecls);
    std::vector<Clingo::AST::BodyLiteral> getSortAtoms(const USortDefVec &sortDefVec,const UAttDeclVec & attdecl);
    static  std::vector<String> findArgSorts(String attName, const UAttDeclVec & attdecls);
    Clingo::AST::Term make_unique_term_with_name(const char *);
    Clingo::AST::Term make_external_term();
    Clingo::AST::Term make_apply_term(bool negation);
    Clingo::AST::Statement make_external_atom_rule(const UAttDeclVec & attdecls, const USortDefVec &sortDefVec);


public:
    static Clingo::AST::BodyLiteral make_body_lit(String name, std::vector<Clingo::AST::Term> args, Clingo::AST::Sign sign = Clingo::AST::Sign::None);
    static Clingo::AST::Literal make_lit(String name, std::vector<Clingo::AST::Term> args);
    static Clingo::AST::Term make_term(String name, std::vector<Clingo::AST::Term> args);
    static Clingo::AST::Term make_term(String name);
};

#endif //PLOG_STATEMENT_H_H
