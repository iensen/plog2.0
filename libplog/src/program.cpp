//
// Created by iensen on 9/16/16.
//


#include <plog/input/program.h>


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
    throw "not implemented yet";
}

void Program::check(Logger &log) {
    throw "not implemented yet";
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

Gringo::Input::Program Program::toGringo() {
    throw "not implemented yet";
}



