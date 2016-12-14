//
// Created by iensen on 8/17/16.
//

#ifndef PLOG_PROGRAM_H
#define PLOG_PROGRAM_H

#include "program_builder.h"
#include <groundplog/program_types.h>
#include <groundplog/rule_utils.h>
#include <clasp/util/misc_types.h>
#include<clasp/shared_context.h>
#include<utility>
#include <vector>

namespace GroundPlog {
    using Clasp::ConstString;

    template<typename T>
    using Range = Clasp::Range<T>;

    typedef std::pair<Id_t, ConstString>    ShowPair;

    class Program : public ProgramBuilder {
        std::vector<Rule> rules;
        std::vector<Observation> observations;
        std::vector<Action> actions;
        std::vector<RandomRule> randomrules;
        std::vector<PrAtom> pratoms;
        std::vector<int> ruleExternals;
        std::vector<int> randomRuleExternals;
        std::vector<std::vector<unsigned> > sort_elems;
        std::vector<unsigned > a_ranges;

        Lit_t query;


    public:
        Program();

        ~Program();


//! Options for the Asp-Preprocessor.
        struct PrepOptions {
        };

        //! Starts the definition of a logic program.
        Program &start(SharedContext &ctx, const PrepOptions &opts = PrepOptions()) {
            startProgram(ctx);
            setOptions(opts);
            return *this;
        }

        //! Sets preprocessing options.
        void setOptions(const PrepOptions &opts);


        //! Finishes the definition of the logic program (or its current increment).
        /*!
         * Applies program mutating operations issued in the current step and transforms
         * the new program into the solver's internal representation.
         *
         * \return false if the program is conflicting, true otherwise.
         *
         * \post
         *  - If true is returned, the program is considered to be "frozen" and calling
         *    program mutating functions is invalid until the next call to update().
         *  - If false is returned, the state of the object is undefined and start()
         *    and dispose() are the only remaining valid operations.
         *  .
         * \note The function is an alias for ProgramBuilder::endProgram().
         */
        bool end() { return endProgram(); }


        //! Disposes (parts of) the internal representation of the logic program.
        /*!
         * \param forceFullDispose If set to true, the whole program is disposed. Otherwise,
         *  only the rules (of the current step) are disposed but atoms and any incremental
         *  control data remain.
         */
        void dispose(bool forceFullDispose);

        //! Clones the program and adds it to the given ctx.
        /*
         * \pre The program is currently frozen.
         */
        bool clone(SharedContext &ctx);

        //@}

        /*!
         * \name Program mutating functions
         *
         * Functions in this group shall only be called if the program is currently not
         * frozen. That is, only between the call to start() (resp. update() if in
         * incremental setting) and end(). A std::logic_error is raised if this precondition is violated.
         *
         */
        //@{

        //! Adds a new atom to the program.
        /*!
         * \return The new atom's id.
         */
        Atom_t newAtom();






        //! Adds the given rule (or integrity constraint) to the program.
        /*!
         * \pre The the rule does not define an atom from a previous incremental step.
         *
         * Simplifies the given rule and adds it to the program if it
         * is neither tautological (e.g. a :- a) nor contradictory (e.g. a :- b, not b).
         * Atoms in the simplified rule that are not yet known are implicitly created.
         *
         * \throws RedefinitionError if the precondition is violated.
         * \note If the head of the simplified rule mentions an atom from a previous step,
         *       that atom shall either be frozen or false. In the former case,
         *       unfreeze() is implicitly called. In the latter case, the rule is interpreted
         *       as an integrity constraint.
         */


        // todo: rewrite this to use unique ptrs
        Program &addRule(Atom_t head, const std::vector<Lit_t> body, int ex_id);

        Program &addRandomRule(std::pair<AttId, AId > head, const std::vector<Lit_t> body, int ex_id);

        Program &addPratom(Atom_t head, const std::vector<Lit_t> body, double prob);

        Program &addQuery(Lit_t query);


        //@}

        /*!
         * \name Query functions
         *
         * Functions in this group are useful to query important information
         * once the program is frozen, i.e. after end() was called.
         * They do not throw exceptions.
         */
        //@{
        //! Returns the number of atoms in the logic program.
        uint32 numAtoms() const { return (uint32) atoms_.size() - 1; }

        //! Returns the number of bodies in the current (slice of the) logic program.
        uint32 numBodies() const { return (uint32) bodies_.size(); }


