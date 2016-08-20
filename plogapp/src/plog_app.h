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

#ifndef PLOG_PLOG_APP_H
#define PLOG_PLOG_APP_H


#include "groundplog/groundplog_app.h"
#include "plog/plogcontrol.hh"

// Standalone plog application.
class PlogApp : public GroundPlog::Cli::GroundPlogAppBase {
    using Output      = GroundPlog::Cli::Output;
    using BaseType    = GroundPlog::Cli::GroundPlogAppBase;
public:
    PlogApp();
    const char* getName()    const override { return "plog"; }
    const char* getVersion() const override { return "2.0"; }
    const char* getUsage()   const override { return "[options] [files]"; }

    void shutdown() override;
protected:
    enum Mode { mode_clingo = 0, mode_ground_plog = 1, mode_gringo = 2 };
    void        initOptions(ProgramOptions::OptionContext& root) override;
    void        validateOptions(const ProgramOptions::OptionContext& root, const ProgramOptions::ParsedOptions& parsed, const ProgramOptions::ParsedValues& vals) override;
    void        run(GroundPlog::GroundPlogFacade& clasp) override;
    Output*     createOutput() override;
    void        printHelp(const ProgramOptions::OptionContext& root) override;
    void        printVersion() override;

    // -------------------------------------------------------------------------------------------
    // Event handler
    void onEvent(const GroundPlog::Event& ev) override;
    bool onResult(const GroundPlog::Solver& s, const double result) override;
    bool onNonDCO(const GroundPlog::Solver& s) override;

    // -------------------------------------------------------------------------------------------
private:
    PlogOptions grOpts_;
    Mode mode_;
    DefaultGringoModule module;
    std::unique_ptr<PlogControl> grd;
};



#endif //PLOG_PLOG_APP_H
