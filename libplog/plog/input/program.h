//
// Created by iensen on 9/16/16.
//

#ifndef FOO_H
#define FOO_H

#include <plog/programbuilder.h>
#include <plog/plogparser.h>
#include <gringo/ground/program.hh>
#include "statement.h"



    class Program {
    public:
        Program();

        Program(Program &&x);



        void add(UStm &&stm);

        void rewrite(Defines &defs, Logger &log);

        void check(Logger &log);

        void print(std::ostream &out) const;

        // here is the thing! this should return a Gringo - Kind of ground program ready to ground
        // to do it, we will need to convert current program to ASP program and call toGround There
        Gringo::Ground::Program toGround(Logger &log);

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
    };


#endif //PLOG_PROG_H
