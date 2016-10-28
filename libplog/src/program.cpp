//
// Created by iensen on 9/16/16.
//


#include <plog/input/program.h>
#include <plog/ploggrammar.tab.hh>


Program::Program() {

}

Program::Program(Program &&x) {
    throw "not implemented yet";
}

void Program::add(USortDef sDef) {
    sortdefs_.emplace_back(std::move(sDef));
}

void Program::add(UAttDecl sDef) {
    attdecls_.emplace_back(std::move(sDef));
}


void Program::add(UStm &&stm) {
    stms_.emplace_back(std::move(stm));
}

void Program::rewrite(Defines &defs, Logger &log) {
    printf("REWRITING IS NOT IMPLEMENTED YET\n");
}

void Program::check(Logger &log) {
    printf("CHECKING IS NOT IMPLEMENTED YET\n");
}

void Program::print(std::ostream &out) const {
    throw "not implemented yet";
}

Program::~Program() {
    throw "not implemented yet";
}

void Program::rewriteDots() {
    throw "not implemented yet";
}

void Program::rewriteArithmetics() {
    throw "not implemented yet";
}

void Program::unpool() {
    throw "not implemented yet";
}

Gringo::Input::Program Program::toGringo() {
    // create a program
    Gringo::Input::Program prg;
   // Location loc(filename().c_str(), 1, 1, filename().c_str(), 1, 1);
   // IdVecUid params = pb_.idvec();
   // for (auto &x : data().second.second) { params = pb_.idvec(params, x.first, x.second); }
    //std::cout <<"BLOCK";
    //std::cout << data().second.first;
    //pb_.block(loc, data().second.first, params);
    prg.begin(DefaultLocation(),String("base"),{});
//    Symbol::createId(String("hz"));
    for(const UStm &stm: stms_)
 //       if (stm->getType() == StatementType::QUERY || stm->getType() == StatementType::PR_ATOM)
        prg.add(stm->toGringo());
    // create dummy defines and logger
    Gringo::Defines defs;
    Gringo::Logger log;
    prg.rewrite(defs,log);
    return prg;
}



