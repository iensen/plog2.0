// {{{ GPL License

// This file is part of gringo - a grounder for logic programs.
// Copyright (C) 2013  Roland Kaminski

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,it
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// }}}

// {{{1 preamble
%require "2.5"
%define api.namespace {PlogGrammar}
%define api.prefix {PlogGrammar_}
//%define parse.error verbose
%error-verbose
%define api.location.type {DefaultLocation}
%locations
%defines
%parse-param { PlogParser *lexer }
%lex-param { PlogParser *lexer }
%skeleton "lalr1.cc"
%define parse.trace
%debug


// {{{1 auxiliary code

%code requires
{
    #include "plog/programbuilder.h"

    class PlogParser;

    struct DefaultLocation : Gringo::Location {
        DefaultLocation() : Location("<undef>", 0, 0, "<undef>", 0, 0) { }
    };

}

%{

#include "plogparser.h"
#include "programbuilder.h"
#include <gringo/base.hh>
#include <climits>
using Relation = Gringo::Relation;
#define BUILDER (lexer->builder())
#define LOGGER (lexer->logger())
#define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do {                                                               \
        if (N) {                                                       \
            (Current).beginFilename = YYRHSLOC (Rhs, 1).beginFilename; \
            (Current).beginLine     = YYRHSLOC (Rhs, 1).beginLine;     \
            (Current).beginColumn   = YYRHSLOC (Rhs, 1).beginColumn;   \
            (Current).endFilename   = YYRHSLOC (Rhs, N).endFilename;   \
            (Current).endLine       = YYRHSLOC (Rhs, N).endLine;       \
            (Current).endColumn     = YYRHSLOC (Rhs, N).endColumn;     \
        }                                                              \
        else {                                                         \
            (Current).beginFilename = YYRHSLOC (Rhs, 0).endFilename;   \
            (Current).beginLine     = YYRHSLOC (Rhs, 0).endLine;       \
            (Current).beginColumn   = YYRHSLOC (Rhs, 0).endColumn;     \
            (Current).endFilename   = YYRHSLOC (Rhs, 0).endFilename;   \
            (Current).endLine       = YYRHSLOC (Rhs, 0).endLine;       \
            (Current).endColumn     = YYRHSLOC (Rhs, 0).endColumn;     \
        }                                                              \
    }                                                                  \
    while (false)

int PlogGrammar_lex(void *value, Gringo::Location* loc, PlogParser *lexer) {
    return lexer->lex(value, *loc);
}

%}

%code {

void PlogGrammar::parser::error(DefaultLocation const &l, std::string const &msg) {
    lexer->parseError(l, msg);
}

}


// {{{1 nonterminals

// {{{2 union type for stack elements
%union
{
      uintptr_t str;
      int num;
      TermUid term;
      TermVecUid termvec;
      SortExprVecUid sortexprvec;
      VarSortExprVecUid varsortexprvec;
      SortExprUid sortexpr;
      VarSortExprUid varsortexpr;
      CondUid cond;
      LitUid lit;
      Gringo::Relation rel;
      BdLitVecUid body;
      ProbUid prob;
}

// }}}2

// declare types here:
%type <sortexpr>        range sort_expr functional_symbol curly_brackets concat_elem
%type <varsortexpr>     var_sort_expr
%type <sortexprvec>     sort_expr_vec concatenation
%type <varsortexprvec>  var_sort_expr_list
%type <term>            constterm comparable_constterm term
%type <termvec>         ntermvec consttermvec
%type <cond>            cond
%type <rel>             cmp
%type <lit>             literal e_literal head_atom head
%type <body>            body
%type <prob>            probability

// {{{1 terminals

%token
    SORTDEFKEYWORD
    ATTDEFKEYWORD
    STMTDEFKEYWORD
    AND         "&"
    ADD         "+"
    EQ          "="
    COLON       ":"
    COMMA       ","
    CONST       "#const"
    DOT         "."
    DOTS        ".."
    END         0 "<EOF>"
    GEQ         ">="
    ARROW       "->"
    GT          ">"
    IF          ":-"
    LBRACE      "{"
    LBRACK      "["
    VBAR        "|"
    LEQ         "<="
    LPAREN      "("
    LT          "<"
    MUL         "*"
    NEQ         "!="
    QUESTION    "?"
    MOD         "\\"
    POW         "^"
    RBRACE      "}"
    RBRACK      "]"
    PR          "pr"
    RPAREN      ")"
    SLASH       "/"
    SUB         "-"
    UBNOT
    UMINUS

