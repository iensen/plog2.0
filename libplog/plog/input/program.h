//
// Created by iensen on 9/16/16.
//

#ifndef FOO_H
#define FOO_H
#include<clingo.hh>
#include <gringo/input/program.hh>
#include "statement.h"


namespace Plog {

    class Program {
    public:
        Program();

        Program(Program &&x);

        // temporary workaround for computing probability using naive algorithm
        std::vector<Clingo::AST::Term>  getAttributeRangeElements(const std::string& range);

        void add(USortDef sDef);

        void add(UAttDecl sDef);

        void add(UStm &&stm);

        void rewrite(Defines &defs, Logger &log);

        void check(Logger &log);

        void print(std::ostream &out) const;

        Gringo::Input::Program toGringo();

        void loadToControl(Clingo::Control &ctl, AlgorithmKind algo);

        ~Program();

    private:
        void rewriteDots();

        void rewriteArithmetics();

        void unpool();

        unsigned auxNames_ = 0;
        //Ground::LocSet        locs_;
        //Ground::SigSet        sigs_;
        //BlockMap              blocks_;
        //Block                *current_;
        //Projections           project_;
        UStmVec stms_;
        USortDefVec sortdefs_;
        UAttDeclVec attdecls_;

    };
}


#endif //PLOG_PROG_H
