//
// Created by iensen on 8/21/16.
//

#pragma  once

#include <cstddef>
#include <plog/plog.h>
#include <string>

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
        PossibleWorldsComputer(Plog::Program* inputProgram, Clingo::Control *cControl, Format format_);
        void run();
    private:
        const Plog::Program* nonGroundProgram;
        Clingo::Control* cControl;
        std::string printModel(const Clingo::Model&);
        std::string printModelJSON(const Clingo::Model &model);
        // stores how many models were printed
        size_t modelsPrinted = 0;
        Format format = json;
    };
}