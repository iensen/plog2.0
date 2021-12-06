
#include <plog/plogoutput.h>
#include <clingo/clingocontrol.hh>
#include "plog/grprogramobs.h"
#include "plog/plogcontrol.hh"
#include "plog/checker.h"

class GroundPlogBackend;

bool PlogControl::hasSubKey(unsigned key, char const *name) const {
    //*subKey = groundPlogConfig_.getKey(key, name);
    //return *subKey != Clasp::Cli::ClaspCliConfig::KEY_INVALID;
    throw "not implemented yet";
}
unsigned PlogControl::getSubKey(unsigned key, char const *name) const{
    //unsigned ret = groundPlogConfig_.getKey(key, name);
    //if (ret == Clasp::Cli::ClaspCliConfig::KEY_INVALID) {
    //    throw std::runtime_error("invalid key");
    //}
    //return ret;
    throw "not implemented yet";
}
unsigned PlogControl::getArrKey(unsigned key, unsigned idx) const{
    //unsigned ret = groundPlogConfig_.getArrKey(key, idx);
    //if (ret == Clasp::Cli::ClaspCliConfig::KEY_INVALID) {
    //    throw std::runtime_error("invalid key");
    //}
    //return ret;
    throw "not implemented yet";
}
void PlogControl::getKeyInfo(unsigned key, int* nSubkeys, int* arrLen, const char** help, int* nValues) const {
    //if (groundPlogConfig_.getKeyInfo(key, nSubkeys, arrLen, help, nValues) < 0) {
    //    throw std::runtime_error("could not get key info");
    //}
    throw "not implemented yet";
}
const char* PlogControl::getSubKeyName(unsigned key, unsigned idx) const {
  //  char const *ret = groundPlogConfig_.getSubkey(key, idx);
  //  if (!ret) {
  //      throw std::runtime_error("could not get subkey");
  //  }
  //  return ret;
    throw "not implemented yet";
}
bool PlogControl::getKeyValue(unsigned key, std::string &value) const{
   // int ret = groundPlogConfig_.getValue(key, value);
   // if (ret < -1) {
   //     throw std::runtime_error("could not get option value");
   // }
   // return ret >= 0;
    throw "not implemented yet";
}
void PlogControl::setKeyValue(unsigned key, const char *val) {
   // configUpdate_ = true;
   // if (groundPlogConfig_.setValue(key, val) <= 0) {
   //     throw std::runtime_error("could not set option value");
   // }
    throw "not implemented yet";

}
unsigned PlogControl::getRootKey() const{
    //return Clasp::Cli::ClaspCliConfig::KEY_ROOT;
    throw "not implemented yet";

}

bool PlogControl::external(Gringo::SymbolicAtomIter it) const {
    throw "not implemented yet";
}

void PlogControl::parse(const PlogControl::StringVec &files, const PlogOptions &opts) {
    using namespace Gringo;
    // make empty theory data

    std::unique_ptr<Potassco::TheoryData> data = gringo_make_unique<Potassco::TheoryData>();
    Output::OutputPredicates outPreds;
    for (auto &x : opts.foobar) {
        outPreds.emplace_back(Location("<cmd>",1,1,"<cmd>", 1,1), x, false);
    }
    out_ = gringo_make_unique<GroundPlogBackend>(*this);
    pb_ = gringo_make_unique<NonGroundProgramBuilder>( prg_, defs_);
    parser_ = Gringo::gringo_make_unique<PlogParser>(*pb_);
    for (auto &x : opts.defines) {
        parser_->parseDefine(x, logger_);
    }
    for (auto x : files) {
        parser_->pushFile(std::move(x), logger_);
    }
    parse();

}

void PlogControl::computeQuery(){
    groundPlogConfig_.releaseOptions();
    ground();

    // solve (this is needed to make sure that the rules are passed from gringo to clasp:
    clingoControl.solve();

    auto res = groundplog_->solve(&clingoControl, &prg_, solvingMode);
    if(solvingMode == SolvingMode::query_dco && !res.success) {
        fprintf(stderr, "ERROR: the program is not dynamically causally ordered\n");
    } else {
        if(!res.success) {
            fprintf(stderr, "ERROR: the input program is not coherent, because the sum of the measures of its possible worlds is 0.\n");
        } else {
            printf("answer: %f\n", res.prob);
        }
    }
}

