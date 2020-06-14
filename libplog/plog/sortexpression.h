//
// Created by iensen on 10/2/16.
//

#ifndef PLOG_SORTEXPRESSION_H
#define PLOG_SORTEXPRESSION_H


#include "term.h"
#include <gringo/printable.hh>
#include <gringo/locatable.hh>
#include <gringo/symbol.hh>
#include <gringo/base.hh>
#include <clingo.hh>
#include <plog/input/types.h>

enum class LogicBinOp: int {AND, OR};
enum class SEBinOp : int { UNION, INTERSECT, SUBTRACT };

using String = Gringo::String;
using Symbol = Gringo::Symbol;
using Relation = Gringo::Relation;


struct SortExpression: public Gringo::Printable, public Gringo::Locatable{
     virtual std::vector<Clingo::AST::Term> generate( const USortDefVec &sortDefVec) = 0;
     void print(std::ostream &out) const;
     virtual std::string toString() const =0 ;
};

using UTerm  = Gringo::UTerm ;
using UTermVec  = Gringo::UTermVec ;


struct VarSortExpression {
    explicit VarSortExpression(USortExpr expr):expr(std::move(expr)), varName(""){};
    VarSortExpression(USortExpr expr, String var):expr(std::move(expr)), varName(var){};
    USortExpr expr;
    String varName;
};

using UVarSortExpr = std::unique_ptr<VarSortExpression>;
using UVarSortExprVec = std::vector<UVarSortExpr>;

struct Range:public SortExpression {
    Range(UTerm && from, UTerm && to);
    std::string toString() const override;
    std::vector<Clingo::AST::Term> generate( const USortDefVec &sortDefVec) override;
    UTerm from;
    UTerm to;
};

struct Concatenation: public SortExpression {
    Concatenation(USortExprVec);
    std::string toString() const override;
    std::vector<Clingo::AST::Term> generate( const USortDefVec &sortDefVec) override;
    USortExprVec  sexprvec;
};


struct CurlyBrackets: public SortExpression {
    CurlyBrackets(UTermVec tvec):termvec(std::move(tvec)){}
    std::string toString() const override;
    std::vector<Clingo::AST::Term> generate( const USortDefVec &sortDefVec) override;

    UTermVec  termvec;
};


struct SortNameExpr: public SortExpression {
    SortNameExpr(String name) :name(name){};
    std::string toString() const override;
    std::vector<Clingo::AST::Term> generate( const USortDefVec &sortDefVec) override;
    String name;
};

struct Condition:public Gringo::Printable {

};

struct UnaryCondition: public Condition {
    UnaryCondition(Relation rel, String leftvar, String rightvar):rel(rel),leftvar(leftvar), rightvar(rightvar) {}
    Relation rel;
    virtual void print(std::ostream &out) const;
    String leftvar;
    String rightvar;
};



using UCond = std::unique_ptr<Condition>;


struct BinOpCondition:public Condition {
    BinOpCondition(LogicBinOp op, UCond left, UCond right):op(op), left(std::move(left)), right(std::move(right)){};
    virtual void print(std::ostream &out) const;
    LogicBinOp op;
    UCond left;
    UCond right;
};


struct FuncSortExpr:public SortExpression {
    FuncSortExpr(Symbol fname, UVarSortExprVec vec, UCond cond):fname(fname),vec(std::move(vec)),cond(std::move(cond)){};
    std::string toString() const override;
    std::vector<Clingo::AST::Term> generate( const USortDefVec &sortDefVec) override;
    Symbol fname;
    UVarSortExprVec  vec;
    UCond cond;
private:
    std::vector<Clingo::AST::Term> generate( const USortDefVec &sortDefVec, std::vector<Clingo::AST::Term> &args);
};


struct BinOpSortExpr:public SortExpression {
    BinOpSortExpr(SEBinOp op, USortExpr left, USortExpr right):op(op), left(std::move(left)), right(std::move(right)){};
    std::string toString() const override;
    std::vector<Clingo::AST::Term> generate( const USortDefVec &sortDefVec) override;
    SEBinOp op;
    USortExpr left;
    USortExpr right;
};




#endif //PLOG_SORTEXPRESSION_H
