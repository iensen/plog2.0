//
// Created by iensen on 8/15/16.
//
#include "groundplog_app.h"
#include <iostream>
#include <fstream>

namespace GroundPlog {
    namespace Cli {

        GroundPlogAppBase::GroundPlogAppBase() {}

        GroundPlogAppBase::~GroundPlogAppBase() {}

        void GroundPlogAppBase::storeCommandArgs(const ProgramOptions::ParsedValues &values) {
            /* for whatever reason, we don't need the values */
        }

        void GroundPlogAppBase::handleStartOptions(GroundPlogFacade &clasp) {
            throw "not implemented yet";
        }

        bool GroundPlogAppBase::handlePostGroundOptions(ProgramBuilder &prg) {
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

        void GroundPlogAppBase::initOptions(ProgramOptions::OptionContext &root) {

            groundPlogConfig_.addOptions(root);
            groundPlogAppOpts_.initOptions(root);
            root.find("verbose")->get()->value()->defaultsTo("1");

        }

        void GroundPlogAppBase::validateOptions(const ProgramOptions::OptionContext &root,
                                                const ProgramOptions::ParsedOptions &parsed,
                                                const ProgramOptions::ParsedValues &values) {
            using ProgramOptions::Error;
            if (!groundPlogAppOpts_.validateOptions(parsed) || !groundPlogConfig_.finalize(parsed, true)) {
                throw Error("command-line error!");
            }
            GroundPlogAppOptions& app = groundPlogAppOpts_;
            for (std::size_t i = 1; i < app.input.size(); ++i) {
                if (!isStdIn(app.input[i]) && !std::ifstream(app.input[i].c_str()).is_open()) {
                    throw Error(ClaspStringBuffer().appendFormat("'%s': could not open input file!", app.input[i].c_str()).c_str());

                }
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
            throw "not implemented yet";
        }

        bool GroundPlogAppBase::onSignal(int) {
            throw "not implemented yet";
        }

        void GroundPlogAppBase::printHelp(const ProgramOptions::OptionContext &root) {
            throw "not implemented yet";
        }

        void GroundPlogAppBase::printVersion() {
            throw "not implemented yet";
        }

        bool GroundPlogAppBase::parsePositional(const std::string &s, std::string &out) {
            int num;
            if   (bk_lib::string_cast(s, num)) { out = "number"; }
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

        int GroundPlogAppBase::exitCode(const GroundPlogAppBase::RunSummary &sol) const {
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



        bool GroundPlogAppOptions::validateOptions(const ProgramOptions::ParsedOptions &parsed) {
            return true; // no options yet
        }

        void GroundPlogAppOptions::initOptions(ProgramOptions::OptionContext &root) {
            using namespace ProgramOptions;
            OptionGroup basic("Basic Options");
            // add other options
            basic.addOptions()
                    ("file,f,@2" , storeTo(input)->composing(), "Input files")
                    ;
            root.add(basic);
        }


    }
}
