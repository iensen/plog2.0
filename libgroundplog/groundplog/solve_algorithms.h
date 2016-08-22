//
// Created by iensen on 8/21/16.
//

#ifndef PLOG_SOLVE_ALGORITHM_H
#define PLOG_SOLVE_ALGORITHM_H

#include <groundplog/solver_strategies.h>
namespace GroundPlog {

    class SolveAlgorithm {
    public:

        explicit SolveAlgorithm();

        virtual ~SolveAlgorithm();

        virtual bool interrupted() const = 0;


        //! Runs the solve algorithm.
        /*!
         * \param ctx     A context object containing the problem.
         * \param assume  A list of initial unit-assumptions.
         * \param onModel Optional handler to be called on each model.
         *
         * \return
         *  - true:  if the search stopped before the search-space was exceeded.
         *  - false: if the search-space was completely examined.
         *
         * \note
         * The use of assumptions allows for incremental solving. Literals contained
         * in assumptions are assumed to be true during search but are undone before solve returns.
         *
         * \note
         * Conceptually, solve() behaves as follows:
         * \code
         * start(ctx, assume);
         * while (next()) {
         *   if (!report(model()) || enum_limit_reached()) { stop(); }
         * }
         * return more();
         * \endcode
         * where report() notifies all registered model handlers.
         */
        bool solve(SharedContext &ctx, ResultHandler *onResult = 0);

        //! Prepares the solve algorithm for enumerating models.
        /*!
         * \pre The algorithm is not yet active.
         */
        void start(SharedContext &ctx, ResultHandler *onResult = 0);

        //! Stops the algorithms.
        void stop();

        //! Resets solving state and sticky messages like terminate.
        /*!
         * \note The function must be called between successive calls to solve().
         */
        virtual void resetSolve()        = 0;

        //! Prepares the algorithm for handling (asynchronous) calls to SolveAlgorithm::interrupt().
        virtual void enableInterrupts()  = 0;

        //! Tries to terminate the current solve process.
        /*!
         * \note If enableInterrupts() was not called, SolveAlgorithm::interrupt() may return false
         * to signal that (asynchronous) termination is not supported.
         */
        bool interrupt();

    protected:
        SolveAlgorithm(const SolveAlgorithm &);

        SolveAlgorithm &operator=(const SolveAlgorithm &);

        //! The actual solve algorithm.
        virtual bool doSolve(SharedContext &ctx) = 0;

        //! Shall return true if termination is supported, otherwise false.
        virtual bool doInterrupt()                                     = 0;

        virtual void doStart(SharedContext &ctx);

        virtual void doStop();

        bool reportResult(Solver &s) const;

        bool reportUnsat(Solver &s) const;

        bool reportNonDCO(Solver &s) const;

        SharedContext &ctx() const { return *ctx_; }

    private:
        bool attach(SharedContext &ctx, ResultHandler *onResult);

        void detach();

        SharedContext *ctx_;
        ResultHandler *onResult_;
        double time_;
        int last_;
    };
}

#endif //PLOG_SOLVE_ALGORITHM_H
