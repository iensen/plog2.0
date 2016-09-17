//
// Created by iensen on 9/16/16.
//

#ifndef PLOG_PLOGOUTPUT_H
#define PLOG_PLOGOUTPUT_H

#include<gringo/output/statement.hh>
#include<gringo/output/literal.hh>
#include "plogcontrol.hh"

using Gringo::Output::AbstractOutput;
using Gringo::Output::DomainData;
using GringoStatement = Gringo::Output::Statement;

class PlogOutput:public AbstractOutput {
public:
    PlogOutput(PlogControl& ctl):ctl_(ctl) {}
    void output(DomainData &data, GringoStatement &stm) override;

private:
    PlogControl& ctl_;

};
#endif //PLOG_PLOGOUTPUT_H
