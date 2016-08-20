//
// Created by iensen on 8/16/16.
//

#ifndef PLOG_SOLVER_STRATEGIES_H
#define PLOG_SOLVER_STRATEGIES_H


#include <groundplog/util/misc_types.h>
#include<vector>



namespace GroundPlog {
    class  SharedContext;
    class Solver;

//! Parameter-Object for configuring a solver.

    class DecisionHeuristic;
    struct SolverStrategies {

    };

    struct SolverParams : SolverStrategies  {

    };

    class ModelHandler {
    public:
        virtual ~ModelHandler();
        virtual bool onUnsat(const Solver&);
    };
    //! Parameters for a SharedContext object.
    struct ContextParams {
    };

    //! Interface for configuring a SharedContext object and its associated solvers.
    class Configuration {
    public:
        typedef SolverParams  SolverOpts;
        typedef ContextParams CtxOpts;
        virtual ~Configuration();
        //! Prepares this configuration for the usage in the given context.
        virtual void               prepare(SharedContext&)    = 0;
        //! Returns the options for the shared context.
        virtual const CtxOpts&     context()            const = 0;
        //! Returns the number of solver options in this config.
        virtual uint32             numSolver()          const = 0;
        //! Returns the solver options for the i'th solver to be attached to the SharedContext.
        virtual const SolverOpts&  solver(uint32 i)     const = 0;
        //! Returns the heuristic to be used in the i'th solver.
        /*!
         * The function is called in Solver::startInit().
         * \note The returned object is owned by the caller.
         */
        virtual DecisionHeuristic* heuristic(uint32 i)  const = 0;
        //! Returns the configuration with the given name or 0 if no such config exists.
        /*!
         * The default implementation returns this
         * if n is empty or one of "." or "/".
         * Otherwise, 0 is returned.
         */
        virtual Configuration*     config(const char* n);
    };

//! Base class for user-provided configurations.
    class UserConfiguration : public Configuration {
    public:
        virtual SolverOpts&     addSolver(uint32 i) = 0;
    };
//! Simple factory for decision heuristics.
    struct Heuristic_t {
        enum Type { Default = 0,None = 6 };
        typedef DecisionHeuristic* (*Creator)(Type t);
        static DecisionHeuristic* create(Type t);
    };

}

#endif //PLOG_SOLVER_STRATEGIES_H
