#include <gringo/output/output.hh>
#include <gringo/input/program.hh>
#include <plog/programbuilder.h>
#include <gringo/input/nongroundparser.hh>
#include <gringo/input/groundtermparser.hh>
#include <clingo/control.hh>
#include <clingo.hh>
#include <gringo/logger.hh>
#include <clingo/scripts.hh>
#include <groundplog/program.h>
#include <groundplog/groundplog_facade.h>
#include <groundplog/cli/groundplog_options.h>
#include <groundplog/solve_algorithms.h>
#include <potassco/application.h>
#include <potassco/string_convert.h>
#include <mutex>
#include<plog/plog.h>
#include <plog/input/program.h>
#include "plogparser.h"
#include "plogoutput.h"
#include "grprogramobs.h"
#include<plog/programbuilder.h>
#include<plog/term.h>
#include<plog/plogoutput.h>
#include <clingo/clingocontrol.hh>

#ifndef PLOGCONTROL_H
#define PLOGCONTROL_H



struct plog_control {
    using FinishHandler = std::function<void (GroundPlog::SolveResult)>;
    using Assumptions = std::vector<std::pair<Gringo::Symbol, bool>>;
    using GroundVec = std::vector<std::pair<Gringo::String, Gringo::SymVec>>;
    using NewControlFunc = Gringo::Control* (*)(int, char const **);
    using FreeControlFunc = void (*)(Gringo::Control *);
    virtual Gringo::SymbolicAtoms &getDomain() = 0;
    virtual void ground() = 0;
    virtual Gringo::SolveResult solve() = 0;
    virtual void interrupt() = 0;
    virtual void add(std::string const &name,  Gringo::StringVec const &, std::string const &part) = 0;
    virtual void load(std::string const &filename) = 0;
    virtual Gringo::Symbol getConst(std::string const &name) = 0;
    virtual Potassco::Atom_t addProgramAtom() = 0;
    virtual void beginAdd() = 0;
    virtual void add(plog_ast_statement_t const &stm) = 0;
    virtual void endAdd() = 0;
    virtual ~plog_control() noexcept = default;
};



struct PlogOptions {
    using Foobar = std::vector<Gringo::Sig>;
    std::vector<std::string>      defines;
    Gringo::Output::OutputOptions outputOptions;
    Gringo::Output::OutputFormat  outputFormat          = Gringo::Output::OutputFormat::INTERMEDIATE;
    bool                          verbose               = false;
    bool                          wNoOperationUndefined = false;
    bool                          wNoAtomUndef          = false;
    bool                          wNoFileIncluded       = false;
    bool                          wNoVariableUnbounded  = false;
    bool                          wNoGlobalVariable     = false;
    bool                          wNoOther              = false;
    bool                          rewriteMinimize       = false;
    bool                          keepFacts             = false;
    Foobar                        foobar;
};

// {{{1 declaration of DefaultGringoModule

class GroundPlogBackend;
class PlogGroundProgramBuilder;

class PlogControl : public plog_control, private Gringo::ConfigProxy, private Gringo::SymbolicAtoms {
public:
    using StringVec        = std::vector<std::string>;
    using ExternalVec      = std::vector<std::pair<Gringo::Symbol, Potassco::Value_t>>;
    using PostGroundFunc   = std::function<bool (GroundPlog::Program &)>;
    using PreSolveFunc     = std::function<bool (GroundPlog::GroundPlogFacade &)>;
    enum class ConfigUpdate { KEEP, REPLACE };

    PlogControl(GroundPlog::GroundPlogFacade *groundplog,
                GroundPlog::Cli::GroundPlogCliConfig &groundplogConfig, PostGroundFunc pgf, PreSolveFunc psf,Gringo::Logger::Printer printer,
                SolvingMode mode);
    ~PlogControl() noexcept override;
    void parse();
    void parse(const StringVec&  files, const PlogOptions& opts);
    void computeQuery();
    void computePossibleWorlds(Format format);

    void onFinish(GroundPlog::GroundPlogFacade::Result ret);
    bool update();

    virtual void postGround(GroundPlog::Program& prg) { throw "not implemented"; }
    virtual void prePrepare(GroundPlog::GroundPlogFacade& ) { throw "not implemented"; }
    virtual void preSolve(GroundPlog::GroundPlogFacade& groundplog) { throw "not implemented";  }
    virtual void postSolve(GroundPlog::GroundPlogFacade& ) { }

    // {{{2 ConfigProxy interface

