//
// Created by iensen on 8/17/16.
//

#ifndef PLOG_PROGRAM_H
#define PLOG_PROGRAM_H

#include <groundplog/program_types.h>
#include <groundplog/rule_utils.h>
#include <clasp/util/misc_types.h>
#include<clasp/shared_context.h>
#include<utility>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <clingo.h>
#include "interpretation.h"
#include<groundplog/state.h>

namespace GroundPlog {
    using Clasp::ConstString;

    template<typename T>
    using Range = Clasp::Range<T>;

    typedef std::pair<Id_t, ConstString> ShowPair;

    class Program {
        friend State;

        ValueRep TRUE_ID;

    public:
        std::vector<RegularRule> rules;
        std::vector<Observation> observations;
        std::vector<Action> actions;
        std::vector<RandomRule> randomrules;
        std::vector<PrAtom> pratoms;
        std::vector<int> ruleExternals;
        std::vector<int> randomRuleExternals;
        std::vector<int> prAtomExternals;
        std::vector<std::vector<unsigned> > sort_elems;
        std::vector<unsigned> a_ranges;
        Lit_t query;
        std::unordered_map<Atom_t, unsigned> atom_to_external;
        std::unordered_map<clingo_atom_t, Lit_t> clingo_to_plog_lit;
        std::unordered_map<Dyn_Range_Atom, ATTID> dynRangeAtt;
        std::unordered_map<ATTID, AId> atfromatt;
        std::vector<std::unordered_set<ValueRep> > val_candidates;
        std::vector<std::vector<ValueRep> > val_candidates_vects;

        size_t att_count;

        Program();

        ~Program();


//! Options for the Asp-Preprocessor.
        struct PrepOptions {
        };

        //! Starts the definition of a logic program.
        Program &start(const PrepOptions &opts = PrepOptions()) {
            setOptions(opts);
            return *this;
        }

        //! Sets preprocessing options.
        void setOptions(const PrepOptions &opts);

        //! Disposes (parts of) the internal representation of the logic program.
        /*!
         * \param forceFullDispose If set to true, the whole program is disposed. Otherwise,
         *  only the rules (of the current step) are disposed but atoms and any incremental
         *  control data remain.
         */
        void dispose(bool forceFullDispose);

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


        // todo: rewrite this to use unique ptrs
        Program &addRule(Atom_t head, const std::vector<Lit_t> body, int ex_id);

        Program &addRandomRule(std::pair<ATTID, AId> head, const std::vector<Lit_t> body, int ex_id);

        Program &addPratom(Atom_t head, const std::vector<Lit_t> body, double prob, int ex_id);

        Program &addQuery(Lit_t query);



        //@}

        /*!
         * \name Implementation functions
         * Low-level implementation functions. Use with care and only if you
         * know what you are doing!
         */
        //@{
        const PrepOptions &options() const { return opts_; }


        // ------------------------------------------------------------------------
        // ------------------------------------------------------------------------
        //@}
        void addAttributeMap(std::vector<unsigned int> vector);

        void addSortElem(unsigned int i, unsigned int i1);

        void addAtRangeSort(unsigned int a_id, unsigned int sort_id);

        void addObservation(unsigned int att_id, unsigned int val_id, bool positive);

        void addAction(unsigned int att_id, unsigned int val_id);

        void fill_vall_candidates();

        void finalize();

        // checking properties of a progeam:
        bool isRandom(ATTID attid);

        size_t getAttValuesCount(unsigned int attid);
        //std::unordered_set<ValueRep> getAttValues(unsigned int attid);

        std::unordered_set<ATTID> getRandomAttributeTerms();

        std::unordered_set<ATTID> getNonRandomAttributeTerms();

        std::unordered_set<unsigned> getExternalsForSubprogramConstructedFrom(const std::vector<ATTID> &atts);

        std::unordered_set<unsigned> getExternalsForAtomsFrom(const Interpretation &i) const;

        std::vector<std::vector<unsigned> > prAtBodies;
        std::vector<std::vector<unsigned> > regularRuleBodies;
        std::vector<std::vector<unsigned> > randomRuleBodies;
        std::vector<std::vector<unsigned> > attRules;
        std::vector<std::vector<unsigned> > attRandomRules;

        std::vector<std::vector<unsigned> > dynRangeAttFor;
        std::vector<std::unordered_set<ATTID>> randomRulesRangeAtts;

        std::vector<char> isRandomAtt;

        void addAtomExternal(unsigned int att_id, unsigned int val_id, unsigned int ex_atom_id);

        void registerLiteral(unsigned int att_id, unsigned int val_id, bool pos, unsigned clingo_at_id);

        double Probability(const Interpretation &I);

        void registerDynRangeAtom(unsigned int a_id, unsigned int arg_id, unsigned int att_id);

        void registerTrueAtId(unsigned int true_id);

        std::unordered_set<ValueRep> getPossibleValuesFor(ATTID attid, const Interpretation &interpretation);

        void storeatttoatmap(unsigned int attid, unsigned int aid);

        void registerTotalAttNum(size_t att_count);

    private:
        Program(const Program &);

        Program &operator=(const Program &);


        typedef std::vector<RuleBuilder *> RuleList;
        typedef Range<uint32> AttRange;

        PrepOptions opts_;
        std::vector<unsigned int> attmap;// a map frpm attribute terms to corresponding attributes in the program

        bool isReady(ATTID attid, const Interpretation &I);

        bool isActive(ATTID attid, const Interpretation &I);

        bool isDisabled(ATTID attid, const Interpretation &I);

        Rule *findUniqueActiveRuleFor(ATTID attid, const Interpretation &I);


        void build_att_occur_map();

        void fill_is_random_map();

        void build_random_rule_ranges_map();

        void fill_val_candidates_vects();

        void rewrite_att_vals();

        ValueRep getRewrittenValue(ATTID attid, ValueRep oldval);

        void sort_regular_rules();
    };
}
#endif //PLOG_PROGRAM_H
