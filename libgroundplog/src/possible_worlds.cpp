//
// Created by iensen on 6/13/20.
//

#include <groundplog/possible_worlds.h>
#include <groundplog/clingo_control.h>
#include <groundplog/util/clingo_model_utils.h>
#include <memory>
#include <numeric>

namespace GroundPlog {



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

    // Class used to output possible worlds. The derived classes will vary depending
    // on the output format (text, json, etc). The output will consist of two main phases:
    // (1) outputting models (2) outputting probabilities
    /* abstract */ class PossibleWorldPrinter {
    public:
        // function to be called before the first possible world
        // is output
        virtual void init() = 0;
        virtual void outputModel(const Clingo::Model &model) = 0;
        virtual void outputProbabilities(std::vector<double> &probabilities) = 0;
        virtual void finalize() = 0;
        virtual void outputError(const std::string &) = 0;
        virtual ~PossibleWorldPrinter() = default;
    };

    // class to output possible worlds in text format
    class PossibleWorldTextPrinter: public PossibleWorldPrinter {

        void init() override {
          std::cout << "Possible Worlds:" << std::endl;
        }

        // keep track how many models have been printed for a nicer output
        unsigned int modelsPrinted = 0;
        void outputModel(const Clingo::Model & model) override {
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
            std::cout << "}" << std::endl;
        }

        void outputProbabilities(std::vector<double> &probabilities) override {
            std::cout << "\nProbabilities:\n";
            for (int i = 0; i < probabilities.size(); i++) {
                std:: cout << i + 1 <<   ": "  << probabilities[i]  << std::endl;
              }
        }

        // method called after all models have been output, and probabilities were output
        // we expect that by the time it finishes, the output is present where it needs to be
        void finalize() override {
            // nothing to do
        }

        void outputError(const std::string & error) override  {
             std::cerr << error;
        }
    };

    // class to output possible worlds in Json Format
    class PossibleWorldJsonPrinter: public PossibleWorldPrinter {
        // for this class, we will keep the entire text in memory before being output,
        // this simplifies the output for probabilities.
        std::vector<std::string> jsonOutput;
        // a flag used to decide whether or not we need to print separator
        bool hasPrintedAtLeastOneModel = false;
        // function to be called before the first possible world
        // is output
        void init() override {
            jsonOutput.emplace_back("[");
        }

        void outputModel(const Clingo::Model &model) override {
            //Store the possible worlds to in json format
            if (hasPrintedAtLeastOneModel) {
                jsonOutput.emplace_back(",");
            }
            //the start of a possible world
            jsonOutput.emplace_back("{\n\"possible_world\" : \n[\n");

            //booleans to store to add comma (,) after an atom is printed
            bool firstAtomPrinted = false;

            auto const &atvec = model.symbols();
            for (const Clingo::Symbol &s : atvec) {
                std::string plogAtom = getPlogAtomFromSymbolforJSON(s);
                if (plogAtom.empty()) {
                    continue;
                }
                //if this is not the first atom record, then add a comma behind it
                if (firstAtomPrinted) {
                    jsonOutput.back() += ",\n";
                }
                jsonOutput.back()+=plogAtom;
                if (firstAtomPrinted) {
                    jsonOutput.back()+="\n";
                }
                firstAtomPrinted = true;
            }
            jsonOutput.back()+="],\n\"probability\" : ";
            jsonOutput.emplace_back("\n}");
            hasPrintedAtLeastOneModel = true;
        }

        void outputProbabilities(std::vector<double> &probabilities) override {
            for (int i = 0; i < probabilities.size(); i++) {
                //add probability in text format
                int position = 2 + (4 * i);
                std::string probability = std::to_string(probabilities[i]);
                jsonOutput.insert(jsonOutput.begin() + position, probability);
            }
        }

        void finalize() override {
            jsonOutput.emplace_back("\n]");
            for (auto const &str: jsonOutput) {
                std::cout << str;
            }
        }

        void outputError(const std::string &) override {
            assert(false); // errors in this mode are not handled correctly
        }
    };

    PossibleWorldsComputer::PossibleWorldsComputer(Plog::Program *inputProgram,
                                                   Clingo::Control *cControl, Format format_) :
            nonGroundProgram(inputProgram), cControl(cControl), format(format_) {}



    void PossibleWorldsComputer::run() {
        //vector to store the probabilities of each possible world for json format
        std::vector<double> probabilities;

        std::unique_ptr<PossibleWorldPrinter> printer;
        if(format == text) {
            printer = std::make_unique<PossibleWorldTextPrinter>();
        } else {
            printer =  std::make_unique<PossibleWorldJsonPrinter>();
        }

        printer->init();

        for (auto const &model: cControl->solve()) {
            if (!model.optimality_proven() && !model.cost().empty()) {
                continue;
            }
            printer->outputModel(model);
            //storing probabilities of each possible world to a vector
            probabilities.push_back(getModelStats(model, nonGroundProgram).probability);
        }

        double sumProb = std::accumulate(probabilities.begin(), probabilities.end(), 0.0);
        if (sumProb == 0.0) {
            printer->outputError("Probabilistic function of this program is undefined.\n"
                                   "The sum of unnormalized measures of its possible worlds is 0.");
            return;
        }
        for (double & probability : probabilities) {
            probability /= sumProb;
        }
        printer->outputProbabilities(probabilities);
        printer->finalize();
    }
}
