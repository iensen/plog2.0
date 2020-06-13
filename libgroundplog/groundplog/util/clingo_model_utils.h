//
// Created by iensen on 6/13/20.
//

#ifndef PLOG_CLINGO_MODEL_UTILS_H
#define PLOG_CLINGO_MODEL_UTILS_H

#include <plog/input/program.h>
namespace GroundPlog {
    struct ModelStats {
        double probability;
        bool isQueryTrue;
    };

// compute States for a given model. Requires inputProgram to do the computation.
    ModelStats getModelStats(const Clingo::Model &model, const Plog::Program *inputProgram);
}
#endif //PLOG_CLINGO_MODEL_UTILS_H