%token <num>
    NUMBER     "<NUMBER>"

%token <str>
    IDENTIFIER "<IDENTIFIER>"
    VARIABLE   "<VARIABLE>"
    NOT        "not"
    SORT_NAME  "<SORT_NAME>"

// {{{2 operator precedence and associativity

%left DOTS
%left VBAR
%left AND
%left ADD SUB
%left MUL SLASH MOD
%right POW
%left UMINUS UBNOT

// }}}1

%%
// {{{1  program and global definitions

program
    : directives sorts_sec atts_sec stmts_sec query |
      directives atts_sec stmts_sec query |
     ;



// {{{1


// {{{2 directives

directives  : directives directive
    |
    ;

directive: const_decl
    ;


const_decl: CONST IDENTIFIER[uid] EQ constterm[rhs] DOT{ BUILDER.define(@$, String::fromRep($uid), $rhs, true, LOGGER);}
      ;


// {{{3


// {{{3 sorts_sec

sorts_sec : SORTDEFKEYWORD sort_defs
    ;

sort_defs: sort_defs sort_def
    |
    ;

sort_def: SORT_NAME[sn] "=" sort_expr[se] DOT {BUILDER.sortdef(@$, String::fromRep($sn),$se);}
    ;

sort_expr:
            range |
            concatenation[c] {$$ = BUILDER.sortexpr(@$,$c); } |
            functional_symbol |
            SORT_NAME[s] {$$ = BUILDER.sortexpr(@$,String::fromRep($s));} |
            curly_brackets |
            sort_expr[a] ADD sort_expr[b] {$$ = BUILDER.sortexpr(@$,SEBinOp::UNION,$a,$b);}  |
            sort_expr[a] MUL sort_expr[b] {$$ = BUILDER.sortexpr(@$,SEBinOp::INTERSECT,$a,$b);} |
            sort_expr[a] SUB sort_expr[b] {$$ = BUILDER.sortexpr(@$,SEBinOp::SUBTRACT,$a,$b);}|
            LPAREN sort_expr[a] RPAREN {$$ = $a;}
      ;

range: comparable_constterm[a] DOTS comparable_constterm[b] { $$=BUILDER.sortexpr(@$, $a, $b); }
      ;

concatenation: concatenation[a] concat_elem[b] { $$ = BUILDER.sortexprvec( $a,$b);}
       | concat_elem[b] { $$ = BUILDER.sortexprvec(BUILDER.sortexprvec(), $b);}
       ;

concat_elem: LBRACK sort_expr[a] RBRACK {$$ = $a;}
       ;

functional_symbol: IDENTIFIER[a] LPAREN var_sort_expr_list[b] RPAREN
             {$$ = BUILDER.sortexpr(@$, Symbol::createId(String::fromRep($a)), $b);} |
        IDENTIFIER[a] LPAREN var_sort_expr_list[b] RPAREN COLON cond[c]
             {$$ = BUILDER.sortexpr(@$, Symbol::createId(String::fromRep($a)), $b, $c);}
       ;

cond: VARIABLE[a] cmp[rel] VARIABLE[b]{$$ = BUILDER.cond($rel, String::fromRep($a),String::fromRep($b));} |
       cond[a] VBAR cond[b] { $$ = BUILDER.cond( LogicBinOp::OR, $a,$b); }|
       cond[a] AND  cond [b] { $$ = BUILDER.cond( LogicBinOp::AND, $a,$b); }|
       LPAREN cond[a] RPAREN {$$ = $a;}
       ;




var_sort_expr_list: var_sort_expr_list[a] COMMA var_sort_expr[b] {$$ = BUILDER.varsortexprvec($a,$b); }
       | var_sort_expr[a] {$$ = BUILDER.varsortexprvec(BUILDER.varsortexprvec(),$a); }
       ;

