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
using Clingo::literal_t;

using GroundPlog::AttId ;
using GroundPlog::ValueRep ;

class PlogGroundProgramBuilder:public GroundProgramObserver {
    struct GRule {
        std::vector<Clingo::atom_t> head;
        std::vector<Clingo::literal_t> body;
        bool isRegular();
        bool isRandom();
        bool isPrAtom();
        void setSymbolTable(std::vector<Clingo::Symbol> * symbols);
    private:
        std::string getHeadAttrName();
        std::vector<Clingo::Symbol> * symbols;
        Clingo::Symbol getHeadSymbol();
        bool isRuleExternalSymbol(Clingo::Symbol & hs);
      };
public:
    PlogGroundProgramBuilder(GroundPlogBackend &out);
private:
    virtual void output_atom(Clingo::Symbol symbol, atom_t atom) override;
    virtual void rule(bool, AtomSpan, LiteralSpan) override;
    virtual void end_step() override;

    void addAttributeMapToBackend();
    void addSortAtomToBackend(GRule &rule);
    void addObservationToBackend(const Clingo::Symbol &);
    void addActionToBackend(const Clingo::Symbol &);

    void addRuleToBackend(GRule &rule);
    void addRegularRuleToBackend(GRule &rule);
    void addQueryToBackend(Clingo::Symbol &);
    void addRandomRuleToBackend(GRule &rule);
    void addPrAtomToBackend(GRule &rule);
    unsigned insert(std::string value, std::unordered_map<std::string, unsigned> & dist);
    void insert(unsigned value, unsigned index, std::vector<unsigned> & dist);
    Atom_t getGroundPlogAtom(const Clingo::Symbol &s);
    std::vector<Lit_t>  getGroundPlogBody(const std::vector<literal_t> gbody);

    GroundPlogBackend& out;
    std::unordered_set<Clingo::Symbol> facts;
    std::vector<Clingo::Symbol> symbols;
    // a map from attribute terms to attributes
    std::vector<unsigned > attributes;

    std::unordered_map<std::string, AttId > attids;
    std::unordered_map<std::string, unsigned > sortids;
    std::unordered_map<std::string, ValueRep > atids;
    std::unordered_map<std::string, unsigned> aids;

    // for optimization, store unique pointers to rule instead!
    std::vector<GRule> storedrules;

    std::tuple<AttId , ValueRep, double > prAtomFromSymbol(const Clingo::Symbol &s);
};



#endif //PLOG_GRPROGRAMOBS_H
