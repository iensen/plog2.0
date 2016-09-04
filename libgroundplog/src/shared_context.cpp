//
// Created by iensen on 8/19/16.
//

#include <groundplog/shared_context.h>
#include <groundplog/groundplog_facade.h>
#include <groundplog/solver.h>
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
        Solver* s    = new Solver(this);
        if(solver_ != 0) {
            throw std::logic_error("there cannot be more then one solver!");
        }
        solver_=s;
        return *s;
    }

    void SharedContext::setConfiguration(Configuration *c, Ownership_t::Type ownership) {
        bool own = ownership == Ownership_t::Acquire;
        if (c == 0) { c = &config_def_s; own = false; }
        if (config_.get() != c) {
            config_ = c;
            if (!own) config_.release();
            config_->prepare(*this);
            solver_->resetConfig();
        }
        else if (own != config_.is_owner()) {
            if (own) config_.acquire();
            else     config_.release();
        }

    }

    bool SharedContext::ok() const {
        return solver_->decisionLevel() || !solver_->hasConflict();
    }
}