void PlogControl::computePossibleWorlds(Format format_){
    groundPlogConfig_.releaseOptions();
    ground();
    groundplog_->computePossibleWorlds(&clingoControl, &prg_, format_);

}


const unsigned messageLimit = 20;
PlogControl::PlogControl(GroundPlog::GroundPlogFacade *groundplog,
                         GroundPlog::Cli::GroundPlogCliConfig &groundplogConfig,
                         PlogControl::PostGroundFunc pgf,
                         PlogControl::PreSolveFunc psf,
                         Gringo::Logger::Printer printer,
                         SolvingMode mode):
 groundplog_(groundplog)
, groundPlogConfig_(groundplogConfig)
, pgf_(pgf)
, psf_(psf)
,logger_(printer),
 clingoControl{{"0","--opt-mode=optN","--project"}, [](Clingo::WarningCode, char const *message) {}, messageLimit},
 solvingMode(mode)
{

}

void PlogControl::onFinish(GroundPlog::GroundPlogFacade::Result ret) {
    throw "not implemented yet";
}

Potassco::Atom_t PlogControl::addProgramAtom() {
    throw "not implemented yet";
}

void PlogControl::interrupt() {
    throw "not implemented yet";
}

Gringo::Symbol PlogControl::getConst(std::string const &name) {
    throw "not implemented yet";
}

std::string PlogControl::str() {
    throw "not implemented yet";
}

Gringo::SolveResult PlogControl::solve() {

}

void PlogControl::load(std::string const &filename) {
    throw "not implemented yet";
}

void PlogControl::add(std::string const &name,  Gringo::StringVec const &, std::string const &part) {
    throw "not implemented yet";
}

void PlogControl::ground() {
    if (parsed) {
        // replace constants with their values, ...
        prg_.rewrite(defs_, logger_);
        // check semantic errors:
        Plog::Checker c(prg_,logger_);
        c.check();

        if (logger_.hasError()) {
            throw std::runtime_error("grounding stopped because of errors");
        }
        parsed = false;
    }
    prg_.loadToControl(clingoControl, solvingMode);
    pb = std::make_unique<PlogGroundProgramBuilder>(*out_, solvingMode == SolvingMode::query_dco);
    clingoControl.register_observer(*pb);
    clingoControl.ground({{"base", {}}});
}

Gringo::SymbolicAtoms &PlogControl::getDomain() {
    throw "not implemented yet";
}

bool PlogControl::valid(Gringo::SymbolicAtomIter it) const {
    throw "not implemented yet";
}

Potassco::Lit_t PlogControl::literal(Gringo::SymbolicAtomIter it) const {
    throw "not implemented yet";
}

Gringo::Symbol PlogControl::atom(Gringo::SymbolicAtomIter it) const {
    throw "not implemented yet";
}

std::vector<Gringo::Sig> PlogControl::signatures() const {
    throw "not implemented yet";
}

size_t PlogControl::length() const {
    throw "not implemented yet";
}

Gringo::SymbolicAtomIter PlogControl::lookup(Gringo::Symbol atom) const {
    throw "not implemented yet";
}

bool PlogControl::eq(Gringo::SymbolicAtomIter it, Gringo::SymbolicAtomIter jt) const {
    throw "not implemented yet";
}

Gringo::SymbolicAtomIter PlogControl::end() const {
    throw "not implemented yet";
}

Gringo::SymbolicAtomIter PlogControl::begin() const {
    throw "not implemented yet";
}

Gringo::SymbolicAtomIter PlogControl::begin(Gringo::Sig sig) const {
    throw "not implemented yet";
}

bool PlogControl::update() {
    configUpdate_ = false;
    if (!grounded) {
        grounded = true;
    }
    return true;
}

void PlogControl::parse() {
    if (!parser_->empty()) {
        parser_->parse(logger_);
        defs_.init(logger_);
        parsed = true;
    }
    if (logger_.hasError()) {
        throw std::runtime_error("parsing failed");
    }
}

PlogControl::~PlogControl() {
}

bool PlogControl::fact(Gringo::SymbolicAtomIter it) const {
    throw "not implemented yet";
}

Gringo::SymbolicAtomIter PlogControl::next(Gringo::SymbolicAtomIter it) const {
    throw "not implemented yet";
}
