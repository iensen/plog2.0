//
// Created by iensen on 8/19/16.
//

#ifndef PLOG_SOLVER_TYPES_H
#define PLOG_SOLVER_TYPES_H
//! Stores assignment related information.
/*!
 * For each variable v, the class stores
 *  - v's current value (value_free if unassigned)
 *  - the decision level on which v was assign (only valid if value(v) != value_free)
 *  - the reason why v is in the assignment (only valid if value(v) != value_free)
 *  - (optionally) some additional data associated with the reason
 *  .
 * Furthermore, the class stores the sequences of assignments as a set of
 * true literals in its trail-member.
 */

#include<groundplog/program_types.h>


namespace GroundPlog {

    typedef uint32 ValueRep;           /**< Type of the three value-literals. */
    typedef uint32 Var;
    const ValueRep value_free   = 0;  /**< Value used for variables that are unassigned. */
    class Assignment {
    public:
        typedef std::vector<uint32> AssignVec;
        typedef std::vector<uint32> LevelVec;
        typedef std::vector<uint32> TrailVec;
        Assignment() { }

        //! Number of variables in the assignment.
        uint32 numVars() const { return (uint32) assign_.size(); }

        //! Returns v's value
        ValueRep value(Var v) const { return assign_[v]; }

        //! Returns the decision level on which v was assigned if value(v) != value_free.
        uint32 level(Var v) const { return level_[v]; }

        void reserve(uint32 n) {
            assign_.reserve(n);
        }

        //! Resize to nv variables.
        void resize(uint32 nv) {
            assign_.resize(nv);
        }

        //! Adds a var to assignment - initially the new var is unassigned.
        uint32 addVar() {
            assign_.push_back(0);;
            level_.push_back(0);
            return numVars() - 1;
        }
        //! Assigns p.var() on level lev to the value that makes p true and stores x as reason for the assignment.
        /*!
         * \return true if the assignment is consistent. False, otherwise.
         * \post If true is returned, p is in trail. Otherwise, ~p is.
         */
        bool assign(ATTID atid, uint32 lev, ValueRep val) {
                assign_[atid] = val;
                level_[atid] = lev;
                trail.push_back(atid);
                return true;
        }
        //! Undos all assignments in the range trail[first, last).
        /*!
         * \param first First assignment to be undone.
         * \param save  If true, previous assignment of a var is saved before it is undone.
         */
        void undoLastLevelTrail() {
            throw "not implemented yet";
        }

        /*!
         * \name Implementation functions
         * Low-level implementation functions. Use with care and only if you
         * know what you are doing!
         */
        //@{

        void setValue(Var v, ValueRep val) {
            assign_[v] = val;
        }

        void copyAssignment(Assignment &o) const { o.assign_ = assign_; }

        void clear(Var v) { assign_[v] = 0; }

        //@}
    private:

        Assignment(const Assignment &);

        Assignment &operator=(const Assignment &);


        AssignVec assign_;
        LevelVec level_;
        TrailVec trail;
    };
}


#endif //PLOG_SOLVER_TYPES_H
