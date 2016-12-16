//
// Created by iensen on 8/16/16.
//

#ifndef PLOG_SOLVER_H
#define PLOG_SOLVER_H

#include <groundplog/solver_strategies.h>
#include <groundplog/solver_types.h>

namespace GroundPlog {

    struct DLevel {
        int start_trail_id, end_trail_id;
    };


    class Solver {
	public:
        typedef SingleOwnerPtr<DecisionHeuristic> HeuristicPtr;
    private:
		/*!
         * \name Construction/Destruction/Setup
         */
		//@{
		friend class SharedContext;

		//! Creates an empty solver object with all strategies set to their default value.
		Solver(SharedContext *ctx);

		//! Destroys the solver object and all contained constraints.
		~Solver();

		//! Resets a solver object to the state it had after construction.
		void reset();

		void resetConfig();

		void startInit(uint32 constraintGuess, const SolverParams &params);

		void updateVars();

		bool endInit();

		bool endStep(uint32 top, const SolverParams &params);
		//@}
	public:

		//! Returns a pointer to the shared context object of this solver.
		const SharedContext *sharedContext() const { return shared_; }

		DecisionHeuristic *heuristic() const { return heuristic_.get(); }

        uint32   numFreeRandomVars() const;


        //! Removes any implications made between the top-level and the root-level.
		/*!
         * The function also resets the current backtrack-level and re-assigns learnt facts.
         * \note
         *   Equivalent to popRootLevel(rootLevel()) followed by simplify().
         */
		bool clearAssumptions();

		//! Sets the literal p to true and schedules p for propagation.
		/*!
         * Setting a literal p to true means assigning the appropriate value to
         * p's variable. That is: value_false if p is a negative literal and value_true
         * if p is a positive literal.
         * \param p The literal that should become true.
         * \param a The reason for the literal to become true or 0 if no reason exists.
         *
         * \return
         *  - false if p is already false
         *  - otherwise true.
         *
         * \pre hasConflict() == false
         * \pre a.isNull() == false || decisionLevel() <= rootLevel() || searchMode() == no_learning
         * \post
         *  p.var() == trueValue(p) || p.var() == falseValue(p) && hasConflict() == true
         *
         * \note if setting p to true leads to a conflict, the nogood that caused the
         * conflict can be requested using the conflict() function.
         */
		void force(ATTID  id, ValueRep val) {

             assign_.assign(id,decisionLevel(),val);
        }


		bool     hasConflict()          const { return !conflict_.empty(); }


		//! Assigns p at dl because of r.
		/*!
         * \pre dl <= decisionLevel()
         * \note
         *   If dl < ul = max(rootLevel(), backtrackLevel()), p is actually assigned
         *   at ul but the solver stores enough information to reassign
         *   p on backtracking.
         */

		//! Assumes the literal p if possible.
		/*!
         * If p is currently unassigned, sets p to true and starts a new decision level.
         * \pre validVar(p.var()) == true
         * \param p The literal to assume.
         * \return !isFalse(p)
         */
		bool assume(const Literal &p);

		//! Selects and assumes the next branching literal by calling the installed decision heuristic.
		/*!
         * \pre queueSize() == 0
         * \note The next decision literal will be selected randomly with probability f.
         * \return
         *  - true if the assignment is not total and a literal was assumed (or forced).
         *  - false otherwise
         *  .
         * \see DecisionHeuristic
         */
		bool decideNextBranch(double f = 0.0);

		//! Sets a conflict that forces the solver to terminate its search.
		/*!
         * \pre  !hasConflict()
         * \post hasConflict()
         *
         * \note
         *   To prevent the solver from resolving the stop conflict, the
         *   function sets the root level to the current decision level.
         *   Call clearStopConflict() to remove the conflict and to restore
         *   the previous root-level.
         */
		void setStopConflict();



		//! Resolves the active conflict using the selected strategy.
		/*!
         * If searchMode() is set to learning, resolveConflict implements
         * First-UIP learning and backjumping. Otherwise, it simply applies
         * chronological backtracking.
         * \pre hasConflict()
         * \return
         *  - true if the conflict was successfully resolved
         *  - false otherwise
         * \note
         *  If decisionLevel() == rootLevel() false is returned.
         */
		bool resolveConflict();

		//! Backtracks the last decision and updates the backtrack-level if necessary.
		/*!
         * \return
         *  - true if backtracking was possible
         *  - false if decisionLevel() == rootLevel()
         */
		bool backtrack();


