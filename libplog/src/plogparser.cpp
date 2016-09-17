//
// Created by iensen on 9/3/16.
//

#include <plog/plogparser.h>

PlogParser::PlogParser(NonGroundProgramBuilder &pb)   : not_("not")
        , pb_(pb)
        , _startSymbol(0)
        , _filename("") { }

void PlogParser::parseError(Location const &loc, std::string const &token) {
    throw "not implemented yet";
}

void PlogParser::pushFile(std::string &&filename, Logger &log) {
    throw "not implemented yet";
}

void PlogParser::pushStream(std::string &&name, std::unique_ptr<std::istream>, Logger &log) {
    throw "not implemented yet";
}

void PlogParser::pushBlock(std::string const &name, IdVec const &vec, std::string const &block, Logger &log) {
    throw "not implemented yet";
}

int PlogParser::lex(void *pValue, Location &loc) {
    throw "not implemented yet";
}

bool PlogParser::parseDefine(std::string const &define, Logger &log) {
    throw "not implemented yet";
}

bool PlogParser::parse(Logger &log) {
    throw "not implemented yet";
}

bool PlogParser::empty() {  throw "not implemented yet";}

void PlogParser::include(std::string file, Location const &loc, bool include, Logger &log) {
    throw "not implemented yet";
}

NonGroundProgramBuilder &PlogParser::builder() {
    throw "not implemented yet";
}

PlogParser::~PlogParser() {
    throw "not implemented yet";
}

void PlogParser::lexerError(std::string token) {
    throw "not implemented yet";
}

bool PlogParser::push(std::string const &filename, bool include) {
    throw "not implemented yet";
}

bool PlogParser::push(std::string const &file, std::unique_ptr<std::istream> in) {
    throw "not implemented yet";
}

void PlogParser::pop() {
    LexerState::pop();
}

void PlogParser::_init() {
    throw "not implemented yet";
}

void PlogParser::condition(PlogParser::Condition cond) {
    throw "not implemented yet";
}

void PlogParser::start(Location &loc) {
    throw "not implemented yet";
}

PlogParser::Condition PlogParser::condition() const {
    throw "not implemented yet";
}

std::string PlogParser::filename() const {
    throw "not implemented yet";
};

int PlogParser::lex_impl(void *pValue, Location &loc) {
    throw "not implemented yet";
}