var_sort_expr: sort_expr[a] {$$ = BUILDER.varsortexpr($a, nullptr);}|
               sort_expr[a] LPAREN VARIABLE[v] RPAREN {$$ = BUILDER.varsortexpr($a, String::fromRep($v));}


curly_brackets: LBRACE consttermvec[a] RBRACE {$$=BUILDER.sortexpr(@$, $a);}|
                LBRACE RBRACE {$$=BUILDER.sortexpr(@$, BUILDER.termvec());}
        ;



// {{{4 att_sec

atts_sec: ATTDEFKEYWORD att_defs

att_defs: att_defs att_def
       |
       ;

att_def: IDENTIFIER[a] COLON sort_expr_vec[v] ARROW sort_expr[r] DOT {BUILDER.attdecl(@$, String::fromRep($a),$v,$r);}
       | IDENTIFIER[a] COLON sort_expr[r] DOT {BUILDER.attdecl(@$, String::fromRep($a), BUILDER.sortexprvec(), $r);}
       ;

sort_expr_vec: sort_expr[a] {$$= BUILDER.sortexprvec(BUILDER.sortexprvec(), $a);}
              | sort_expr_vec[a] COMMA sort_expr[b]
                                               {$$= BUILDER.sortexprvec($a,$b);}
              ;

//}}}

// {{{5 stmts_sec

stmts_sec:  STMTDEFKEYWORD stmts
         ;

stmts: stmts stmt
     |
     ;



// rules:

stmt : head[hd] DOT           {  BUILDER.rule(@$, $hd); }
    | head[hd] IF DOT         {  BUILDER.rule(@$, $hd); }
    | head[hd] IF body[bd] DOT{  BUILDER.rule(@$, $hd, $bd); }
    | IF body[bd]  DOT        {  BUILDER.rule(@$, BUILDER.lit(false), $bd); }
    | IF DOT                  {  BUILDER.rule(@$, BUILDER.lit(false)); }
    ;

head
    : head_atom

    ;

head_atom
    : IDENTIFIER[id]                                  { $$ = BUILDER.lit(@$, String::fromRep($id),BUILDER.termvec()); }
    | IDENTIFIER[id] LPAREN ntermvec[tvv] RPAREN[r]     {$$ = BUILDER.lit(@$, String::fromRep($id), $tvv);  }
    | IDENTIFIER[id] LPAREN ntermvec[tvv] RPAREN[r]  EQ term[t] {$$ = BUILDER.lit(@$, String::fromRep($id), $tvv, $t); }
    | IDENTIFIER[id] EQ term[t]                          {$$ = BUILDER.lit(@$, String::fromRep($id), $t); }
    ;

body
    : body[bd] COMMA e_literal[lit]  {$$ = BUILDER.body($bd, $lit);}
    | e_literal[lit] {$$ = BUILDER.body(BUILDER.body(), $lit);}
    ;


constterm:
      comparable_constterm[a] {$$ = $a; }
    | IDENTIFIER[a] LPAREN consttermvec[b] RPAREN       {  $$ = BUILDER.term(@$, String::fromRep($a), $b);}
    ;

comparable_constterm:
     comparable_constterm[a] ADD comparable_constterm[b]                     {$$ = BUILDER.term(@$, BinOp::ADD, $a, $b);  }
    | comparable_constterm[a] SUB comparable_constterm[b]                    {$$ = BUILDER.term(@$, BinOp::SUB, $a, $b);  }
    | comparable_constterm[a] MUL comparable_constterm[b]                    {$$ = BUILDER.term(@$, BinOp::MUL, $a, $b);  }
    | comparable_constterm[a] SLASH comparable_constterm[b]                  {$$ = BUILDER.term(@$, BinOp::DIV, $a, $b);  }
    | comparable_constterm[a] MOD comparable_constterm[b]                    {$$ = BUILDER.term(@$, BinOp::MOD, $a, $b);  }
    | comparable_constterm[a] POW comparable_constterm[b]                    {$$ = BUILDER.term(@$, BinOp::POW, $a, $b);  }
    | SUB comparable_constterm[a] %prec UMINUS                    { $$ = BUILDER.term(@$, UnOp::NEG, $a); }
    | VBAR[l] comparable_constterm[a] VBAR                        { $$ = BUILDER.term(@$, UnOp::ABS, $a); }
    | IDENTIFIER[a]                                    { $$ = BUILDER.term(@$, Symbol::createId(String::fromRep($a))); }
    | NUMBER[a]                                        { $$ = BUILDER.term(@$, Symbol::createNum($a)); }
    | LPAREN comparable_constterm[a] RPAREN               { $$ = $a;}
    ;

