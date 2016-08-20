#include <gringo/output/output.hh>
#include <gringo/input/program.hh>
#include <gringo/input/programbuilder.hh>
#include <gringo/input/nongroundparser.hh>
#include <gringo/input/groundtermparser.hh>
#include <gringo/control.hh>
#include <gringo/logger.hh>
#include <gringo/scripts.hh>
#include <groundplog/program.h>
#include <groundplog/groundplog_facade.h>
#include <groundplog/cli/groundplog_options.h>
#include <program_opts/application.h>
#include <program_opts/string_convert.h>
#include <mutex>
#include<plog/plog.h>


struct plog_control {
    using FinishHandler = std::function<void (GroundPlog::SolveResult)>;
    using Assumptions = std::vector<std::pair<Gringo::Symbol, bool>>;
    using GroundVec = std::vector<std::pair<Gringo::String, Gringo::SymVec>>;
    using NewControlFunc = Gringo::Control* (*)(int, char const **);
    using FreeControlFunc = void (*)(Gringo::Control *);
    virtual Gringo::SymbolicAtoms &getDomain() = 0;
    virtual void ground(GroundVec const &vec, Gringo::Context *context) = 0;
    virtual Gringo::SolveResult solve() = 0;
    virtual void interrupt() = 0;
    virtual void add(std::string const &name, Gringo::FWStringVec const &params, std::string const &part) = 0;
    virtual void load(std::string const &filename) = 0;
    virtual Gringo::Symbol getConst(std::string const &name) = 0;
    virtual Potassco::Atom_t addProgramAtom() = 0;
    virtual void beginAdd() = 0;
    virtual void add(plog_ast_statement_t const &stm) = 0;
    virtual void endAdd() = 0;
    virtual ~plog_control() noexcept = default;
};



struct PlogOptions {

};

// {{{1 declaration of DefaultGringoModule

struct DefaultGringoModule : Gringo::GringoModule {
    DefaultGringoModule();
    Gringo::Control *newControl(int argc, char const * const *argv, Gringo::Logger::Printer p, unsigned messageLimit)override;
    Gringo::Symbol parseValue(std::string const &str, Gringo::Logger::Printer printer, unsigned messageLimit) override;
};


class PlogControl : public plog_control, private Gringo::ConfigProxy, private Gringo::SymbolicAtoms {
public:
    using StringVec        = std::vector<std::string>;
    using ExternalVec      = std::vector<std::pair<Gringo::Symbol, Potassco::Value_t>>;
    using StringSeq        = ProgramOptions::StringSeq;
    using PostGroundFunc   = std::function<bool (GroundPlog::ProgramBuilder &)>;
    using PreSolveFunc     = std::function<bool (GroundPlog::GroundPlogFacade &)>;
    enum class ConfigUpdate { KEEP, REPLACE };

    PlogControl(GroundPlog::GroundPlogFacade *groundplog,
                GroundPlog::Cli::GroundPlogCliConfig &groundplogConfig, PostGroundFunc pgf, PreSolveFunc psf, Gringo::Logger::Printer printer, unsigned messageLimit);
    ~PlogControl() noexcept override;
    void parse();
    void parse(const StringSeq& files, const PlogOptions& opts, GroundPlog::Program* out, bool addStdIn = true);
    void main();
    void onFinish(GroundPlog::GroundPlogFacade::Result ret);
    bool update();

    virtual void postGround(GroundPlog::ProgramBuilder& prg) { throw "not implemented"; }
    virtual void prePrepare(GroundPlog::GroundPlogFacade& ) { throw "not implemented"; }
    virtual void preSolve(GroundPlog::GroundPlogFacade& groundplog) { throw "not implemented";  }
    virtual void postSolve(GroundPlog::GroundPlogFacade& ) { }

    // {{{2 SymbolicAtoms interface

    Gringo::SymbolicAtomIter begin(Gringo::Sig sig) const override;
    Gringo::SymbolicAtomIter begin() const override;
    Gringo::SymbolicAtomIter end() const override;
    bool eq(Gringo::SymbolicAtomIter it, Gringo::SymbolicAtomIter jt) const override;
    Gringo::SymbolicAtomIter lookup(Gringo::Symbol atom) const override;
    size_t length() const override;
    std::vector<Gringo::Sig> signatures() const override;
    Gringo::Symbol atom(Gringo::SymbolicAtomIter it) const override;
    Potassco::Lit_t literal(Gringo::SymbolicAtomIter it) const override;
    bool fact(Gringo::SymbolicAtomIter it) const override;
    Gringo::SymbolicAtomIter next(Gringo::SymbolicAtomIter it) override;
    bool valid(Gringo::SymbolicAtomIter it) const override;


    // {{{2 Control interface

    Gringo::SymbolicAtoms &getDomain() override;
    void ground(Gringo::Control::GroundVec const &vec, Gringo::Context *ctx) override;
    void add(std::string const &name, Gringo::FWStringVec const &params, std::string const &part) override;
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

    std::unique_ptr<Gringo::Output::OutputBase>               out_;
    Gringo::Input::Program                                    prg_;
    Gringo::Defines                                           defs_;
    std::unique_ptr<Gringo::Input::NongroundProgramBuilder>   pb_;
    std::unique_ptr<Gringo::Input::NonGroundParser>           parser_;
    FinishHandler                                             finishHandler_;
    GroundPlog::GroundPlogFacade                                       *clasp_ = nullptr;
    GroundPlog::Cli::GroundPlogCliConfig                               &claspConfig_;
    PostGroundFunc                                            pgf_;
    PreSolveFunc                                              psf_;
    std::vector<Gringo::UProp>                                props_;
    bool parsed                 = false;
    bool grounded               = false;
    bool configUpdate_          = false;
};

