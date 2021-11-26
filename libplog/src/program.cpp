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

    // temporary workaround for computing probability using naive algorithm
    std::vector<Clingo::AST::Term>  Program::getAttributeRangeElements(const std::string& attribute) const {
            for(const UAttDecl& attDecl : attdecls_) {
                if(attDecl->attname.c_str() == attribute ) {
                    return attDecl->se->generate(sortdefs_);
                }
            }
            assert(false);
    }

    size_t Program::getAttributeRangeElementsCount(const std::string &attribute) const {
        auto it = attributeRangeCountCache.find(attribute);
        if (it != attributeRangeCountCache.end()) {
            return it->second;
        }
        for (const UAttDecl &attDecl : attdecls_) {
            if (attDecl->attname.c_str() == attribute) {
                return attributeRangeCountCache[attribute] = attDecl->se->generate(sortdefs_).size();
            }
        }
        assert(false);
    }

    void Program::loadToControl(Clingo::Control &ctl, SolvingMode solvingMode) {
        auto b = ctl.builder();
        Clingo::Location loc("<test>", "<test>", 1, 1, 1, 1);
        b.add({loc, Clingo::AST::Program{"base", {}}});
        // add program rules:
        for (const UStm &stm: stms_) {
            auto rules = stm->toGringoAST(attdecls_, sortdefs_, solvingMode);
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
        // 1. The same attribute cannot take two different values at the same time,
        //    so add axioms :- a(X1,X2,...,Xn,V1), a(X1,X2,...,Xn,V2), V1!=V2.
        for(const UAttDecl& attDecl : attdecls_) {
            auto const &name =  attDecl->attname;
            auto const numArgs = attDecl->svec.size();
            auto const vVal = "V";
            // make a(X1,X2,...,Xn,V1); and a(X1,X2,...,Xn,V1);
            std::vector<Clingo::AST::Term> Args1;
            std::vector<Clingo::AST::Term> Args2;
            for(int i=0;i<numArgs;i++) {
                std::string istr = std::to_string(i);
                // memory leak, figure out the correct API
                char * buf = new char[istr.length()+2];
                buf[0] = 'X';
                strcpy(buf+1,istr.c_str());
                Clingo::AST::Term vararg = Clingo::AST::Term{defaultLoc,Clingo::AST::Variable{buf}};
                Args1.push_back(vararg);
                Args2.push_back(vararg);
            }
            auto const &V1 = Clingo::AST::Term{defaultLoc,Clingo::AST::Variable{"_V1"}};
            Args1.emplace_back(V1);
            auto const &V2 = Clingo::AST::Term{defaultLoc,Clingo::AST::Variable{"_V2"}};
            Args2.emplace_back(V2);
            auto bodyLit1 = Statement::make_body_lit(name, Args1);
            auto bodyLit2 = Statement::make_body_lit(name, Args2);

            // make V1 != V2
            Clingo::AST::Comparison cmp{Clingo::AST::ComparisonOperator::NotEqual, V1, V2};
            Clingo::AST::Literal alit{defaultLoc, Clingo::AST::Sign::None, cmp};
            auto bodyLit3 = Clingo::AST::BodyLiteral{defaultLoc, Clingo::AST::Sign::None, alit};

            std::vector<Clingo::AST::BodyLiteral> body;
            body.push_back(bodyLit1);
            body.push_back(bodyLit2);
            body.push_back(bodyLit3);
            // empty disjunction should act as a constraint
            Clingo::AST::Disjunction d;
            Clingo::AST::Rule f_r{{defaultLoc, d}, body};
            b.add({defaultLoc, f_r});
        }
        if(solvingMode == SolvingMode::query_naive || solvingMode == SolvingMode::possible_worlds) {
            b.add({defaultLoc, Clingo::AST::ShowSignature{Clingo::Signature("__pr", 4, true), false}});
            b.add({defaultLoc, Clingo::AST::ShowSignature{Clingo::Signature("__query", 0, true), false}});
            b.add({defaultLoc, Clingo::AST::ShowSignature{Clingo::Signature("__truly_random", 1, true), false}});
            b.add({defaultLoc, Clingo::AST::ShowSignature{Clingo::Signature("__truly_random", 2, true), false}});
        }

        if(solvingMode == SolvingMode::possible_worlds) {
            for(const UAttDecl& attDecl : attdecls_) {
                b.add({defaultLoc, Clingo::AST::ShowSignature{Clingo::Signature(attDecl->attname.c_str(), attDecl->svec.size() + 1, true), false}});
            }
        }
    }

}

