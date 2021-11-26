//
// Created by iensen on 11/26/21.
//

#include "plog/checker.h"
#include "plog/input/sortdefinition.h"
#include "plog/sortexpression.h"
namespace {

}
namespace Plog {

    Checker::Checker(const Program &program, Logger &log): program(program), log(log) {
    }
    void Checker::check() {
        checkSortDefs();
    }

    // check sort definitions of the program for errors
    void Checker::checkSortDefs() {
        for (auto const& sortDef: program.sortdefs_) {
           checkSortDef(*sortDef.get());
        }
    }

    void Checker::checkSortDef(const SortDefinition& sortDef) {
        auto const &sortExpr = sortDef.getSortExpr().get();
        if(auto rangeSortExpr = dynamic_cast<Range*>(sortExpr)) {
            checkRangeSortExpr(*rangeSortExpr);
        }
    }

    void Checker::checkRangeSortExpr(const Range & rSortExpr) {
        auto const& fromTerm = rSortExpr.from;
        auto const &toTerm = rSortExpr.to;
        bool hasUndefinedSymbols = false;
        Gringo::Logger glog;
        int fromNum = fromTerm->toNum(hasUndefinedSymbols, glog);
        int toNum = toTerm->toNum(hasUndefinedSymbols, glog);
        if(hasUndefinedSymbols) {
            log.check(plog_error_sort_definition);
        }
        if(toNum < fromNum) {
            PLOG_REPORT(log, plog_error_sort_definition)
                << rSortExpr.loc() <<": invalid range definition. "
                << "The second number in the range must be greater or equal to the first." << "\n";
        }
        // check that in range expression num1..num2, num2 >= num1.

    }
}