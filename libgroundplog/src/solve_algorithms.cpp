//
// Created by iensen on 9/3/16.
//


#include <groundplog/solve_algorithms.h>

GroundPlog::ExactDCOSolve::ExactDCOSolve():solve_(0) {

}

bool GroundPlog::ExactDCOSolve::interrupted() const {
    throw "not implemented yet";
}

void GroundPlog::ExactDCOSolve::resetSolve() {
    throw "not implemented yet";
}

void GroundPlog::ExactDCOSolve::enableInterrupts() {
    throw "not implemented yet";
}

bool
GroundPlog::ExactDCOSolve::doSolve(GroundPlog::SharedContext &ctx, const std::vector<GroundPlog::Literal> &assume) {
    throw "not implemented yet";
}

bool GroundPlog::ExactDCOSolve::doInterrupt() {
    throw "not implemented yet";
}

void GroundPlog::ExactDCOSolve::doStart(GroundPlog::SharedContext &ctx) {
    SolveAlgorithm::doStart(ctx);
}

int GroundPlog::ExactDCOSolve::doNext(int last) {
    throw "not implemented yet";
}

void GroundPlog::ExactDCOSolve::doStop() {
    SolveAlgorithm::doStop();
}

GroundPlog::SolveAlgorithm::SolveAlgorithm():ctx_(0), time_(0.0) {

}

GroundPlog::SolveAlgorithm::~SolveAlgorithm() {

}

void GroundPlog::SolveAlgorithm::doStart(GroundPlog::SharedContext &ctx) {
    throw "not implemented yet";
}

void GroundPlog::SolveAlgorithm::doStop() {
    throw "not implemented yet";
}

GroundPlog::BasicSolve::BasicSolve(GroundPlog::Solver &s) {
    throw "not implemented yet";
}

GroundPlog::BasicSolve::~BasicSolve() {
    throw "not implemented yet";
}
