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
    #include "groundplog/program_types.h"

    class PlogParser;

    struct DefaultLocation : Gringo::Location {
        DefaultLocation() : Location("<undef>", 0, 0, "<undef>", 0, 0) { }
    };

}

%{

#include "plogparser.h"
#include "programbuilder.h"
#include <climits>

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
}

// }}}2

// declare types here:
%type <term>            constterm comparable_constterm term
%type <termvec>         ntermvec consttermvec

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
    SORT_NAME
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
    RANDOM      "random"
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

sort_def: SORT_NAME "=" sort_expr DOT
    ;

sort_expr:
            range |
            concatenation |
            functional_symbol |
            SORT_NAME |
            curly_brackets |
            sort_expr ADD sort_expr |
            sort_expr MUL sort_expr |
            sort_expr SUB sort_expr |
            LPAREN sort_expr RPAREN
      ;

range: comparable_constterm DOTS comparable_constterm
      ;

concatenation: concatenation concat_elem
       | concat_elem
       ;

concat_elem: LBRACK sort_expr RBRACK
       ;

functional_symbol: IDENTIFIER LPAREN sort_expr_list RPAREN |
        IDENTIFIER LPAREN sort_expr_list RPAREN COLON cond
       ;

cond: VARIABLE cmp VARIABLE |
       cond VBAR cond |
       cond AND cond |
       LPAREN cond RPAREN
       ;




sort_expr_list: sort_expr_list COMMA var_sort_expr
       | var_sort_expr
       ;

var_sort_expr: sort_expr |
               sort_expr LPAREN VARIABLE RPAREN


curly_brackets: LBRACE consttermvec RBRACE
        ;



// {{{4 att_sec

atts_sec: ATTDEFKEYWORD att_defs

att_defs: att_defs att_def
       |
       ;

att_def: IDENTIFIER COLON sort_name_list ARROW SORT_NAME DOT
       | IDENTIFIER COLON SORT_NAME DOT
       ;

sort_name_list: SORT_NAME
              | sort_name_list COMMA SORT_NAME
              ;

//}}}

// {{{5 stmts_sec

stmts_sec:  STMTDEFKEYWORD stmts
         ;

stmts: stmts stmt
     |
     ;



// rules:

stmt : head[hd] DOT           {  }
    | head[hd] IF DOT         {  }
    | head[hd] IF body DOT    {  }
    | IF body  DOT            {  }
    | IF DOT                  {  }
    ;

head
    : head_atom            {  }
    | random_atom   {  }
    ;

head_atom
    : IDENTIFIER[id]                                  {  }
    | IDENTIFIER[id] LPAREN ntermvec[tvv] RPAREN[r]     {  }
    | IDENTIFIER[id] LPAREN ntermvec[tvv] RPAREN[r]  EQ term { }
    | IDENTIFIER[id] EQ term                          {  }
    ;

random_atom: RANDOM LPAREN IDENTIFIER COMMA IDENTIFIER RPAREN[r] |
             RANDOM LPAREN IDENTIFIER COLON LBRACE VARIABLE COLON IDENTIFIER LPAREN VARIABLE RPAREN RBRACE RPAREN
             ;

body
    : body COMMA e_literal[lit]
    | e_literal[lit]
    ;


constterm:
      comparable_constterm[a] {$$ = $a; }
    | IDENTIFIER[a] LPAREN consttermvec[b] RPAREN       {  $$ = BUILDER.term(@$, String::fromRep($a), $b);}
    ;

comparable_constterm:
     comparable_constterm[a] ADD comparable_constterm[b]                     {$$ = BUILDER.term(@$, BinOp::ADD, $a, $b);  }
    | comparable_constterm[a] SUB comparable_constterm[b]                    {$$ = BUILDER.term(@$, BinOp::SUB, $a, $b); }
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
    | IDENTIFIER[a] LPAREN ntermvec[b] RPAREN   { $$ = BUILDER.term(@$, String::fromRep($a), $b); }
    | VBAR term[a] VBAR                           { $$ = BUILDER.term(@$, UnOp::ABS, $a); }
    | IDENTIFIER[a]                            { $$ = BUILDER.term(@$, Symbol::createId(String::fromRep($a)));}
    | NUMBER[a]                                { $$ = BUILDER.term(@$, Symbol::createNum($a)); }
    | VARIABLE[a]                              { $$ = BUILDER.term(@$, String::fromRep($a));  }
    | LPAREN term[a] RPAREN                    { $$ = $a; }
    ;

// {{{2 argument lists for unary operations


ntermvec
    : term[a]                   {  }
    | ntermvec[a] COMMA term[b] {  }
    ;





cmp
    : GT     {  }
    | LT     {  }
    | GEQ    {  }
    | LEQ    {  }
    | EQ     {  }
    | NEQ    {  }
    ;

literal: IDENTIFIER[id]                                  {  }
        | IDENTIFIER[id] LPAREN ntermvec[tvv] RPAREN[r]     {  }
        | term[l] cmp[rel] term[r] { }
    ;

e_literal: literal
    |  NOT literal
    ;

// pr-atoms
stmt: PR LPAREN head_atom VBAR body RPAREN EQ probability |
        LPAREN head_atom RPAREN EQ probability
       ;

probability: NUMBER SLASH NUMBER
           ;

query: QUESTION literal DOT

