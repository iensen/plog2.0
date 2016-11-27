//
// Created by KR_Lab on 11/26/16.
//

#ifndef PLOG_UTILS_H
#define PLOG_UTILS_H

#include<clingo.hh>
#include <gringo/term.hh>
using Gringo::UTermVec ;
using Gringo::UTerm;
using Gringo::String;



// manipulations with gringo and clingo terms:
Clingo::AST::Term termToClingoTerm(const UTerm & term);
UTermVec clone(const UTermVec &vec);

// manipulations with gringo strings:
String  concat(char prefix, String s);

//default location for newly created clingo objects (statements, terms, etc):
const Clingo::Location defaultLoc = {"<test>", "<test>", 1, 1, 1, 1};


#endif