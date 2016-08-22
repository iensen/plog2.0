//
// Created by iensen on 8/22/16.
//

#include <stdarg.h>
#include <groundplog/cli/groundplog_output.h>


GroundPlog::Cli::TextOutput::TextOutput() {

}

GroundPlog::Cli::TextOutput::~TextOutput() {

}

static inline std::string prettify(const std::string& str) {
    if (str.size() < 40) return str;
    std::string t("...");
    t.append(str.end()-38, str.end());
    return t;
}


void GroundPlog::Cli::TextOutput::run(const char *solver, const char *version, const std::string *begInput,
                                      const std::string *endInput) {
    if (!version) version = "";
    if (solver) comment("%s version %s\n", solver, version);
    if (begInput != endInput) {
        comment( "Reading from %s%s\n", prettify(*begInput).c_str(), (endInput - begInput) > 1 ? " ..." : "");
    }
}

void GroundPlog::Cli::TextOutput::shutdown() {
    throw "not implemented yet";
}

void GroundPlog::Cli::TextOutput::printUnsat() {
    throw "not implemented yet";

}

void GroundPlog::Cli::TextOutput::onEvent(const GroundPlog::Event &ev) {
    throw "not implemented yet";
}

void GroundPlog::Cli::TextOutput::startStep(const GroundPlog::GroundPlogFacade &) {
    throw "not implemented yet";
}

void GroundPlog::Cli::TextOutput::comment(const char *fmt, ...) const {
        va_list args;
        va_start(args, fmt);
        vfprintf(stdout, fmt, args);
        va_end(args);
        fflush(stdout);

}

GroundPlog::Cli::Output::Output(): summary_(0) {
}

GroundPlog::Cli::Output::~Output() {
    throw "not implemented yet";
}

void GroundPlog::Cli::Output::shutdown(const GroundPlog::GroundPlogFacade::Summary &summary) {
    throw "not implemented yet";
}

void GroundPlog::Cli::Output::onEvent(const GroundPlog::Event &ev) {
    EventHandler::onEvent(ev);
}

bool GroundPlog::Cli::Output::onUnsat(const GroundPlog::Solver &s) {
    return ResultHandler::onUnsat(s);
}

void GroundPlog::Cli::Output::printUnsat() {
    throw "not implemented yet";
}

void GroundPlog::Cli::Output::printProbability() {
    throw "not implemented yet";
}

void GroundPlog::Cli::Output::startStep(const GroundPlog::GroundPlogFacade &) {
    throw "not implemented yet";
}

void GroundPlog::Cli::Output::stopStep(const GroundPlog::GroundPlogFacade::Summary &summary) {
    throw "not implemented yet";
}

GroundPlog::Cli::Output &GroundPlog::Cli::Output::operator=(const GroundPlog::Cli::Output &) {
    throw "not implemented yet";
}
