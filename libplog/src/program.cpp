//
// Created by iensen on 9/16/16.
//


#include <plog/input/program.h>
#include <plog/ploggrammar.tab.hh>
#include<plog/input/utils.h>
#include<plog/input/sortdefinition.h>
namespace Plog {
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
        //printf("REWRITING IS NOT IMPLEMENTED YET\n");
    }

    void Program::check(Logger &log) {
        //printf("CHECKING IS NOT IMPLEMENTED YET\n");
    }

    void Program::print(std::ostream &out) const {
        throw "not implemented yet";
    }

    Program::~Program() {

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


    void Program::loadToControl(Clingo::Control &ctl) {
        auto b = ctl.builder();
        Clingo::Location loc("<test>", "<test>", 1, 1, 1, 1);
        b.add({loc, Clingo::AST::Program{"base", {}}});
        // add program rules:
        for (const UStm &stm: stms_) {
            //       if (stm->getType() == StatementType::QUERY || stm->getType() == StatementType::PR_ATOM)
            auto rules = stm->toGringoAST(attdecls_, sortdefs_);
            for (const auto &rule: rules) {
                //std::cout << rule << std::endl;
                b.add(rule);
            }
        }

        //add sorts:
        for (const USortDef &sortDef:sortdefs_) {
            String sortName = sortDef->getSortName();
            std::vector<Clingo::AST::Term> instances = sortDef->getSortExpr()->generate(sortdefs_);
            for (const Clingo::AST::Term &term:instances) {
                Clingo::AST::Literal hlit = Statement::make_lit(concat('_', sortName), {term});
                Clingo::AST::Rule f_r{{loc, hlit},
                                      {}};
                //std::cout << f_r << std::endl;
                b.add({defaultLoc, f_r});
            }
        }

        //add axioms:

    }

}

