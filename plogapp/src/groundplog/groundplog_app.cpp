//
// Created by iensen on 8/15/16.
//
#include "groundplog_app.h"

namespace GroundPlog {
    namespace Cli {
        GroundPlogAppBase::GroundPlogAppBase() {}

        GroundPlogAppBase::~GroundPlogAppBase() {}

        Output *GroundPlogAppBase::createOutput() {
            throw "not implemented yet";
        }

        void GroundPlogAppBase::storeCommandArgs(const ProgramOptions::ParsedValues &values) {
            throw "not implemented yet";
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
            throw "not implemented yet";
        }

        void GroundPlogAppBase::initOptions(ProgramOptions::OptionContext &root) {
            throw "not implemented yet";
        }

        void GroundPlogAppBase::validateOptions(const ProgramOptions::OptionContext &root,
                                                const ProgramOptions::ParsedOptions &parsed,
                                                const ProgramOptions::ParsedValues &values) {
            throw "not implemented yet";
        }

        void GroundPlogAppBase::setup() {
            throw "not implemented yet";
        }

        void GroundPlogAppBase::run() {
            throw "not implemented yet";
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
            throw "not implemented yet";
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
    }
}