//
// Created by iensen on 11/26/21.
//

#ifndef PLOG_CHECKER_H
#define PLOG_CHECKER_H

#include "input/program.h"
#include "recordinfo.h"

class SortDefinition;
class Range;


namespace Plog {
    // This class performs error checking for a given P-log program with variables.
    class Checker {
    public:
        Checker(const Program &program, Plog::Logger &log);

        void check();

    private:
        const Program &program;
        Logger &log;
        std::unordered_set<Record> records;

        void checkSortDefs();
        void checkSortDef(const SortDefinition &, const std::unordered_set<Gringo::String> &definedSorts);
        void checkSortExpr(const SortExpression* sortExpr,
                           const std::unordered_set<Gringo::String> &definedSorts);
        void checkRangeSortExpr(const Range &);
        void checkSetBinOpSortExpr(const BinOpSortExpr& binopSortExpr,
                                            const std::unordered_set<Gringo::String> &definedSorts);

        void checkSortNameSortExpr(const SortNameExpr &sortNameSortExpr,
                              const std::unordered_set<Gringo::String> &definedSorts);

        const SortDefinition & getSortDefinition(Gringo::String sortName);

        void
        checkFuncSortExpr(const FuncSortExpr &funcSortExpr, const std::unordered_set<Gringo::String> &definedSorts);

        void checkAttributeDecls();

        const AttributeDeclaration &getAttributeDeclaration(String attributeName);

        void checkAttDecl(const AttributeDeclaration &declaration,
                          const std::unordered_set<String> &definedSorts);
    };
}

#endif //PLOG_CHECKER_H
