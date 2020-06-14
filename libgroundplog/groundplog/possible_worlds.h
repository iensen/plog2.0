//
// Created by iensen on 8/21/16.
//

#pragma  once

#include <cstddef>

namespace Plog {
    class Program;
}
namespace Clingo {
    class Control;
    class Model;
}

namespace GroundPlog {
    class PossibleWorldsComputer {
     public:
        PossibleWorldsComputer(Plog::Program* inputProgram, Clingo::Control *cControl);
        void run();
    private:
        const Plog::Program* nonGroundProgram;
        Clingo::Control* cControl;
        void printModel(const Clingo::Model&);
        // stores how many models were printed
        size_t modelsPrinted = 0;
    };
}