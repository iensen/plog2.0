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
using GroundPlog::Atom_t;
using Clingo::literal_t;

using GroundPlog::ATTID ;
using GroundPlog::ValueRep ;
using GroundPlog::AId ;

enum class ExternalSymbolType {
    None, Rule, Atom
};

class GroundPlogBackend;


class PlogGroundProgramBuilder:public GroundProgramObserver {
    struct GRule {
        std::vector<Clingo::atom_t> head;
        std::vector<Clingo::literal_t> body;
        bool isRegular();
        bool isRandom();
        bool isPrAtom();
        bool isAtomExternal();
        void setSymbolTable(std::vector<Clingo::Symbol> * symbols);
        void normalize();
    private:
        std::string getHeadAttrName();
        std::vector<Clingo::Symbol> * symbols;
        Clingo::Symbol getHeadSymbol();
        ExternalSymbolType getExternalSymbolType(Clingo::Symbol & hs);
        // move the externals in the body to the end
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
    void addAtomExternalToBackend(GRule &rule);
    unsigned insert(std::string value, std::unordered_map<std::string, unsigned> & dist);
    void insert(unsigned value, unsigned index, std::vector<unsigned> & dist);
    Atom_t getGroundPlogAtom(const Clingo::Symbol &s);
    std::vector<Lit_t>  getGroundPlogBody(const std::vector<literal_t> gbody);

    GroundPlogBackend& out;
    std::unordered_set<Clingo::Symbol> facts;
    std::vector<Clingo::Symbol> symbols;
    // a map from attribute terms to attributes
    std::vector<unsigned > attributes;

    std::unordered_map<std::string, ATTID > attids;
    std::unordered_map<std::string, unsigned > sortids;
    std::unordered_map<std::string, ValueRep > atids;
    std::unordered_map<std::string, unsigned> aids;

    std::unordered_map<AId, AId> a_range_sort;
    std::unordered_map<AId , std::vector<ValueRep > > sort_elems;
    std::unordered_map<ValueRep, std::string> term_str;

    // for optimization, store unique pointers to rule instead!
    std::vector<GRule> storedrules;

    std::tuple<ATTID , ValueRep, double > prAtomFromSymbol(const Clingo::Symbol &s);
    std::pair<ATTID, ValueRep > atomFromSymbol(const Clingo::Symbol &s);

    void registerAtomInBackend(unsigned int &atom_id);
    bool rulesPassedToBackend = false;


};



#endif //PLOG_GRPROGRAMOBS_H