        //! Returns whether a is an atom in the (simplified) program.
        bool inProgram(Atom_t a) const;

        //! Returns whether a occurs in the head of a rule.
        bool isDefined(Atom_t a) const;

        //! Returns whether a is a fact.
        bool isFact(Atom_t a) const;
        //! Returns the internal solver literal that is associated with the given atom or condition.
        /*!
         * \pre id is the id of a valid atom literal or was previously returned by newCondition().
         * \note Untill end() is called, the function returns lit_false() for
         *       all atoms and conditions defined in the current step.
         * \note For an atom literal lit with Potassco::atom(lit) == a,
         *       getLiteral(Potassco::id(lit)) returns
         *        getLiteral(a), iff lit ==  a, or
         *       ~getLiteral(a), iff lit == -a.
         */
        Literal getLiteral(Id_t id) const;
        //@}

        /*!
         * \name Implementation functions
         * Low-level implementation functions. Use with care and only if you
         * know what you are doing!
         */
        //@{
        const PrepOptions &options() const { return opts_; }

        bool ok() const { return ProgramBuilder::ok(); }

        PrgAtom *getAtom(uint32 atomId) const { return atoms_[atomId]; }

        PrgHead *getHead(PrgEdge it) const {
            return  getAtom(it.node());
        }

        PrgNode *getSupp(PrgEdge it) const {
            return getBody(it.node());
        }

        PrgBody *getBody(Id_t bodyId) const { return bodies_[bodyId]; }


        bool validAtom(Id_t aId) const { return aId < (uint32) atoms_.size(); }

        bool validBody(Id_t bId) const { return bId < numBodies(); }


        Literal getDomLiteral(Atom_t a) const;

        bool isFact(PrgAtom *a) const;

        const char *findName(Atom_t x) const;

        Atom_t falseAtom();

        std::vector<Id_t> &getSupportedBodies(bool sorted);

        uint32 update(PrgBody *b, uint32 oldHash, uint32 newHash);

        bool assignValue(PrgAtom *a, ValueRep v, PrgEdge reason);

        bool assignValue(PrgHead *h, ValueRep v, PrgEdge reason);


        bool propagate() {throw "not implmenented"; }


        // ------------------------------------------------------------------------
        // ------------------------------------------------------------------------
        //@}
        void addAttributeMap(std::vector<unsigned int> vector);

        void registerRandomRuleExternal(int i);

        void registerRuleExternal(int i);

        void addSortElem(unsigned int i, unsigned int i1);

        void addAtRangeSort(unsigned int a_id, unsigned int sort_id);

        void addObservation(unsigned int att_id, unsigned int val_id, bool positive);

        void addAction(unsigned int att_id, unsigned int val_id);

    private:
        Program(const Program &);

        Program &operator=(const Program &);


        typedef std::vector<RuleBuilder*> RuleList;
        typedef Range<uint32>                  AttRange;
        // ------------------------------------------------------------------------
        // virtual overrides
        bool doStartProgram();

        bool doUpdateProgram();

        bool doEndProgram();

        void doGetAssumptions(std::vector<Literal>  &out) const;

        AttId startAtom()       const { return input_.lo; }
        // ------------------------------------------------------------------------
        // Program definition
        bool isNew(AttId attId) const { return attId >= startAtom(); }

        PrgAtom *resize(Atom_t atomId);

        PrgAtom *setExternal(Atom_t atomId, ValueRep v);



        void addFact(const Atom_t head);


        PrgBody *getBodyFor(const Rule &r, bool addDeps = true);

        PrgBody *getTrueBody();


        PrgBody *assignBodyFor(const Rule &r, EdgeType x, bool strongSimp);
        // ------------------------------------------------------------------------
        void deleteAtoms(uint32 start);


        ValueRep litVal(const PrgAtom *a, bool pos) const;


        AttRange   input_;       // input attribute terms of current step
        RuleBuilder rule_;        // temporary: active rule
        std::vector<PrgBody*> bodies_;      // all bodies
        std::vector<PrgAtom*> atoms_;       // all atoms
        std::vector<Atom_t> heads_;// all (head) disjunctions
        RuleList extended_;    // extended rules to be translated
        std::vector<ShowPair> show_;        // shown atoms/conditions
        std::vector<Atom_t> propQ_;       // assigned atoms
        PrepOptions opts_;
        std::vector<unsigned int> attmap;// a map frpm attribute terms to corresponding attributes in the program


    };
}
#endif //PLOG_PROGRAM_H
