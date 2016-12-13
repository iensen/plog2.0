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
using GroundPlog::AttId ;


class GroundPlogBackend {
public:

    GroundPlogBackend(PlogControl& ctl):ctl_(ctl) {}
    void rule(Atom_t &head, const std::vector<Lit_t> &body);
    void randomRule(std::vector<std::pair<Atom_t,AttId>> head, const std::vector<Lit_t> &body);
    void prAtom(const Atom_t &head, const std::vector<Lit_t> &body, double prob);
    void query(const Lit_t &query);

private:
    GroundPlog::Program* prg();
    PlogControl& ctl_;

};
#endif //PLOG_PLOGOUTPUT_H
