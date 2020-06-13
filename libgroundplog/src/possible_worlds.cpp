//
// Created by iensen on 6/13/20.
//

#include <groundplog/possible_worlds.h>
#include <groundplog/clingo_control.h>
#include <groundplog/util/clingo_model_utils.h>
#include <numeric>

namespace GroundPlog {

    PossibleWorldsComputer::PossibleWorldsComputer(GroundPlog::Program *groundProgram, Plog::Program *inputProgram,
                                                   Clingo::Control *cControl) :
            groundProgram(groundProgram), nonGroundProgram(inputProgram), cControl(cControl) {}

    void PossibleWorldsComputer::run() {
        std::function<bool(unsigned int)> isRuleActive = [](unsigned int) {
            return false;
        };
        auto control = PlogClingoControl(cControl, isRuleActive);
        std::vector<double> probabilities;
        std::cout << "Possible Worlds:" << std::endl;
        for (auto const &model: control.getModels()) {
            if (!model.optimality_proven() && !model.cost().empty()) {
                continue;
            }
            printModel(model);
            probabilities.push_back(getModelStats(model,nonGroundProgram).probability);
        }
        double sumProb = std::accumulate(probabilities.begin(), probabilities.end(),0.0);
        if(sumProb == 0.0) {
            std::cout << "Probabilistic function of this program is undefined." << std::endl
                      << "The sum of unnormalized measures of its possible worlds is 0.";
            return;
        }
        for(int i = 0; i < probabilities.size(); i++) {
            probabilities[i]/=sumProb;
        }
        std::cout << std::endl << "Probabilities:" << std::endl;
        for(int i = 0; i < probabilities.size(); i++) {
           std::cout << (i+1) << ": " << probabilities[i] << std::endl;
        }


    }

    static std::string getPlogAtomFromSymbol(const Clingo::Symbol &s) {
        if (s.name()[0] == '_') {
            return "";
        }
        std::stringstream ss;
        ss << s.name();
        auto args = s.arguments();
        assert(!args.empty());
        if (args.size() > 1) {
            ss << "(";
            for (size_t i = 0; i < args.size() - 1; i++) {
                if (i > 0) {
                    ss << ", ";
                }
                ss << args[i].to_string();
            }
            ss << ")";
        }
        auto value = args.back().to_string();
        if (value != "true") {
            ss << " = " << value;
        }
        return ss.str();
    }

    void PossibleWorldsComputer::printModel(const Clingo::Model &model) {
        bool firstAtomPrinted = false;
        ++modelsPrinted;
        std::cout << modelsPrinted << ": {";
        auto const &atvec = model.symbols();
        for (const Clingo::Symbol &s : atvec) {
            std::string plogAtom = getPlogAtomFromSymbol(s);
            if (plogAtom.empty()) {
                continue;
            }
            if (firstAtomPrinted) {
                std::cout << ", ";
            }
            std::cout << plogAtom;
            firstAtomPrinted = true;
        }
        std::cout <<"}" << std::endl;
    }
}
