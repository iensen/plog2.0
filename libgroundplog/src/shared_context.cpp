//
// Created by iensen on 8/19/16.
//

#include <groundplog/shared_context.h>
#include <groundplog/groundplog_facade.h>

namespace GroundPlog {
    GroundPlog::EventHandler::EventHandler() {

    }

    GroundPlog::EventHandler::~EventHandler() {

    }

    static BasicSatConfig config_def_s;

    GroundPlog::SharedContext::SharedContext()
            : progress_(0) { // minimize statements
        config_ = &config_def_s;
        config_.release();
        pushSolver();
    }

    GroundPlog::SharedContext::~SharedContext() {
        throw "not implemented yet";
    }

    Solver &SharedContext::pushSolver() {
        throw "not implemented yet";
    }
}
