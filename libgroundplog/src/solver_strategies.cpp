//
// Created by iensen on 8/19/16.
//

#include <groundplog/solver_strategies.h>


GroundPlog::Configuration *GroundPlog::Configuration::config(const char *n) {
	throw "not implemented yet";
}


GroundPlog::BasicSatConfig::BasicSatConfig() {
	opts_ = SolverParams();
	heu_ = 0;
}
void GroundPlog::BasicSatConfig::reset() {
    throw "not implemented yet";
}

void GroundPlog::BasicSatConfig::resize(uint32 numSolver, uint32 numSearch) {
    throw "not implemented yet";
}

void GroundPlog::BasicSatConfig::setHeuristicCreator(GroundPlog::BasicSatConfig::HeuristicCreator hc) {
    throw "not implemented yet";
}

void GroundPlog::BasicSatConfig::prepare(GroundPlog::SharedContext &) {
   opts_.prepare();
     // warnings go here
}


GroundPlog::DecisionHeuristic *GroundPlog::BasicSatConfig::heuristic(uint32 i) const {
    throw "not implemented yet";
}

GroundPlog::Configuration::SolverOpts &GroundPlog::BasicSatConfig::addSolver(uint32 i) {
    throw "not implemented yet";
}

GroundPlog::Configuration::~Configuration() {
}

uint32 GroundPlog::SolverParams::prepare() {
    SolverStrategies::prepare();
    return 0;
}

void GroundPlog::SolverStrategies::prepare() {

}
