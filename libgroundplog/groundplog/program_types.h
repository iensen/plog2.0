//
// Created by iensen on 8/17/16.
//

#ifndef PLOG_PROGRAM_TYPES_H
#define PLOG_PROGRAM_TYPES_H
#include<groundplog/util/platform.h>
#include <assert.h>
#include<vector>
#include <unordered_set>

namespace GroundPlog {

    class Program;
    typedef uint32 ATTID;
    typedef uint32 ValueRep;
    typedef uint32 Var;
    typedef uint32 AId;

    struct Atom_t {
        ATTID attid;
        ValueRep valid;

        // implement equality operator:
        bool operator==(const Atom_t &other) const
        { return (attid == other.attid
                  && valid == other.valid);
        }
    };

    struct Dyn_Range_Atom {
        AId attribute;
        ValueRep argument;
        bool operator == (const Dyn_Range_Atom &other) const {
            return attribute == other.attribute && argument == other.argument;
        }
    };



    struct Lit_t {
        Lit_t(){};
        Lit_t(ATTID attid, ValueRep valid, bool defaultNeg, bool classicNeg):attid(attid), valid(valid),
                                                                             defaultNeg(defaultNeg),
                                                                             classicNeg(classicNeg){}
        ATTID attid;
        ValueRep valid;
        bool defaultNeg;
        bool classicNeg;
    };


    typedef uint64 Id_t;
      //! A variable is an integer in the range [0..varMax).

    struct Rule {
      virtual ~Rule();
    };

    struct RegularRule:public Rule {
        RegularRule(Atom_t head, const std::vector<Lit_t> &body) {
            this->head = head;
            this->body = body;
        }
        Atom_t head;
        std::vector<Lit_t> body;
        bool constructedFrom(const std::unordered_set<ATTID> &atts);
    };

    struct RandomRule:public Rule {
        RandomRule(std::pair<ATTID, AId> head, const std::vector<Lit_t> & body) {
            this->head = head;
            this->body = body;
        }
        std::pair<ATTID,AId>  head;
        std::vector<Lit_t> body;
        bool constructedFrom(const std::unordered_set<ATTID> &atts);
    };


    struct PrAtom {
        Atom_t head;
        std::vector<Lit_t> body;
        double prob;
        bool constructedFrom(const std::unordered_set<ATTID> &atts);

    };

    struct Observation {
        ATTID  attid;
        ValueRep  valid;
        bool positive;
    };


    struct Action {
        ATTID  attid;
        ValueRep  valid;
    };

}


// implement hash functions:
namespace std {
    using GroundPlog::Dyn_Range_Atom;
    using GroundPlog::Atom_t;
    using GroundPlog::ATTID ;
    using GroundPlog::ValueRep ;
    using GroundPlog::AId ;
    // implement hash for atoms to allow unordered maps from Atom_t:
    template <>
    struct hash<Atom_t>
    {
        size_t operator()(const Atom_t& a) const
        {
            // Compute individual hash values for two data members
            size_t hash1 = std::hash<ATTID >{}(a.attid);
            size_t hash2 = std::hash<ValueRep >{}(a.valid);
            // combine two hashes:
            // i am not sure if this combination actually avoids collisions, need to check:
            return hash1 ^ (hash2 << 1);
        }
    };

    // implement hash for dynamic range atoms:
    template <>
    struct hash<Dyn_Range_Atom>
    {
        size_t operator()(const Dyn_Range_Atom& a) const
        {
            // Compute individual hash values for two data members
            size_t hash1 = std::hash<AId >{}(a.attribute);
            size_t hash2 = std::hash<ValueRep >{}(a.argument);
            // combine two hashes:
            // i am not sure if this combination actually avoids collisions, need to check:
            return hash1 ^ (hash2 << 1);
        }
    };

}


#endif //PLOG_PROGRAM_TYPES_H
