//
// Created by iensen on 9/16/16.
//


#include <plog/input/program.h>


Program::Program() {

}

Program::Program(Program &&x) {
    throw "not implemented yet";
}


void Program::add(UStm &&stm) {
    throw "not implemented yet";
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

Gringo::Ground::Program Program::toGround(Logger &log) {
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

void Program::add(USortDef sDef) {
    throw "not implemented yet";
}

void Program::add(UAttDecl sDef) {
    throw "not implemented yet";
}


