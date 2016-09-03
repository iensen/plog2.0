
#include "plog/plogcontrol.hh"


bool PlogControl::hasSubKey(unsigned key, char const *name, unsigned* subKey) {
    //*subKey = claspConfig_.getKey(key, name);
    //return *subKey != Clasp::Cli::ClaspCliConfig::KEY_INVALID;
    throw "not implemented yet";
}
unsigned PlogControl::getSubKey(unsigned key, char const *name) {
    //unsigned ret = claspConfig_.getKey(key, name);
    //if (ret == Clasp::Cli::ClaspCliConfig::KEY_INVALID) {
    //    throw std::runtime_error("invalid key");
    //}
    //return ret;
    throw "not implemented yet";
}
unsigned PlogControl::getArrKey(unsigned key, unsigned idx) {
    //unsigned ret = claspConfig_.getArrKey(key, idx);
    //if (ret == Clasp::Cli::ClaspCliConfig::KEY_INVALID) {
    //    throw std::runtime_error("invalid key");
    //}
    //return ret;
    throw "not implemented yet";
}
void PlogControl::getKeyInfo(unsigned key, int* nSubkeys, int* arrLen, const char** help, int* nValues) const {
    //if (claspConfig_.getKeyInfo(key, nSubkeys, arrLen, help, nValues) < 0) {
    //    throw std::runtime_error("could not get key info");
    //}
    throw "not implemented yet";
}
const char* PlogControl::getSubKeyName(unsigned key, unsigned idx) const {
  //  char const *ret = claspConfig_.getSubkey(key, idx);
  //  if (!ret) {
  //      throw std::runtime_error("could not get subkey");
  //  }
  //  return ret;
    throw "not implemented yet";
}
bool PlogControl::getKeyValue(unsigned key, std::string &value) {
   // int ret = claspConfig_.getValue(key, value);
   // if (ret < -1) {
   //     throw std::runtime_error("could not get option value");
   // }
   // return ret >= 0;
    throw "not implemented yet";
}
void PlogControl::setKeyValue(unsigned key, const char *val) {
   // configUpdate_ = true;
   // if (claspConfig_.setValue(key, val) <= 0) {
   //     throw std::runtime_error("could not set option value");
   // }
    throw "not implemented yet";

}
unsigned PlogControl::getRootKey() {
    //return Clasp::Cli::ClaspCliConfig::KEY_ROOT;
    throw "not implemented yet";

}

bool PlogControl::external(Gringo::SymbolicAtomIter it) const {
    throw "not implemented yet";
}

void PlogControl::parse(const PlogControl::StringSeq &files, const PlogOptions &opts, GroundPlog::Program *out,
                        bool addStdIn) {
    throw "not implemented yet";
}

void PlogControl::main() {
    throw "not implemented yet";
}

PlogControl::PlogControl(GroundPlog::GroundPlogFacade *groundplog,
                         GroundPlog::Cli::GroundPlogCliConfig &groundplogConfig, PlogControl::PostGroundFunc pgf,
                         PlogControl::PreSolveFunc psf):
 groundplog_(groundplog)
, claspConfig_(groundplogConfig)
, pgf_(pgf)
, psf_(psf)
{
    throw "not implemented yet";
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
    throw "not implemented yet";
}

void PlogControl::load(std::string const &filename) {
    throw "not implemented yet";
}

void PlogControl::add(std::string const &name, Gringo::FWStringVec const &params, std::string const &part) {
    throw "not implemented yet";
}

void PlogControl::ground(Gringo::Control::GroundVec const &vec, Gringo::Context *ctx) {
    throw "not implemented yet";
}

Gringo::SymbolicAtoms &PlogControl::getDomain() {
    throw "not implemented yet";
}

bool PlogControl::valid(Gringo::SymbolicAtomIter it) const {
    throw "not implemented yet";
}

Gringo::SymbolicAtomIter PlogControl::next(Gringo::SymbolicAtomIter it) {
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
    throw "not implemented yet";
}

void PlogControl::parse() {
    throw "not implemented yet";
}

PlogControl::~PlogControl() {
    throw "not implemented yet";
}

bool PlogControl::fact(Gringo::SymbolicAtomIter it) const {
    throw "not implemented yet";
}
