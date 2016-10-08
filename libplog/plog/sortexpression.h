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


enum class LogicBinOp: int {AND, OR};
enum class SEBinOp : int { UNION, INTERSECT, SUBTRACT };

using String = Gringo::String;
using Symbol = Gringo::Symbol;
using Relation = Gringo::Relation;


struct SortExpression: public Gringo::Printable, public Gringo::Locatable{
     //virtual std::vector<UTerm> generate() = 0;
};

using UTerm  = Gringo::UTerm ;
using UTermVec  = Gringo::UTermVec ;
using USortExpr = std::unique_ptr<SortExpression>;
using USortExprVec = std::vector<USortExpr>;

struct VarSortExpression {
    VarSortExpression(USortExpr expr, String var):expr(std::move(expr)), varName(var){};
    virtual void print(std::ostream &out) const;
    USortExpr expr;
    String varName;
};

using UVarSortExpr = std::unique_ptr<VarSortExpression>;
using UVarSortExprVec = std::vector<UVarSortExpr>;

struct Range:public SortExpression {
    Range(UTerm && from, UTerm && to);
    virtual void print(std::ostream &out) const;
    UTerm from;
    UTerm to;
};

struct Concatenation: public SortExpression {
    Concatenation(USortExprVec);
    virtual void print(std::ostream &out) const;
    USortExprVec  sexprvec;
};


struct CurlyBrackets: public SortExpression {
    CurlyBrackets(UTermVec tvec):termvec(std::move(tvec)){}
        virtual void print(std::ostream &out) const;
    UTermVec  termvec;
};


struct SortNameExpr: public SortExpression {
    SortNameExpr(Symbol s):s(s){};
    virtual void print(std::ostream &out) const;
    Symbol s;
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
    BinOpCondition(LogicBinOp op, UCond left, UCond right){};
    virtual void print(std::ostream &out) const;
    SEBinOp op;
    UCond left;
    UCond right;
};


struct FuncSortExpr:public SortExpression {
    FuncSortExpr(Symbol fname, UVarSortExprVec vec, UCond cond):fname(fname),vec(std::move(vec)),cond(std::move(cond)){};
    virtual void print(std::ostream &out) const;
    Symbol fname;
    UVarSortExprVec  vec;
    UCond cond;
};


struct BinOpSortExpr:public SortExpression {
    BinOpSortExpr(SEBinOp op, USortExpr left, USortExpr right){};
    virtual void print(std::ostream &out) const;
    SEBinOp op;
    USortExpr left;
    USortExpr right;
};




#endif //PLOG_SORTEXPRESSION_H
