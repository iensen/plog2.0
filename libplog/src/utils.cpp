//
// Created by KR_Lab on 11/26/16.
//
#include<plog/input/utils.h>

using Gringo::FunctionTerm;
using Gringo::String;
using Gringo::VarTerm;
using Gringo::ValTerm;
using Gringo::UTermVec;
using Gringo::Term;

Clingo::AST::Term termToClingoTerm(const UTerm & term) {

    std::stringstream stream;
    term.get()->print(stream);


    // if it is a function term:
    FunctionTerm * fterm = dynamic_cast<FunctionTerm*>(term.get());

    if (fterm) {
        String name = fterm->name;
        UTermVec fargs = clone(fterm->args);
        std::vector<Clingo::AST::Term> args;
        for(const UTerm &t: fargs) {
            args.push_back(termToClingoTerm(t));
        }
        auto f_ = Clingo::AST::Function{name.c_str(), args};
        return {defaultLoc,f_};
    }

    // if term is a variable

    VarTerm * varT = dynamic_cast<VarTerm*>(term.get());

    if (varT) {
        String name = varT->name;
        //printf("%s\n",varT->name.c_str());
        auto f_ = Clingo::AST::Variable{name.c_str()};
        return {defaultLoc,f_};
    }

    // if term is a valterm:

    ValTerm * valT = dynamic_cast<ValTerm*>(term.get());

    if (valT) {
        std::stringstream ss;
        valT->print(ss);
        Clingo::Symbol sym = Clingo::parse_term(stream.str().c_str());
        return {defaultLoc,sym};
    }

    // bin op and un op terms go here

    throw std::logic_error("cannot convert a term");

}


UTermVec clone(const UTermVec &vec) {
    UTermVec  res;
    for(const UTerm &term:vec) {
        std::unique_ptr<Term> ut(term->clone());
        res.emplace_back(std::move(ut));
    }
    return res;
}

// not sure if this leaks.
// does String own the memory?
String concat(char prefix, String s) {
    char* raw = new char [2 + s.length()];
    raw[0] = prefix;
    for(int i=0;i<s.length();i++) {
        raw[i+1] = s.c_str()[i];
    }
    raw[s.length()+1] = '\0';
    return String(raw);
}
