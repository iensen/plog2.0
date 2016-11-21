//
// Created by iensen on 11/18/16.
//

#include<clingo.hh>
#include<gringo/output/output.hh>
#include "plogoutput.h"

using Clingo::GroundProgramObserver;
using Clingo::AtomSpan ;
using Clingo::LiteralSpan ;
using Clingo::Symbol;
using Clingo::atom_t ;

#ifndef PLOG_GRPROGRAMOBS_H
#define PLOG_GRPROGRAMOBS_H

class PlogGroundProgramBuilder:public GroundProgramObserver {
public:
    PlogGroundProgramBuilder(GroundPlogBackend &out);
private:
    virtual void output_atom(Clingo::Symbol symbol, atom_t atom) override;
    virtual void rule(bool, AtomSpan, LiteralSpan) override;
    GroundPlogBackend& out;

};


#endif //PLOG_GRPROGRAMOBS_H