		//! Returns whether undoUntil(decisionLevel()-1) is valid and would remove decisionLevel().
		bool isUndoLevel() const;

		//@}

		/*!
         * \name state inspection
         * Functions for inspecting the state of the solver & search.
         * \note validVar(v) is a precondition for all functions that take a variable as
         * parameter.
         */
		//@{


		//! Returns the value of v w.r.t the current assignment.
		ValueRep value(Var v) const {
			return assign_.value(v);
		}

		//! Returns the value of v w.r.t the top level.
		ValueRep topValue(Var v) const { return level(v) == 0 ? value(v) : value_free; }


		//! Returns true if p is true w.r.t the current assignment.
		bool isTrue(Literal p) const {
			throw "not implemented";
		}

		//! Returns true if p is false w.r.t the current assignment.
		bool isFalse(Literal p) const {
            throw "not implemented";
		}
		//! Returns the literal of v being true in the current assignment.
		/*!
         * \pre v is assigned a value in the current assignment
         */
		//! Returns the decision level on which v was assigned.
		/*!
         * \note The returned value is only meaningful if value(v) != value_free.
         */
		uint32 level(Var v) const {
			return assign_.level(v);
		}
		//! Returns true if v is currently marked as seen.
		/*!
         * Note: variables assigned on level 0 are always marked.
         */
		//! Returns the current decision level.
		uint32 decisionLevel() const { return (uint32) levels_.size(); }



		const Assignment &assignment() const { return assign_; }



		void setHeuristic(DecisionHeuristic *h, Ownership_t::Type own);

		//@}
	private:

		private:

		void undoLevel();
        std::vector<DLevel>    levels_;      // information (e.g. position in trail) on each decision level
        std::vector<Literal>            conflict_;    // conflict-literals for later analysis
        SharedContext *shared_;      // initialized by master thread - otherwise read-only!
		HeuristicPtr heuristic_;   // active decision heuristic
		Assignment assign_;      // assignment.
	};


    class DecisionHeuristic {
    public:
        DecisionHeuristic() {}
        virtual ~DecisionHeuristic();
        /*!
         * Called once after all problem variables are known to the solver.
         * The default-implementation is a noop.
         * \param s The solver in which this heuristic is used.
         */
        virtual void startInit(const Solver& /* s */) {}

        /*!
         * Called once after all problem constraints are known to the solver
         * and the problem was simplified.
         * The default-implementation is a noop.
         * \param s The solver in which this heuristic is used.
         */
        virtual void endInit(Solver& /* s */) { }

        //! Called once if s switches to a different heuristic.
        virtual void detach(Solver& /* s */) {}


        /*!
         * Called if the state of one or more variables changed.
         * A state change is one of:
         *   - A previously eliminated variable is resurrected.
         *   - A new aux variable was added.
         *   - An aux variable was removed.
         *   .
         * \param s Solver in which the state change occurred.
         * \param v The first variable affected by the change.
         * \param n The range of variables affected, i.e. [v, v+n).
         * \note Use s.validVar(v) and s.auxVar(v) to determine the reason for the update.
         */
        virtual void updateVar(const Solver& /* s */, Var /* v */, uint32 /* n */) = 0;

        /*!
         * Called whenever the solver backracks.
         * Literals in the range [s.trail()[st], s.trail().size()) are subject to backtracking.
         * The default-implementation is a noop.
         * \param s The solver that is about to backtrack.
         * \param st Position in the trail of the first literal that will be backtracked.
         */
        virtual void undoUntil(const Solver& /* s */, std::vector<Literal>::size_type /* st */) {}




        /*!
         * Called whenever the solver must pick a new variable to branch on.
         * \param s The solver that needs a new decision variable.
         * \return
         *  - true  : if the decision heuristic assumed a literal
         *  - false : if no decision could be made because assignment is total or there is a conflict
         *  .
         * \post
         * If true is returned, the heuristic has asserted a literal.
         */
        //! Implements the actual selection process.
        /*!
         * \pre s.numFreeVars() > 0, i.e. there is at least one variable to branch on.
         * \return
         *  - a literal that is currently free or
         *  - a sentinel literal. In that case, the heuristic shall have asserted a literal!
         */
        virtual ATTID select(Solver& /* s */) = 0;


    private:
        DecisionHeuristic(const DecisionHeuristic&);
        DecisionHeuristic& operator=(const DecisionHeuristic&);
    };



}

#endif //PLOG_SOLVER_H
