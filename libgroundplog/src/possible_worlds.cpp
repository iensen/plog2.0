//
// Created by iensen on 6/13/20.
//

#include <groundplog/possible_worlds.h>
#include <groundplog/clingo_control.h>
#include <groundplog/util/clingo_model_utils.h>
#include <numeric>

namespace GroundPlog {

    PossibleWorldsComputer::PossibleWorldsComputer(Plog::Program *inputProgram,
                                                   Clingo::Control *cControl, Format format_) :
            nonGroundProgram(inputProgram), cControl(cControl), format(format_) {}

    static std::string getPlogAtomFromSymbol(const Clingo::Symbol &s)  {
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

    static std::string getPlogAtomFromSymbolforJSON(const Clingo::Symbol &s) {
        if (s.name()[0] == '_') {
            return "";
        }
        std::stringstream ss;
        ss << "{\n";
        ss << "\"attribute_term\" : " << "\"" << s.name();
        auto args = s.arguments();
        assert(!args.empty());
        if (args.size() > 1) {
            for (size_t i = 0; i < args.size() - 1; i++) {
                ss << "(" << args[i].to_string() << ")";
            }
        }
        ss << "\",\n";
        auto value = args.back().to_string();
        ss << "\"value\" : " << "\"" << value << "\"\n";
        ss << "}";
        return ss.str();
    }

    void PossibleWorldsComputer::run() {
        //vector to store the output in json format
        std::vector<std::string> jsonFile;
        //vector to store the output in text format
        std::vector<std::string> textFile;
        //vector to store the probabilities of each possible world for json format
        std::vector<double> probabilities;

        textFile.push_back("Possible Worlds:\n");
        jsonFile.push_back("[");

        //booleans to store to add comma (,) after a possible world is printed
        bool firstPossibleWorldPrinted = false;
        for (auto const &model: cControl->solve()) {
            if (!model.optimality_proven() && !model.cost().empty()) {
                continue;
            }
            //Store the possible worlds to in text format
            std::string modelText = printModel(model);
            textFile.push_back(modelText);

            //Store the possible worlds to in json format
            if (firstPossibleWorldPrinted) {
                jsonFile.push_back(",");
            }
            std::string modelJSON = printModelJSON(model);
            jsonFile.push_back(modelJSON);
            jsonFile.push_back("\n}");
            firstPossibleWorldPrinted = true;

            //storing probabilities of each possible world to a vector
            probabilities.push_back(getModelStats(model, nonGroundProgram).probability);
        }

        double sumProb = std::accumulate(probabilities.begin(), probabilities.end(), 0.0);
        if (sumProb == 0.0) {
            textFile.push_back("Probabilistic function of this program is undefined.\n");
            textFile.push_back("The sum of unnormalized measures of its possible worlds is 0.");
            return;
        }
        for (int i = 0; i < probabilities.size(); i++) {
            probabilities[i] /= sumProb;
        }
        textFile.push_back("\nProbabilities:\n");
        for (int i = 0; i < probabilities.size(); i++) {
            //add probability in text format
            int number = i + 1;
            textFile.push_back(std::to_string(number) + ": " + std::to_string(probabilities[i]) + "\n");
            //add the appropriate probability to the right position (2,6,10) in json format
            int position = 2 + (4 * i);
            std::string probability = std::to_string(probabilities[i]);
            jsonFile.insert(jsonFile.begin() + position, probability);
        }

        //Decides what format to print the possible worlds in
        if (format == json) {
            jsonFile.push_back("\n]");
            for (int i=0; i<jsonFile.size(); ++i)
                std::cout << jsonFile[i];
        } else {
            for (int i=0; i<textFile.size(); ++i)
                std::cout << textFile[i];
        }
    }

    std::string PossibleWorldsComputer::printModel(const Clingo::Model &model) {
        bool firstAtomPrinted = false;
        std::stringstream modelsstext;
        ++modelsPrinted;
        modelsstext << modelsPrinted << ": {";
        auto const &atvec = model.symbols();
        for (const Clingo::Symbol &s : atvec) {
            std::string plogAtom = getPlogAtomFromSymbol(s);
            if (plogAtom.empty()) {
                continue;
            }
            if (firstAtomPrinted) {
                modelsstext << ", ";
            }
            modelsstext << plogAtom;
            firstAtomPrinted = true;
        }
        modelsstext << "}" << std::endl;
        return modelsstext.str();
    }

    std::string PossibleWorldsComputer::printModelJSON(const Clingo::Model &model) {
        std::stringstream modelssjson;

        modelssjson << "\n";
        auto const &atvec = model.symbols();

        //the start of a possible world
        modelssjson << "{\n\"possible_world\" : \n[\n";

        //booleans to store to add comma (,) after an atom is printed
        bool firstAtomPrinted = false;
        for (const Clingo::Symbol &s : atvec) {
            std::string plogAtom = getPlogAtomFromSymbolforJSON(s);
            if (plogAtom.empty()) {
                continue;
            }
            //if this is not the first atom record, then add a comma behind it
            if (firstAtomPrinted) {
                modelssjson << ",";
                modelssjson << "\n";
            }
            modelssjson << plogAtom;
            if (firstAtomPrinted) {
                modelssjson << "\n";
            }
            firstAtomPrinted = true;
        }
        modelssjson <<"],\n\"probability\" : ";

        return modelssjson.str();
    }
}
