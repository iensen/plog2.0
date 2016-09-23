//
// Created by iensen on 9/6/16.
//

#ifndef PLOG_PROGRAMXBUILDER_H
#define PLOG_PROGRAMXBUILDER_H

#include <string>
#include <gringo/locatable.hh>
#include <gringo/output/output.hh>
#include <plog/term.h>


using Location = Gringo::Location;
using IdVec = std::vector<std::pair<Location, std::string>>;

class Program;
class Defines;

class NonGroundProgramBuilder {
public:
    NonGroundProgramBuilder(Program &prg, Defines &defs);
private:
    Program            &prg_;
    Defines            &defs_;
};


#endif //PLOG_PROGRAMXBUILDER_H