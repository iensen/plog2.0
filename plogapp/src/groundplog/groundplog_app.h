//
// Created by iensen on 8/15/16.
//

#ifndef PLOG_GRNDPLOG_APP_H
#define PLOG_GRNDPLOG_APP_H
#include <program_opts/typed_value.h>
#include <program_opts/application.h>
#include <clasp/util/timer.h>
#include <groundplog/cli/groundplog_options.h>
#include <groundplog/cli/groundplog_output.h>
#include <string>
#include <vector>
#include <iosfwd>
#include <memory>

#include <groundplog/program_builder.h>
#include <groundplog/util/misc_types.h>
#include <groundplog/solver.h>

namespace GroundPlog {

    inline bool isStdIn(const std::string& in)  { return in == "-" || in == "stdin"; }
    inline bool isStdOut(const std::string& out){ return out == "-" || out == "stdout"; }

    namespace Cli {
/////////////////////////////////////////////////////////////////////////////////////////
// groundplog exit codes !!! check why this codes are used
/////////////////////////////////////////////////////////////////////////////////////////
        enum ExitCode {
            E_UNKNOWN   = 0,  /*!< Satisfiablity of problem not knwon; search not started.    */
            E_INTERRUPT = 1,  /*!< Run was interrupted.                                       */
            E_FINISHED   = 10, /*!< Algorithm completed.                                      */
            E_MEMORY    = 20, /*!< Run was interrupted by out of memory exception.            */
            E_ERROR     = 33, /*!< Run was interrupted by an error.                           */
            E_NO_RUN    = 65 /*!< Search not started because of syntax or command line error. */
        };
/////////////////////////////////////////////////////////////////////////////////////////
// groundplog app helpers
/////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////
// groundplog specific application options
/////////////////////////////////////////////////////////////////////////////////////////
        struct GroundPlogAppOptions {
            GroundPlogAppOptions();
            void initOptions(ProgramOptions::OptionContext& root);

            bool validateOptions(const ProgramOptions::ParsedOptions& parsed);
            typedef std::vector<std::string>  StringSeq;
            StringSeq   input;     // list of input files - only first used!
        };
/////////////////////////////////////////////////////////////////////////////////////////
// ground P-log application base
/////////////////////////////////////////////////////////////////////////////////////////
// Base class for applications using the clasp library.
        class GroundPlogAppBase : public ProgramOptions::Application {
        public:
            typedef GroundPlogFacade::Summary  RunSummary;
            typedef ProgramOptions::PosOption PosOption;
        protected:
            using ProgramOptions::Application::run;
            GroundPlogAppBase();
            ~GroundPlogAppBase();
            // -------------------------------------------------------------------------------------------
            // Functions to be implemented by subclasses
            virtual void          run(GroundPlogFacade& groundPlog)      = 0;
            virtual void          storeCommandArgs(const ProgramOptions::ParsedValues& values);
            // -------------------------------------------------------------------------------------------
            // Helper functions that subclasses might call during run
            void handleStartOptions(GroundPlogFacade& clasp);
            bool handlePostGroundOptions(ProgramBuilder& prg);
            bool handlePreSolveOptions(GroundPlogFacade& clasp);
            // -------------------------------------------------------------------------------------------
            // Application functions
            virtual const int*  getSignals()    const;
            virtual HelpOpt     getHelpOption() const { return HelpOpt("Print {1=basic|2=more|3=full} help and exit", 3); }
            virtual PosOption   getPositional() const { return parsePositional; }
            virtual void        initOptions(ProgramOptions::OptionContext& root);
            virtual void        validateOptions(const ProgramOptions::OptionContext& root, const ProgramOptions::ParsedOptions& parsed, const ProgramOptions::ParsedValues& values);
            virtual void        setup();
            virtual void        run();
            virtual void        shutdown();
            virtual bool        onSignal(int);
            virtual void        printHelp(const ProgramOptions::OptionContext& root);
            virtual void        printVersion();
            static  bool        parsePositional(const std::string& s, std::string& out);
            // -------------------------------------------------------------------------------------------
            // Event handler
            virtual void onEvent(const Event& ev);
            virtual bool onResult(const Solver& s, const double result);
            virtual bool onNonDCO(const Solver& s);
            // -------------------------------------------------------------------------------------------
            // Status information & output
            int  exitCode(const RunSummary& sol)    const;
            void printTemplate()                    const;
            void printDefaultConfigs()              const;
            void printLibClaspVersion()             const;
            std::istream& getStream();
            // -------------------------------------------------------------------------------------------

            typedef SingleOwnerPtr<GroundPlogFacade> GroundPlogPtr;
            GroundPlogCliConfig  groundPlogConfig_;
            GroundPlogAppOptions groundPlogAppOpts_;
            GroundPlogPtr        groundPlog_;
        };
/////////////////////////////////////////////////////////////////////////////////////////
// clasp application
/////////////////////////////////////////////////////////////////////////////////////////
// Standalone clasp application.
        class GroundPlogApp : public GroundPlogAppBase {
        public:
            GroundPlogApp();
            const char* getName()       const { return "ground plog"; }
            const char* getVersion()    const { return "1.0"; }
            const char* getUsage()      const {
                return
                        "[options] [file]\n"
                                "compute answer for the program <file>";
            }
        protected:
            virtual void        run(GroundPlogFacade& clasp);
            virtual void        printHelp(const ProgramOptions::OptionContext& root);
        private:
            GroundPlogApp(const GroundPlogApp&);
            GroundPlogApp& operator=(const GroundPlogApp&);
        };
    }}
#endif //PLOG_GRNDPLOG_APP_H




