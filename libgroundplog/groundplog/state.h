//
// Created by iensen on 1/17/17.
//

#ifndef PLOG_STATE_H
#define PLOG_STATE_H

#include <groundplog/interpretation.h>
#include "dependency_graph.h"

// define hash function for pairs

template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
    template<typename S, typename T> struct hash<pair<S, T>>
    {
        inline size_t operator()(const pair<S, T> & v) const
        {
            size_t seed = 0;
            ::hash_combine(seed, v.first);
            ::hash_combine(seed, v.second);
            return seed;
        }
    };
}

namespace  GroundPlog {

    class DepGraph;
    class Interpretation;
    class State {
        Interpretation I;
        DepGraph* depGraph;
        Program* prg;

        std::vector<ATTID> RAT; // +
        std::vector<ATTID> DAT; // +
        std::vector<unsigned> DATLEVEL; //+

        std::vector<ATTID> RDYRAT; // +
        std::vector<unsigned> RDYRATLEVEL; //+


        std::vector<std::vector<ATTID> > randomDeps;
        std::vector<unsigned> depCounter;
        int currentLevel;


        // this will backtrack together with falsified/bodytruelits
        std::vector<unsigned > UNDECIDEDRULECOUNTER;

        // this will backtrack naturally
        std::vector<unsigned>prAtBodyTrueLitCounter;
        std::vector<unsigned>regRuleBodyTrueLitCounter;
        std::vector<unsigned>randomRuleBodyTrueLitCounter;

        std::vector<unsigned> undecidedDynRangeAttFor;


        std::vector<char>prAtBodyFalsified;
        std::vector<unsigned> prAtBodyFalsifiedTrail;
        std::vector<unsigned> prAtBodyFalsifiedTrailLevel;

        std::vector<char>regRuleBodyFalsified;
        std::vector<unsigned> regRuleBodyFalsifiedTrail;
        std::vector<unsigned> regRuleBodyFalsifiedTrailLevel;


        std::vector<char>randomRuleBodyFalsified;
        std::vector<unsigned> randomRuleBodyFalsifiedTrail;
        std::vector<unsigned> randomRuleBodyFalsifiedTrailLevel;


        // this will backtrack together with falsified arrays (once we backtrack the falsified, increase the counter of he head)!
        std::unordered_map<std::pair<ATTID ,ValueRep >, int> pvCounter;

        void initRandomDeps();
        std::unordered_set<ATTID> findDeps(ATTID id);

        template<typename Statement>
        void backTrackPositiveAssignment( std::vector<std::vector<unsigned > >&bodiesArray, Statement stmts[], ATTID attid);


    public:
        State() {};
        unsigned LastLevelUndecidedCount();
        void init(GroundPlog::DepGraph *dg, GroundPlog::Program *pr);
        void assignRandom(ATTID attid, ValueRep val);
        void assignNonRandom(ATTID attid, ValueRep val);
        ValueRep getValue(ATTID attid);
        const std::vector<ATTID>& getReadyAtts();
        std::vector<ATTID> getLastLevelDAT();
        void backTrackLevel();
        void increaseLevel();
        bool propagateAssignment(ATTID attid, ValueRep val, bool isimpossible);
        bool hasAssignmentToRandom();
        bool initClosure();
        bool propagateLastRandomAssignment();
        bool AtMost();
        void updateRandomRules(ATTID attid, ValueRep val, bool is_impossible);
        void updatePrAtoms(ATTID attid, ValueRep val, bool is_impossible);
        const Interpretation & getI() const;
        const std::vector<ATTID>& getRAT() const;
        const std::vector<ATTID>& getDAT() const;
        GroundPlog::Program * getProgram() const;
        DepGraph* getDepGraph() const;
        const std::vector<ATTID>&getRDYRAT() const;

        void initUndecidedRuleCounter();

        void initBodyTrueLitCounters();

        void initBodyFalsifiedFlags();

        void initPvCounter();

        void backTrackRandomAssignment();

        void backTrackPositiveAssignments();

        void backTrackImpossibleAssignments();

        void backTrackFalsifiedPrAtomBodies();

        void backTrackFalsifiedRandomRuleBodies();

        void backTrackFalsifiedRegularRuleBodies();

        void backTrackRDYrandomAttributeTerms();

        void initReadyRandomAttributeTerms();

        void initDynRangeDecidedAttCounter();

        void updateDynRangeCounters(ATTID attid);
    };
}
#endif //PLOG_STATE_H
