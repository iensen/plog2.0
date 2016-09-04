//
// Created by iensen on 9/2/16.
//

#include <groundplog/program_builder.h>

namespace GroundPlog {
    ProgramBuilder::ProgramBuilder():ctx_(0), frozen_(true) {
    }

    ProgramBuilder::~ProgramBuilder() {
    }

    bool ProgramBuilder::ok() const {
        throw "not implemented yet";
    }

    bool ProgramBuilder::startProgram(SharedContext &ctx) {
        ctx_    = &ctx;
        return ctx_->ok() && doStartProgram();
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