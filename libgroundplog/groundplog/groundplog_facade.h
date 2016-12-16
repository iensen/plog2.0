//
// Created by iensen on 8/16/16.
//

#ifndef PLOG_GROUNDPLOG_FACEDE_H
#define PLOG_GROUNDPLOG_FACEDE_H
#include "solver_strategies.h"
#include "solve_algorithms.h"
#include<groundplog/util/platform.h>
#include<groundplog/program_builder.h>
#include<groundplog/program.h>
#include<vector>
#include <clingo.hh>

//! Provides a simplified interface to the services of the Ground Plog library.
namespace GroundPlog {



    struct SolveOptions {
            SolveAlgorithm* createSolveObject() const { return new ExactDCOSolve(); }
    };

    struct ParserOptions{};
    class GroundPlogConfig : public BasicSatConfig {

    public:
        typedef BasicSatConfig UserConfig;
        typedef Program::PrepOptions PrepOptions;
        SolveOptions   solve; /*!< Options for solve algorithm and enumerator. */
        PrepOptions     prep;   /*!< Options for asp preprocessing.      */
        ParserOptions  parse; /*!< Options for input parser. */

    };


    class GroundPlogFacade : public ResultHandler {
        struct SolveData;
        struct SolveStrategy;
    public:
        typedef SolveResult Result;

        //! Type summarizing one or more solving steps.
        struct Summary {
            typedef const GroundPlogFacade *FacadePtr;

            void init(GroundPlogFacade &f);

            bool notdco() const { return result.notdco(); }

            bool complete() const { return result.exhausted(); }


            FacadePtr facade;    /**< Facade object of this run.          */
            double totalTime; /**< Total wall clock time.              */
            double cpuTime;   /**< Total cpu time.                     */
            double solveTime; /**< Wall clock time for solving.        */
            double unsatTime; /**< Wall clock time to prove unsat.     */
            double satTime;   /**< Wall clock time to first model.     */
            Result result;    /**< Result of step.                     */
        };

        GroundPlogFacade();

        ~GroundPlogFacade();


        /*!
         * \name Query functions
         * Functions for checking the state of this object.
         */
        //@{
        //! Returns whether the problem is still valid.
        bool ok() const { return program()->ok();  }

        //! Returns whether the active step is ready for solving.
        bool prepared() const;

        //! Returns whether the active step is currently being solved.
        bool solving() const;

        //! Returns whether the active step has been solved, i.e., has a result.
        bool solved() const;

        //! Returns whether solving of the active step was interrupted.
        bool interrupted() const;


        //! Returns the summary of the active (accu = false) or all steps.
        const Summary &summary() const;





        //! Returns the active program or 0 if it was already released.
        ProgramBuilder *program() const { return builder_.get(); }


        //@}

        /*!
         * \name Start functions
         * Functions for defining a problem.
         * Calling one of the start functions discards any previous problem
         * and emits a StepStart event.
         */



        //! Starts definition of a P-log problem
        Program& start(GroundPlogConfig & config);

        //! Starts definition of a problem given in stream.
        ProgramBuilder &start(GroundPlogConfig& config, std::istream &stream);

        //! Enables support for (asynchronous) solve interrupts.
        void enableSolveInterrupts();

        //@}

        //! Tries to read the next program part from the stream passed to start().
        /*!
         * \return false if nothing was read because the stream is exhausted, solving was interrupted,
         * or the problem is unconditionally unsat.
         */
        bool read();

        //! Finishes the definition of a problem and prepares it for solving.
        /*!
         * \pre !solving()
         * \post prepared() || !ok()
         * \note If solved() is true, prepare() first starts a new solving step.
         */


        //! Solves the current problem.
        /*!
         * If prepared() is false, the function first calls prepare() to prepare the problem for solving.
         * \pre !solving()
         * \post solved()
         * \param eh An optional event handler that is notified on each model and
         *           once the solve operation has completed.
         * \param a A list of unit-assumptions under which solving should operate.
         */
        Result solve(Clingo::Control *ctl);

                //! Starts solving of the current problem signaling models via the returned generator object.
        /*!
        * Instead of signaling results via a callback, the returned generator object
        * can be used to query models one by one.
        * \pre !solving()
        * \note It is the caller's responsibility to finish the solve operation,
        * either by extracting models until ModelGenerator::next() returns false, or
        * by calling ModelGenerator::stop().
        */
        void startSolve(const std::vector<Lit_t> &a = {});

        //! Tries to interrupt the active solve operation.
        /*!
         * The function sends the given signal to the active solve operation.
         * If no solve operation is active (i.e. solving() is false), the signal
         * is queued and applied to the next solve operation.
         *
         * \param sig The signal to raise or 0, to re-raises a previously queued signal.
         * \return false if no operation was interrupted, because
         *         there is no active solve operation,
         *         or the operation does not support interrupts,
         *         or sig was 0 and there was no queued signal.
         *
         * \see enableSolveInterrupts()
         */
        bool interrupt(int sig);

        //! Forces termination of the current solving step.
        /*!
         * \post solved()
         * \return summary(true)
         */
        const Summary &shutdown();


        struct Ready : Event_t<Ready> {
            explicit Ready(const Summary& x) : Event_t<Ready>(subsystem_facade), summary(&x) {}
            const Summary* summary;
        };

        SharedContext ctx; /*!< Context-object used to store problem. */
    private:
        struct Statistics;
        typedef SingleOwnerPtr <ProgramBuilder> BuilderPtr;
        typedef SingleOwnerPtr <SolveData> SolvePtr;
        typedef SingleOwnerPtr <Summary> SummaryPtr;
        typedef SingleOwnerPtr <Statistics> StatsPtr;

        void init(GroundPlogConfig &cfg);

        void initBuilder(ProgramBuilder *in);

        void start();

        Result stop();


        void updateStats();


        void doUpdate(ProgramBuilder *p, bool updateConfig, void (*sig)(int));
        BuilderPtr   builder_;
        std::vector<Lit_t> assume_;
        GroundPlogConfig *config_;
        Summary      sum;
        SolvePtr solve_; // NOTE: last so that it is destroyed first;
        Result result();
    };

}
#endif //PLOG_GROUNDPLOG_FACEDE_H
