//
// Created by iensen on 9/6/16.
//

#ifndef PLOG_PROGRAMXBUILDER_H
#define PLOG_PROGRAMXBUILDER_H

#include <string>
#include <gringo/locatable.hh>
#include <gringo/output/output.hh>
#include <plog/term.h>
#include<gringo/indexed.hh>
#include<gringo/symbol.hh>

using String = Gringo::String;

template <class T, class R = unsigned>
using Indexed = Gringo::Indexed<T,R>;

using Location = Gringo::Location;
using IdVec = std::vector<std::pair<Location, String>>;

class Program;
class Defines;
enum IdVecUid           : unsigned { };


class NonGroundProgramBuilder {
public:
    NonGroundProgramBuilder(Program &prg, Defines &defs);
    using IdVecs           = Indexed<IdVec, IdVecUid>;
    IdVecUid idvec(IdVecUid uid, Location const &loc, String id);
    IdVecUid idvec();
  //  void block(Location const &loc, String name, IdVecUid args);
private:
    Program            &prg_;
    Defines            &defs_;
    IdVecs              idvecs_;

};


#endif //PLOG_PROGRAMXBUILDER_H