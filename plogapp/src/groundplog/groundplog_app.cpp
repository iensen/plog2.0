//
// Created by iensen on 8/15/16.
//
#include "groundplog_app.h"
#include <iostream>
#include <fstream>
#include <signal.h>

namespace GroundPlog {
    namespace Cli {

        GroundPlogAppBase::GroundPlogAppBase() {}

        GroundPlogAppBase::~GroundPlogAppBase() {}

        void GroundPlogAppBase::storeCommandArgs(const Potassco::ProgramOptions::ParsedValues &values) {
            /* for whatever reason, we don't need the values */
        }

        void GroundPlogAppBase::handleStartOptions(GroundPlogFacade &clasp) {
            throw "not implemented yet";
        }

        bool GroundPlogAppBase::handlePostGroundOptions(Program &prg) {
            throw "not implemented yet";
        }

        bool GroundPlogAppBase::handlePreSolveOptions(GroundPlogFacade &clasp) {
            throw "not implemented yet";
        }

        const int *GroundPlogAppBase::getSignals() const {
            static const int signals[] = {
                    SIGINT, SIGTERM
#if !defined (_WIN32)
                    , SIGUSR1, SIGUSR2, SIGQUIT, SIGHUP, SIGXCPU, SIGXFSZ
#endif
                    , 0};
            return signals;

        }

        void GroundPlogAppBase::initOptions(Potassco::ProgramOptions::OptionContext &root) {

            groundPlogConfig_.addOptions(root);
            groundPlogAppOpts_.initOptions(root);
            root.find("verbose")->get()->value()->defaultsTo("1");

        }

        void GroundPlogAppBase::validateOptions(const Potassco::ProgramOptions::OptionContext &root,
                                                const Potassco::ProgramOptions::ParsedOptions &parsed,
                                                const Potassco::ProgramOptions::ParsedValues &values) {
            using Potassco::ProgramOptions::Error;
            if (!groundPlogAppOpts_.validateOptions(parsed) || !groundPlogConfig_.finalize(parsed, true)) {
                throw Error("command-line error!");
            }
            GroundPlogAppOptions& app = groundPlogAppOpts_;
            for (std::size_t i = 1; i < app.input.size(); ++i) {
                POTASSCO_EXPECT(isStdIn(app.input[i]) || std::ifstream(app.input[i].c_str()).is_open(),
                                "'%s': could not open input file!", app.input[i].c_str());
            }
            setExitCode(0);
            storeCommandArgs(values);
        }

        void GroundPlogAppBase::setup() {
            groundPlog_         = new GroundPlogFacade();
        }

        void GroundPlogAppBase::run() {

            try        { run(*groundPlog_); }
            catch(...) {
                try { blockSignals(); setExitCode(E_ERROR); throw; }
                catch (const std::bad_alloc&  ) { setExitCode(E_MEMORY); error("std::bad_alloc"); }
                catch (const std::exception& e) { error(e.what()); }
                catch (...)                     { ; }
            }
        }

        void GroundPlogAppBase::shutdown() {
            if (!groundPlog_.get()) { return; }
            setExitCode(getExitCode());
        }

        bool GroundPlogAppBase::onSignal(int) {
            throw "not implemented yet";
        }

        void GroundPlogAppBase::printHelp(const Potassco::ProgramOptions::OptionContext &root) {
            throw "not implemented yet";
        }

        void GroundPlogAppBase::printVersion() {
            throw "not implemented yet";
        }

        bool GroundPlogAppBase::parsePositional(const std::string &s, std::string &out) {
            int num;
            if   (Potassco::string_cast(s, num)) { out = "number"; }
            else                               { out = "file";   }
            return true;
        }

        void GroundPlogAppBase::onEvent(const Event &ev) {
            throw "not implemented yet";
        }

        bool GroundPlogAppBase::onResult(const Solver &s, const double result) {
            throw "not implemented yet";
        }

        bool GroundPlogAppBase::onNonDCO(const Solver &s) {
            throw "not implemented yet";
        }

        void GroundPlogAppBase::printTemplate() const {
            throw "not implemented yet";
        }

        void GroundPlogAppBase::printDefaultConfigs() const {
            throw "not implemented yet";
        }

        void GroundPlogAppBase::printLibClaspVersion() const {
            throw "not implemented yet";
        }

        std::istream &GroundPlogAppBase::getStream() {
            throw "not implemented yet";
        }

        GroundPlogAppOptions::GroundPlogAppOptions(){

        }



        bool GroundPlogAppOptions::validateOptions(const Potassco::ProgramOptions::ParsedOptions &parsed) {
            return true; // no options yet
        }

        void GroundPlogAppOptions::initOptions(Potassco::ProgramOptions::OptionContext &root) {
            using namespace Potassco::ProgramOptions;
            OptionGroup basic("Basic Options");
            // add other options
            basic.addOptions()
                    ("file,f,@2" , storeTo(input)->composing(), "Input files")
                    ;
            root.add(basic);
        }


    }
}
