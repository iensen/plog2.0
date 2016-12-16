//
// Created by iensen on 8/19/16.
//

#include <groundplog/groundplog_facade.h>
#include <groundplog/solve_algorithms.h>
#include <groundplog/solver.h>
#include<clasp/util/timer.h>
#include <clingo.hh>


GroundPlog::GroundPlogFacade::GroundPlogFacade():config_(0) {
    sum.init(*this);
}




GroundPlog::GroundPlogFacade::~GroundPlogFacade() {
    throw "not implemented yet";
}

GroundPlog::Program &GroundPlog::GroundPlogFacade::start(GroundPlog::GroundPlogConfig &config) {
    init(config);
    Program* p = new Program();
    initBuilder(p);
    p->setOptions(config.prep);
    return *p;
}

GroundPlog::ProgramBuilder &
GroundPlog::GroundPlogFacade::start(GroundPlog::GroundPlogConfig &config, std::istream &stream) {
    throw "not implemented yet";
}

bool GroundPlog::GroundPlogFacade::read() {
    throw "not implemented yet";
}


GroundPlog::GroundPlogFacade::Result
GroundPlog::GroundPlogFacade::solve(Clingo::Control *clctl) {
    SolveAlgorithm*  algo = config_->solve.createSolveObject();
    return algo->run(static_cast<GroundPlog::Program *>(this->program()), clctl);




    /*
    struct SyncSolve : public SolveStrategy {
        SyncSolve(SolveData& s) : x(&s) { x->active = this; }
        ~SyncSolve()                    { x->active = 0;    }
        virtual void doSolve() { runAlgo(state_done); }
        SolveData* x;
    } syncSolve(*solve_);
    syncSolve.solve(*this,  solve_->algo.get(), eh);
    return result();
     */
}

void GroundPlog::GroundPlogFacade::init(GroundPlog::GroundPlogConfig &cfg) {
    //  ctx.setConfiguration(0, Ownership_t::Retain); // force reload of configuration once done ?? not needed
    config_ = &cfg;
    ctx.setConfiguration(&cfg, Ownership_t::Retain); // prepare and apply config
    Program* p = static_cast<Program*>(program());
    p->setOptions(cfg.prep);
}

void GroundPlog::GroundPlogFacade::initBuilder(GroundPlog::ProgramBuilder *in) {
    builder_ = in;
    assume_.clear();
    builder_->startProgram(ctx);
}



void GroundPlog::GroundPlogFacade::Summary::init(GroundPlog::GroundPlogFacade &f) {
    std::memset(this, 0, sizeof(Summary)); facade = &f;
}
