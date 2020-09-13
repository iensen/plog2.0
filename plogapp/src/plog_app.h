// {{{ GPL License

// Copyright (C) 2020  Evgenii Balai

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
    using BaseType    = GroundPlog::Cli::GroundPlogAppBase;
public:
    PlogApp();
    const char* getName()    const override { return "Plog"; }
    const char* getVersion() const override { return "2.1"; }
    const char* getUsage()   const override { return "[options] [files]"; }

    void shutdown() override;
protected:
    enum Mode { mode_query = 0, mode_possible_worlds = 1 };
//    enum Format { json = 0, text = 1};
    enum QAlgo { qalgo_naive = 0, qalgo_dco = 1 };
    void        initOptions(Potassco::ProgramOptions::OptionContext& root) override;
    void        validateOptions(const Potassco::ProgramOptions::OptionContext& root, const Potassco::ProgramOptions::ParsedOptions& parsed, const Potassco::ProgramOptions::ParsedValues& vals) override;
    void        run(GroundPlog::GroundPlogFacade& clasp) override;
    void        printHelp(const Potassco::ProgramOptions::OptionContext& root) override;
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

    Format format_;
    // algorithm used to answer queries
    QAlgo qalgo_;
    SolvingMode getSolvingMode();

    std::unique_ptr<PlogControl> grd;

};



#endif //PLOG_PLOG_APP_H
