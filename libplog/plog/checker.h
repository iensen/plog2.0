//
// Created by iensen on 11/26/21.
//

#ifndef PLOG_CHECKER_H
#define PLOG_CHECKER_H

#include "input/program.h"

class SortDefinition;
class Range;
namespace Plog {
    // This class performs error checking for a given P-log program with variables.
    class Checker {
    public:
        Checker(const Program &program, Plog::Logger &log);
        void check();
    private:
        const Program & program;
        Logger& log;
        void checkSortDefs();
        void checkSortDef(const SortDefinition& );
        void checkRangeSortExpr(const Range& );
    };
}

#endif //PLOG_CHECKER_H
