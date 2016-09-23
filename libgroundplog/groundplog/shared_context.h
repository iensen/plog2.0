//
// Created by iensen on 8/16/16.
//

#ifndef PLOG_SHARED_CONTEXT_H
#define PLOG_SHARED_CONTEXT_H


#include <groundplog/groundplogfwd.h>
#include <groundplog/literal.h>
#include <groundplog/solver_strategies.h>
#include <groundplog/dependency_graph.h>
#include <groundplog/program_types.h>


namespace GroundPlog {

    class EventHandler : public ResultHandler {
    public:
        explicit EventHandler();
        virtual ~EventHandler();
        bool setActive(Event::Subsystem sys);
        Event::Subsystem active() const;
        void dispatch(const Event& ev)               {  onEvent(ev); }
        virtual void onEvent(const Event& /* ev */)  {}
        virtual bool onResult(const Solver&, const double result) { return true; }
    private:
        EventHandler(const EventHandler&);
        EventHandler& operator=(const EventHandler&);
        uint16 sys_;
    };





    class SharedContext {
    public:
        typedef SingleOwnerPtr<PrgDepGraph>    SccGraph;
        typedef Configuration*                 ConfigPtr;
        enum ReportMode { report_default = 0u};
        typedef EventHandler*                  LogPtr;

        /*!
         * \name Configuration
         */

        //! Enables event reporting via the given event handler.
        void       setEventHandler(LogPtr r) { progress_ = r; }


        //@{
        //! Creates a new object for sharing variables and the binary and ternary implication graph.
        explicit SharedContext();
        ~SharedContext();
        //! Resets this object to the state after default construction.
        void       reset();

        //! Adds an additional solver to this object and returns it.
        Solver&    pushSolver();
        //! Configures the statistic object of attached solvers.
        /*!
         * The level determines the amount of extra statistics.
         * \see ExtendedStats
         * \see JumpStats
       */
        void       enableStats(uint32 level);
        //! Sets the configuration for this object and its attached solvers.
        /*!
         * \note If ownership is Ownership_t::Acquire, ownership of c is transferred.
         */
        void       setConfiguration(Configuration* c, Ownership_t::Type ownership);
        SccGraph   sccGraph;   /*!< Program dependency graph - only used for ASP-problems. */

        //! Returns the current configuration used in this object.
        ConfigPtr  configuration()      const { return config_.get(); }

        /*!
         * \name Problem introspection
         * Functions for querying information about the problem.
         */
        //@{
        //! Returns true unless the master has an unresolvable top-level conflict.
        bool       ok()                 const;
        //! Returns the master solver associated with this object.
        Solver*    solver()             const { return solver_;    }

        //! Returns the number of problem variables.
        /*!
         * \note The special sentinel-var 0 is not counted, i.e. numVars() returns
         * the number of problem-variables.
         * To iterate over all problem variables use a loop like:
         * \code
         * for (Var i = 1; i <= numVars(); ++i) {...}
         * \endcode
         */
        uint32     numAtts()            const { return static_cast<uint32>(varInfo_.size() - 1); }
        //! Returns true if var represents a valid variable in this problem.
        /*!
         * \note The range of valid variables is [1..numVars()]. The variable 0
         * is a special sentinel variable.
         */
        bool       validATT(ATTID att)    const { throw "not implemented yet"; }

        bool       marked(Literal p)    const {throw "not implemented yet";}

        VarInfo    varInfo(Var v)       const {return varInfo_[v];}
        //@}

        /*!
         * \name Problem setup
         * Functions for specifying the problem.
         * Problem specification is a four-stage process:
         * -# Add variables to the SharedContext object.
         * -# Call startAddConstraints().
         * -# Add problem constraints.
         * -# Call endInit() to finish the initialization process.
         * .
         * \note After endInit() was called, other solvers can be attached to this object.
         * \note In incremental setting, the process must be repeated for each incremental step.
         *
         * \note Problem specification is *not* thread-safe, i.e. during initialization no other thread shall
         * access the context.
         *
         * \note !frozen() is a precondition for all functions in this group!
         */
        //@{
        //! Unfreezes a frozen program and prepares it for updates.
        /*!
         * The function also triggers forgetting of volatile knowledge and removes
         * any auxiliary variables.
         * \see requestStepVar()
         * \see Solver::popAuxVar()
         */
        bool    unfreeze();


        ATTID     addAtt(){ return addAtts(1); }
        ATTID     addAtts(uint32 nVars);
        void    setAttEq(ATTID v, uint32 val) {throw  "not implemented yet"; }
        void    set(ATTID a,  uint32 val) { throw "not implemented yet"; }
        void    mark(Literal p)         { throw "not implemented yet"; }
        void    unmark(ATTID v)           { throw "not implemented yet"; }
        //! Eliminates the variable v from the problem.
        /*!
         * \pre v must not occur in any constraint and frozen(v) == false and value(v) == value_free
         */


        //! Prepares the master solver so that constraints can be added.
        /*!
         * Must be called to publish previously added variables to master solver
         * and before constraints over these variables can be added.
         * \return The master solver associated with this object.
         */

        //! A convenience method for adding facts to the master.
        bool    addUnary(Literal x);
        //! A convenience method for adding binary clauses.

        //! Finishes initialization of the master solver.
        /*!
         * The function must be called once before search is started. After endInit()
         * was called, previously added solvers can be attached to the
         * shared context and learnt constraints may be added to solver.
         * \param attachAll If true, also calls attach() for all solvers that were added to this object.
         * \return If the constraints are initially conflicting, false. Otherwise, true.
         * \note
         * The master solver can't recover from top-level conflicts, i.e. if endInit()
         * returned false, the solver is in an unusable state.
         * \post frozen()
         */
        bool    endInit(bool attachAll = false);
        //@}

        //! Attaches the solver with the given id to this object.
        /*!
         * \note It is safe to attach multiple solvers concurrently
         * but the master solver shall not change during the whole operation.
         *
         * \pre hasSolver(id)
         */
        bool     attach_solver();

        //! Detaches the solver with the given id from this object.
        /*!
         * The function removes any tentative constraints from s.
         * Shall be called once after search has stopped.
         * \note The function is concurrency-safe w.r.t to different solver objects,
         *       i.e. in a parallel search different solvers may call detach()
         *       concurrently.
         */
        void     detach_solver();



        //! Simplifies the problem constraints w.r.t the master's assignment.
        void     simplify(bool shuffle);


        //@}
    private:
        SharedContext(const SharedContext&);
        SharedContext& operator=(const SharedContext&);
        typedef SingleOwnerPtr<Configuration> Config;
        typedef std::vector<VarInfo>       VarVec;
        VarVec       varInfo_;       // varInfo[v] stores info about variable v
        Config       config_;        // active configuration
        LogPtr       progress_;      // event handler or 0 if not used
        Solver*    solver_;       // solvers associated with this context

    };



//@}
}
#endif //PLOG_SHARED_CONTEXT_H
