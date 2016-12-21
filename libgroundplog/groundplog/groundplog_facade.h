//
// Created by iensen on 8/16/16.
//

#ifndef PLOG_GROUNDPLOG_FACEDE_H
#define PLOG_GROUNDPLOG_FACEDE_H
#include "solver_strategies.h"
#include "solve_algorithms.h"
#include<groundplog/util/platform.h>
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

        GroundPlogFacade();

        ~GroundPlogFacade();




        //! Returns whether the active step is ready for solving.
        bool prepared() const;

        //! Returns whether the active step is currently being solved.
        bool solving() const;

        //! Returns whether the active step has been solved, i.e., has a result.
        bool solved() const;

        //! Returns whether solving of the active step was interrupted.
        bool interrupted() const;






        //! Returns the active program or 0 if it was already released.
        Program *program() const { return builder_; }


        //@}

        /*!
         * \name Start functions
         * Functions for defining a problem.
         * Calling one of the start functions discards any previous problem
         * and emits a StepStart event.
         */



        //! Starts definition of a P-log problem
        Program& start(GroundPlogConfig & config);

        Result solve(Clingo::Control *ctl);


    private:
        struct Statistics;

        typedef SingleOwnerPtr <SolveData> SolvePtr;
        typedef SingleOwnerPtr <Statistics> StatsPtr;

        void init(GroundPlogConfig &cfg);

        void start();

        Program*   builder_;
        std::vector<Lit_t> assume_;
        GroundPlogConfig *config_;
        SolvePtr solve_; // NOTE: last so that it is destroyed first;
    };

}
#endif //PLOG_GROUNDPLOG_FACEDE_H
