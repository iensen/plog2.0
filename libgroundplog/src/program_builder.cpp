//
// Created by iensen on 9/2/16.
//

#include <groundplog/program_builder.h>

namespace GroundPlog {
    ProgramBuilder::ProgramBuilder(): frozen_(true) {
    }

    ProgramBuilder::~ProgramBuilder() {
    }

    bool ProgramBuilder::ok() const {
        return true;
    }

    bool ProgramBuilder::startProgram() {
        return doStartProgram();
    }

    bool ProgramBuilder::parseProgram(std::istream &prg) {
        throw "not implemented yet";
    }

    bool ProgramBuilder::updateProgram() {
        throw "not implemented yet";
    }

    bool ProgramBuilder::endProgram() {
        throw "not implemented yet";
    }

    void ProgramBuilder::getAssumptions(std::vector<Literal> &out) const {
        throw "not implemented yet";
    }

    ProgramBuilder &ProgramBuilder::operator=(ProgramBuilder &) {
        throw "not implemented yet";
    }


}