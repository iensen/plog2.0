// {{{ GPL License

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



#include <clingo/clingocontrol.hh>
#include "plog_app.h"

using namespace GroundPlog;
using namespace GroundPlog::Cli;


static bool parseConst(const std::string& str, std::vector<std::string>& out) {
    out.push_back(str);
    return true;
}

static bool parseText(const std::string&, PlogOptions& out) {
    out.outputFormat = Gringo::Output::OutputFormat::TEXT;
    return true;
}



PlogApp::PlogApp() { }

void PlogApp::shutdown() {
    GroundPlog::Cli::GroundPlogAppBase::shutdown();
}

void PlogApp::initOptions(Potassco::ProgramOptions::OptionContext &root) {
    using namespace Potassco::ProgramOptions;
    BaseType::initOptions(root);
    grOpts_.defines.clear();
    grOpts_.verbose = false;
    OptionGroup gringo("Gringo Options");
    gringo.addOptions()
            ("text", storeTo(grOpts_, parseText)->flag(), "Print plain text format")
            ("const,c", storeTo(grOpts_.defines, parseConst)->composing()->arg("<id>=<term>"), "Replace term occurrences of <id> with <term>")
            ("output,o", storeTo(grOpts_.outputFormat = Gringo::Output::OutputFormat::INTERMEDIATE, values<Gringo::Output::OutputFormat>()
                    ("intermediate", Gringo::Output::OutputFormat::INTERMEDIATE)
                    ("text", Gringo::Output::OutputFormat::TEXT)
                    ("reify", Gringo::Output::OutputFormat::REIFY)
                    ("smodels", Gringo::Output::OutputFormat::SMODELS)), "Choose output format:\n"
                     "      intermediate: print intermediate format\n"
                     "      text        : print plain text format\n"
                     "      reify       : print program as reified facts\n"
                     "      smodels     : print smodels format\n"
                     "                    (only supports basic features)")
            ("output-debug", storeTo(grOpts_.outputOptions.debug = Gringo::Output::OutputDebug::NONE, values<Gringo::Output::OutputDebug>()
                    ("none", Gringo::Output::OutputDebug::NONE)
                    ("text", Gringo::Output::OutputDebug::TEXT)
                    ("translate", Gringo::Output::OutputDebug::TRANSLATE)
                    ("all", Gringo::Output::OutputDebug::ALL)), "Print debug information during output:\n"
                     "      none     : no additional info\n"
                     "      text     : print rules as plain text (prefix %%)\n"
                     "      translate: print translated rules as plain text (prefix %%%%)\n"
                     "      all      : combines text and translate")
            ("warn,W"                   , storeTo(grOpts_, parseWarning)->arg("<warn>")->composing(), "Enable/disable warnings:\n"
                    "      none:                     disable all warnings\n"
                    "      all:                      enable all warnings\n"
                    "      [no-]atom-undefined:      a :- b.\n"
                    "      [no-]file-included:       #include \"a.lp\". #include \"a.lp\".\n"
                    "      [no-]operation-undefined: p(1/0).\n"
                    "      [no-]variable-unbounded:  $x > 10.\n"
                    "      [no-]global-variable:     :- #count { X } = 1, X = 1.\n"
                    "      [no-]other:               clasp related and uncategorized warnings")
            ("rewrite-minimize"         , flag(grOpts_.rewriteMinimize = false), "Rewrite minimize constraints into rules")
            ("keep-facts"               , flag(grOpts_.keepFacts = false), "Do not remove facts from normal rules")
            ("reify-sccs"               , flag(grOpts_.outputOptions.reifySCCs = false), "Calculate SCCs for reified output")
            ("reify-steps"              , flag(grOpts_.outputOptions.reifySteps = false), "Add step numbers to reified output")
            ("foobar,@4"                , storeTo(grOpts_.foobar, Gringo::parseFoobar) , "Foobar")
            ;
    root.add(gringo);

    OptionGroup basic("Basic Options");
    // add basic options
    basic.addOptions()
            ("mode", storeTo(mode_ = mode_query, values<Mode>()
                     ("query", mode_query)
                     ("pw", mode_possible_worlds)),
             "Run in {query|compute possible wolrds} mode\n")
            ("algo", storeTo(qalgo_ = qalgo_naive, values<QAlgo>()
                     ("dco", QAlgo::qalgo_dco)
                     ("naive", QAlgo::qalgo_naive)),
             "Use {algorithm for dco programs|naive algorithm that computes all possible worlds}\n");

    root.add(basic);

}

void PlogApp::validateOptions(const Potassco::ProgramOptions::OptionContext &root, const Potassco::ProgramOptions::ParsedOptions &parsed,
                              const Potassco::ProgramOptions::ParsedValues &vals) {
	 BaseType::validateOptions(root, parsed, vals);
}

SolvingMode PlogApp::getSolvingMode() {
      if(mode_ == Mode::mode_possible_worlds) {
          return SolvingMode::possible_worlds;
      } else {
          if(qalgo_ == QAlgo::qalgo_naive) {
              return SolvingMode::query_naive;
          } else {
              return SolvingMode::query_dco;
          }
      }

}
void PlogApp::run(GroundPlog::GroundPlogFacade &groundPlog) {
    printVersion();
    try {
        using namespace std::placeholders;
        groundPlog.start(groundPlogConfig_);
        grd = Gringo::gringo_make_unique<PlogControl>(groundPlog_.get(), groundPlogConfig_, std::bind(&PlogApp::handlePostGroundOptions, this, _1), std::bind(&PlogApp::handlePreSolveOptions, this, _1), nullptr,
                                                      getSolvingMode());
        grd->parse(groundPlogAppOpts_.input, grOpts_);
        if (mode_ == mode_query) {
              grd->computeQuery();
        }
        else if(mode_ == mode_possible_worlds){
            grd->computePossibleWorlds();
        }
    }
    catch (Gringo::GringoError const &e) {
        std::cerr << e.what() << std::endl;
        throw std::runtime_error("fatal error");
    }
    catch (...) { throw; }
}



void PlogApp::printHelp(const Potassco::ProgramOptions::OptionContext &root) {
    throw "not implemented yet";
}

void PlogApp::printVersion() {
    std::cout << getName()<< " " << getVersion() << std::endl;
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
