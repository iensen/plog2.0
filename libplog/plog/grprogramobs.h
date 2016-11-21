//
// Created by iensen on 11/18/16.
//
#ifndef PLOG_GRPROGRAMOBS_H
#define PLOG_GRPROGRAMOBS_H

#include <clingo.hh>
#include <string>
#include <gringo/output/output.hh>
#include "plogoutput.h"
#include <map>
#include <utility>
#include <unordered_map>
#include <groundplog/program_types.h>



using Clingo::GroundProgramObserver;
using Clingo::AtomSpan ;
using Clingo::LiteralSpan ;
using Clingo::Symbol;
using Clingo::atom_t ;

using GroundPlog::AttId ;
using GroundPlog::ValueRep ;

class PlogGroundProgramBuilder:public GroundProgramObserver {
    struct GRule {
        std::vector<Clingo::atom_t> head;
        std::vector<Clingo::literal_t> body;
        bool isRandom();
        bool isQuery();
        bool isPrAtom();
    };
public:
    PlogGroundProgramBuilder(GroundPlogBackend &out);
private:
    virtual void output_atom(Clingo::Symbol symbol, atom_t atom) override;
    virtual void rule(bool, AtomSpan, LiteralSpan) override;
    virtual void end_step() override;


    void addRuleToBackend(GRule &rule);
    void addRegularRuleToBackend(GRule &rule);
    void addQueryToBackend(GRule &rule);
    void addRandomRuleToBackend(GRule &rule);
    void addPrAtomToBackend(GRule &rule);
    unsigned insert(std::string value, std::unordered_map<std::string, unsigned> & dist);
    Atom_t getGroundPlogAtom(Clingo::Symbol &s);


    GroundPlogBackend& out;

    std::unordered_set<Clingo::Symbol> facts;
    std::vector<Clingo::Symbol> symbols;
    std::unordered_map<std::string, AttId > attids;
    std::unordered_map<std::string, ValueRep > atids;


    // for optimization, store unique pointers to rule instead!
    std::vector<GRule> storedrules;
};


#endif //PLOG_GRPROGRAMOBS_H
