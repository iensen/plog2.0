//
// Created by KR_Lab on 11/26/16.
//

#ifndef PLOG_UTILS_H
#define PLOG_UTILS_H

#include<clingo.hh>
#include <gringo/term.hh>
#include<utility>
#include <plog/sortexpression.h>
#include "types.h"
#include<plog/input/attributedeclaration.h>


using Gringo::UTermVec ;
using Gringo::UTerm;
using Gringo::String;




// manipulations with gringo and clingo terms:
Clingo::AST::Term termToClingoTerm(const UTerm & term);
UTermVec clone(const UTermVec &vec);
std::string term_to_string (const Clingo::AST::Term &term);
Gringo::String getAttrName(const UTerm &term);
std::vector<Clingo::AST::Term> getAttrArgs(const UTerm &term);

// manipulations with gringo strings:
String  concat(char prefix, String s);

//default location for newly created clingo objects (statements, terms, etc):
const Clingo::Location defaultLoc = {"<test>", "<test>", 1, 1, 1, 1};

// int and string manipulations:
std::string int_to_str(int n);
int str_to_int(std::string str);

// find sorts for attribute
std::pair<const USortExprVec &, const USortExpr &> getSorts(String attrName, const UAttDeclVec & attdecls);
const USortExpr & getResultSort(String attrName, const UAttDeclVec & attdecls);
const USortExprVec & getArgSorts(String attrName, const UAttDeclVec & attdecls);



#endif