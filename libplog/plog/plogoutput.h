//
// Created by iensen on 9/16/16.
//

#ifndef PLOG_PLOGOUTPUT_H
#define PLOG_PLOGOUTPUT_H

#include<gringo/output/statement.hh>
#include<gringo/output/literal.hh>
#include<groundplog/program_types.h>
#include "plogcontrol.hh"
#include<vector>

using Gringo::Output::AbstractOutput;
using Gringo::Output::DomainData;
using GringoStatement = Gringo::Output::Statement;
using GroundPlog::Atom_t;
using GroundPlog::Lit_t;
using GroundPlog::ATTID ;
using GroundPlog::AId;

class GroundPlogBackend {
public:

    GroundPlogBackend(PlogControl& ctl):ctl_(ctl) {}
    void rule(Atom_t &head, const std::vector<Lit_t> &body, int ex_atom_id);
    void randomRule(std::pair<ATTID ,AId> head, const std::vector<Lit_t> &body, int ex_atom_id);
    void prAtom(const Atom_t &head, const std::vector<Lit_t> &body, double prob, int ex_atom_id);
    void query(const Lit_t &query);
    void atMap(std::vector<unsigned>);
    void sortElem(unsigned sort_id, unsigned sort_elem_id);
    void rangeSort(unsigned a_id, unsigned sort_id);
    void observation(unsigned att_id, unsigned val_id, bool positive);
    void action(unsigned att_id, unsigned val_id);
    void atomExternal(unsigned att_id, unsigned val_id, unsigned ex_atom_id);
    void registerLiteral(unsigned atom_id, unsigned att_id, unsigned val_id, bool neg);
    void registerDynRangeAtom(unsigned a_id, unsigned arg_id, unsigned att_id);
    void registerTrueAtId(unsigned true_id);
    void atttoat(unsigned attid, unsigned aid);

private:
    GroundPlog::Program* prg();
    PlogControl& ctl_;

};
#endif //PLOG_PLOGOUTPUT_H
