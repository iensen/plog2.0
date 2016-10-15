//
// Created by iensen on 8/19/16.
//

#include <groundplog/groundplog_facade.h>
#include <groundplog/solve_algorithms.h>
#include <groundplog/solver.h>
#include<clasp/util/timer.h>



GroundPlog::GroundPlogFacade::GroundPlogFacade():config_(0) {
    sum.init(*this);
}




struct GroundPlog::GroundPlogFacade::SolveStrategy {
public:
    enum { SIGCANCEL = 9 };
    enum State { state_start = 0, state_running = 1, state_result = 2, state_done = 6 };
    SolveStrategy()         { state = signal = 0;  facade = 0; algo = 0; handler = 0; }
    virtual ~SolveStrategy(){}
    bool running() const    { return (state & state_running) != 0; }
    bool hasResult()const   { return (state & state_result)  != 0; }
    bool interrupt(int sig) {
        if (!running()) { return false; }
        if (!signal)    { signal = sig; }
        return cancel(sig);
    }
    void solve(GroundPlogFacade& f,  SolveAlgorithm* algo, EventHandler* h) {
        this->facade  = &f;
        this->algo    = algo;
        this->handler = h;
        this->state   = 0;
        this->signal  = 0;
        preSolve();
        this->state = state_running;
        facade->interrupt(0); // handle pending interrupts
        doSolve();
    }
    void detach(State end) {
        facade->stop();
        if (handler) { handler->onEvent(Ready(facade->summary())); }
        state = end;
    }
    bool attach() {
        using Clasp::RealTime;
        CLASP_FAIL_IF(!running(), "invalid call to attach!");
        if (!signal && !facade->ctx.solver()->hasConflict()) {
            facade->sum.solveTime = facade->sum.unsatTime = RealTime::getTime();
            return true;
        }
        //facade->ctx.report(Event::subsystem_solve); // no report
        return false;
    }
    bool startGen() {
        if (!attach()) {
            detach(state_done);
            return false;
        }
        algo->start(facade->ctx, facade);
        return true;
    }
    void stopGen() {
        if (running()) {
            algo->stop();
            detach(state_done);
        }
    }
    virtual void release()  {}
    virtual bool cancel(int){ return algo->interrupt(); }
    GroundPlogFacade*    facade;
    SolveAlgorithm* algo;
    EventHandler*   handler;
    typedef Clasp::Atomic_t<int>::type SafeIntType;
    SafeIntType     state;
    SafeIntType     signal;

protected:
    void runAlgo(State end);
    virtual void preSolve() {}
    virtual void doSolve() = 0;
};





struct GroundPlog::GroundPlogFacade::SolveData {

    typedef SingleOwnerPtr<SolveAlgorithm> AlgoPtr;
    typedef Clasp::Atomic_t<int>::type     SafeIntType;
    SolveData() : algo(0), active(0), prepared(false), interruptible(false) { qSig = 0; }
    ~SolveData() { reset(); }
    void init(SolveAlgorithm* algo) {
        this->algo = algo;
        if (interruptible) {
            this->algo->enableInterrupts();
        }
    }

    void reset() {
        if (active)    { active->interrupt(SolveStrategy::SIGCANCEL); active->release(); active = 0; }
        if (algo.get()){ algo->resetSolve(); }
        prepared = false;
    }
    bool update(const Solver& s, double result ) { return !active->handler || active->handler->onResult(s, result); }
    bool interrupt(int sig) {
        if (solving()) { return active->interrupt(sig); }
        if (!qSig && sig != SolveStrategy::SIGCANCEL) { qSig = sig; }
        return false;
    }
    bool                      solving()   const  { return active && active->running();   }
    AlgoPtr        algo;
    SolveStrategy* active;
    SafeIntType    qSig;
    bool           prepared;
    bool           interruptible;
};

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

void GroundPlog::GroundPlogFacade::prepare() {
    throw "not implemented yet";
}

GroundPlog::GroundPlogFacade::Result
GroundPlog::GroundPlogFacade::solve(GroundPlog::EventHandler *eh, const std::vector<GroundPlog::Lit_t> &a) {
    throw "not implemented yet";
}

void GroundPlog::GroundPlogFacade::init(GroundPlog::GroundPlogConfig &cfg) {
    //  ctx.setConfiguration(0, Ownership_t::Retain); // force reload of configuration once done ?? not needed
    config_ = &cfg;
    ctx.setConfiguration(&cfg, Ownership_t::Retain); // prepare and apply config
    Program* p = static_cast<Program*>(program());
    p->setOptions(cfg.prep);
    if (!solve_.get()) { solve_ = new SolveData(); }
    SolveData::AlgoPtr a(cfg.solve.createSolveObject());
    solve_->init(a.release());

}

void GroundPlog::GroundPlogFacade::initBuilder(GroundPlog::ProgramBuilder *in) {
    builder_ = in;
    assume_.clear();
    builder_->startProgram(ctx);
}

GroundPlog::ProgramBuilder &GroundPlog::GroundPlogFacade::update(bool updateConfig) {
    throw "not implemented yet";
}

void GroundPlog::GroundPlogFacade::Summary::init(GroundPlog::GroundPlogFacade &f) {
    std::memset(this, 0, sizeof(Summary)); facade = &f;
}
