//
// Created by iensen on 8/19/16.
//

#include <groundplog/groundplog_facade.h>
#include <groundplog/possible_worlds.h>
#include <groundplog/solve_algorithms.h>

#include<clasp/util/timer.h>
#include <clingo.hh>
#include <plog/plogcontrol.hh>


GroundPlog::GroundPlogFacade::GroundPlogFacade():config_(0) {

}


GroundPlog::GroundPlogFacade::~GroundPlogFacade() {

}

GroundPlog::Program &GroundPlog::GroundPlogFacade::start(GroundPlog::GroundPlogConfig &config) {
    init(config);
    // this are all memory leaks?
    Program* p = new Program();
    p->setOptions(config.prep);
    return *p;
}


GroundPlog::GroundPlogFacade::Result
GroundPlog::GroundPlogFacade::solve(Clingo::Control * cCtl, Plog::Program* prg, SolvingMode solvingMode) {
    std::unique_ptr<SolveAlgorithm>  algo(config_->solve.createSolveObject(solvingMode));
    return algo->run(static_cast<GroundPlog::Program *>(this->program()), prg, cCtl);
}

void
GroundPlog::GroundPlogFacade::computePossibleWorlds(Clingo::Control *ctl, Plog::Program *inputProgram, Format format_) {
   PossibleWorldsComputer computer(inputProgram, ctl, format_);
   computer.run();
}

void GroundPlog::GroundPlogFacade::init(GroundPlog::GroundPlogConfig &cfg) {
    //  ctx.setConfiguration(0, Ownership_t::Retain); // force reload of configuration once done ?? not needed
    config_ = &cfg;
    builder_= new Program();
    builder_->setOptions(cfg.prep);
}