// {{{2 arguments lists for functions in constant terms

consttermvec
    : constterm[a]                       { $$ = BUILDER.termvec(BUILDER.termvec(), $a);}
    | consttermvec[a] COMMA constterm[b] { $$ = BUILDER.termvec($a, $b); }
    ;


// {{{2 terms including variables

term:
      term[a] ADD term[b]                      { $$ = BUILDER.term(@$, BinOp::ADD, $a, $b);  }
    | term[a] SUB term[b]                      { $$ = BUILDER.term(@$, BinOp::SUB, $a, $b);  }
    | term[a] MUL term[b]                      { $$ = BUILDER.term(@$, BinOp::MUL, $a, $b);  }
    | term[a] SLASH term[b]                    { $$ = BUILDER.term(@$, BinOp::DIV, $a, $b);  }
    | term[a] MOD term[b]                      { $$ = BUILDER.term(@$, BinOp::MOD, $a, $b);  }
    | term[a] POW term[b]                      { $$ = BUILDER.term(@$, BinOp::POW, $a, $b); }
    | SUB term[a] %prec UMINUS                 { $$ = BUILDER.term(@$, UnOp::NEG, $a);  }
    | IDENTIFIER[a] LPAREN ntermvec[b] RPAREN  { $$ = BUILDER.term(@$, String::fromRep($a), $b); }
    | VBAR term[a] VBAR                        { $$ = BUILDER.term(@$, UnOp::ABS, $a); }
    | IDENTIFIER[a]                            { $$ = BUILDER.term(@$, Symbol::createId(String::fromRep($a)));}
    | NUMBER[a]                                { $$ = BUILDER.term(@$, Symbol::createNum($a)); }
    | VARIABLE[a]                              { $$ = BUILDER.term(@$, String::fromRep($a));  }
    | LPAREN term[a] RPAREN                    { $$ = $a; }
    ;

// {{{2 argument lists for unary operations


ntermvec
    : term[a]                   { $$ = BUILDER.termvec(BUILDER.termvec(), $a); }
    | ntermvec[a] COMMA term[b] { $$ = BUILDER.termvec($a, $b); }
    ;





cmp
    : GT     { $$ = Relation::GT;  }
    | LT     { $$ = Relation::LT;  }
    | GEQ    { $$ = Relation::GEQ; }
    | LEQ    { $$ = Relation::LEQ; }
    | EQ     { $$ = Relation::EQ;  }
    | NEQ    { $$ = Relation::NEQ; }
    ;

literal: term[l]  {  $$ = BUILDER.lit(@$,$l); }
        | term[l] cmp[rel] term[r] {$$ = BUILDER.lit(@$,$l, $rel, $r); }
    ;

e_literal: literal[l] { $$ = BUILDER.elit(@$,  $l, false);}
    |  NOT literal[l] { $$ = BUILDER.elit(@$,  $l, true); }
    ;

// pr-atoms
stmt: PR LPAREN head_atom[a] VBAR body[b] RPAREN EQ probability[p] DOT {BUILDER.pratom(@$,$a,$b,$p);}
        | PR LPAREN head_atom[a] RPAREN EQ probability[p] DOT {BUILDER.pratom(@$,$a,BUILDER.body(),$p);}
       ;

probability: NUMBER[n1] SLASH NUMBER[n2] {$$ = BUILDER.prob(@$,$n1,$n2);}
           ;

query: QUESTION literal[l] DOT {BUILDER.query(@$, $l);}

