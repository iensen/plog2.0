// {{{ GPL License

// This file is part of gringo - a grounder for logic programs.
// Copyright (C) 2016  Evgenii Balai

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// }}}


#include "plog_app.h"

PlogApp::PlogApp() { }

void PlogApp::shutdown() {
   throw "not implemented yet";
}

void PlogApp::initOptions(ProgramOptions::OptionContext &root) {
    throw "not implemented yet";
}

void PlogApp::validateOptions(const ProgramOptions::OptionContext &root, const ProgramOptions::ParsedOptions &parsed,
                              const ProgramOptions::ParsedValues &vals) {
    throw "not implemented yet";
}

void PlogApp::run(GroundPlog::GroundPlogFacade &clasp) {
    throw "not implemented yet";
}

PlogApp::Output *PlogApp::createOutput() {
    throw "not implemented yet";
}

void PlogApp::printHelp(const ProgramOptions::OptionContext &root) {
    throw "not implemented yet";
}

void PlogApp::printVersion() {
    throw "not implemented yet";
}

void PlogApp::onEvent(const GroundPlog::Event &ev) {
    throw "not implemented yet";
}

bool PlogApp::onResult(const GroundPlog::Solver &s, const double result) {
    throw "not implemented yet";
}

bool PlogApp::onNonDCO(const GroundPlog::Solver &s) {
    throw "not implemented yet";
}
