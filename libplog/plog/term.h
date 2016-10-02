//
// Created by iensen on 9/21/16.
//

#ifndef PLOG_TERMZ_H
#define PLOG_TERMZ_H

#include <bits/unique_ptr.h>
#include <gringo/term.hh>
#include "plogparser.h"
#include<gringo/symbol.hh>
#include<gringo/locatable.hh>
#include<groundplog/logger.h>

using Location = Gringo::Location;
using Gringo::String;
using Logger = Plog::Logger;
using Term = Gringo::Term;
using UTerm = Gringo::UTerm ;

class Defines:public Gringo::Defines {
public:
    //! Add a define.
    //! Default defintions will not overwrite existing definitions and can be overwritten by other defines.
    void add(Location const &loc, String name, UTerm &&value, bool defaultDef, Logger &log);
    //! Evaluates layered definitions and checks for cycles.
    void init(Logger &log);
};


#endif //PLOG_TERM_H
