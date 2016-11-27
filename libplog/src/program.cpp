//
// Created by iensen on 9/16/16.
//


#include <plog/input/program.h>
#include <plog/ploggrammar.tab.hh>


Program::Program() {

}

Program::Program(Program &&x) {
    throw "not implemented yet";
}

void Program::add(USortDef sDef) {
    sortdefs_.emplace_back(std::move(sDef));
}

void Program::add(UAttDecl sDef) {
    attdecls_.emplace_back(std::move(sDef));
}


void Program::add(UStm &&stm) {
    stms_.emplace_back(std::move(stm));
}

void Program::rewrite(Defines &defs, Logger &log) {
    printf("REWRITING IS NOT IMPLEMENTED YET\n");
}

void Program::check(Logger &log) {
    printf("CHECKING IS NOT IMPLEMENTED YET\n");
}

void Program::print(std::ostream &out) const {
    throw "not implemented yet";
}

Program::~Program() {
    throw "not implemented yet";
}

void Program::rewriteDots() {
    throw "not implemented yet";
}

void Program::rewriteArithmetics() {
    throw "not implemented yet";
}

void Program::unpool() {
    throw "not implemented yet";
}


void Program::loadToControl(Clingo::Control &ctl) {
    auto b = ctl.builder();
    b.begin();
    Clingo::Location loc("<test>", "<test>", 1, 1, 1, 1);
    b.add({loc, Clingo::AST::Program{"base", {}}});
    // add program rules:
    for(const UStm &stm: stms_)
        //       if (stm->getType() == StatementType::QUERY || stm->getType() == StatementType::PR_ATOM)
        b.add(stm->toGringoAST(attdecls_, sortdefs_));

    //add sorts:

    //add axioms:
    b.end();
}