    bool hasSubKey(unsigned key, char const *name) const override;
    unsigned getSubKey(unsigned key, char const *name) const override;
    unsigned getArrKey(unsigned key, unsigned idx) const override;
    void getKeyInfo(unsigned key, int* nSubkeys = 0, int* arrLen = 0, const char** help = 0, int* nValues = 0) const override;
    const char* getSubKeyName(unsigned key, unsigned idx) const override;
    bool getKeyValue(unsigned key, std::string &value) const override;
    void setKeyValue(unsigned key, const char *val) override;
    unsigned getRootKey() const override;

    // {{{2 SymbolicAtoms interface

    Gringo::SymbolicAtomIter begin(Gringo::Sig sig) const override;
    Gringo::SymbolicAtomIter begin() const override;
    Gringo::SymbolicAtomIter end() const override;
    Gringo::SymbolicAtomIter next(Gringo::SymbolicAtomIter it) const override;
    bool eq(Gringo::SymbolicAtomIter it, Gringo::SymbolicAtomIter jt) const override;
    Gringo::SymbolicAtomIter lookup(Gringo::Symbol atom) const override;
    size_t length() const override;
    std::vector<Gringo::Sig> signatures() const override;
    Gringo::Symbol atom(Gringo::SymbolicAtomIter it) const override;
    Potassco::Lit_t literal(Gringo::SymbolicAtomIter it) const override;
    bool fact(Gringo::SymbolicAtomIter it) const override;
    bool valid(Gringo::SymbolicAtomIter it) const override;
    bool external(Gringo::SymbolicAtomIter it) const override;

    // {{{2 Control interface

    Gringo::SymbolicAtoms &getDomain() override;
    void ground() override ;
    void add(std::string const &name,  Gringo::StringVec const &params, std::string const &part) override;
    void load(std::string const &filename) override;
    Gringo::SolveResult solve() override;
    std::string str();
    Gringo::Symbol getConst(std::string const &name) override;
    void interrupt() override;
    Potassco::Atom_t addProgramAtom() override;
    void beginAdd() override { parse(); }
    void add(plog_ast_statement_t const &stm) override { throw "not implemented"; }
    void endAdd() override { throw "not implemented"; }

    // }}}2

    std::unique_ptr<GroundPlogBackend>                        out_;
    Plog::Program                                                   prg_;
    Defines                                                   defs_;
    std::unique_ptr<NonGroundProgramBuilder>   pb_;
    std::unique_ptr<PlogParser>                               parser_;
    FinishHandler                                             finishHandler_;
    GroundPlog::GroundPlogFacade                              *groundplog_ = nullptr;
    GroundPlog::Cli::GroundPlogCliConfig                      &groundPlogConfig_;
    PostGroundFunc                                            pgf_;
    PreSolveFunc                                              psf_;
    std::vector<Gringo::UProp>                                props_;
    Plog::Logger                                              logger_;
    Clingo::Control                                           clingoControl;
    bool parsed                 = false;
    bool grounded               = false;
    bool configUpdate_          = false;
    // the flag is true if the mode is query mode, and the algorithm is for dco programs
    SolvingMode solvingMode;
private:
    PlogGroundProgramBuilder *pb;
};


inline void enableAll(PlogOptions& out, bool enable) {
    out.wNoAtomUndef          = !enable;
    out.wNoFileIncluded       = !enable;
    out.wNoOperationUndefined = !enable;
    out.wNoVariableUnbounded  = !enable;
    out.wNoGlobalVariable     = !enable;
    out.wNoOther              = !enable;
}


inline bool parseWarning(const std::string& str, PlogOptions& out) {
    if (str == "none")                     { enableAll(out, false);             return true; }
    if (str == "all")                      { enableAll(out, true);              return true; }
    if (str == "no-atom-undefined")        { out.wNoAtomUndef          = true;  return true; }
    if (str ==    "atom-undefined")        { out.wNoAtomUndef          = false; return true; }
    if (str == "no-file-included")         { out.wNoFileIncluded       = true;  return true; }
    if (str ==    "file-included")         { out.wNoFileIncluded       = false; return true; }
    if (str == "no-operation-undefined")   { out.wNoOperationUndefined = true;  return true; }
    if (str ==    "operation-undefined")   { out.wNoOperationUndefined = false; return true; }
    if (str == "no-variable-unbounded")    { out.wNoVariableUnbounded  = true;  return true; }
    if (str ==    "variable-unbounded")    { out.wNoVariableUnbounded  = false; return true; }
    if (str == "no-global-variable")       { out.wNoGlobalVariable     = true;  return true; }
    if (str ==    "global-variable")       { out.wNoGlobalVariable     = false; return true; }
    if (str == "no-other")                 { out.wNoOther              = true;  return true; }
    if (str ==    "other")                 { out.wNoOther              = false; return true; }
    return false;
}

//inline bool parseWarning(const std::string& str, PlogOptions& out);
#endif
