//
// Created by iensen on 6/13/20.
//
#include <groundplog/util/clingo_model_utils.h>
#include <plog/input/utils.h>

namespace GroundPlog {
// Compute statistics for the given model.
// Computes the number of possible values of a given attribute term in a given model
// @param dynRangeAtt is the name of the attribute term which is used to specify dynamic range of the attribute term
// in a given model. If there is no dynamic range, dynRangeAtt is empty.
// @param modelAttValue represents a model. modelAttvalue[a(t)] = y iff a(t) = y in a given model.
// @param inputProgram is the program for which the model was computed
    size_t getAttributeRangeElemCount(const std::string &attribute, const std::string &dynRangeAtt,
                                      std::unordered_map<std::string, std::string> &modelAttValue,
                                      const Plog::Program *inputProgram) {
        if (dynRangeAtt.empty()) {
            return  inputProgram->getAttributeRangeElementsCount(attribute);
        }

        auto attributeValues = inputProgram->getAttributeRangeElements(attribute);
        return std::count_if(attributeValues.begin(), attributeValues.end(),
                             [&](const Clingo::AST::Term &value) {
                                 auto att = dynRangeAtt + "(" + term_to_string(value) + ")";
                                 auto it = modelAttValue.find(att);
                                 return it != modelAttValue.end() && it->second == "true";
                             });
    }


    // returns true iff string src starts with prefix
    static bool startswith(const char *src, const char *prefix) {
        while (*prefix != 0) {
            if (*src == 0) {
                return false;
            }
            if (*prefix != *src) {
                return false;
            }
            ++src;
            ++prefix;
        }
        return true;
    }

    static bool
    isTrueInModel(const std::string &att, const std::unordered_map<std::string, std::string> &modelAttValue) {
        auto it = modelAttValue.find(att);
        if (it != modelAttValue.end()) {
            return it->second == "true";
        } else {
            return false;
        }
    }

    ModelStats getModelStats(const Clingo::Model &model, const Plog::Program *inputProgram) {
        const Clingo::SymbolVector &atvec = model.symbols();
        // trulyRandomAtts[i].first is the attribute name, trylyRandomAtts[i].second is the name of dynamic range
        // if there is no dynamic range, stores empty string.
        std::vector<std::pair<std::string, std::string>> trulyRandomAtts;
        // modelAttValue[a] = y if and only if the model contains atom a = y
        std::unordered_map<std::string, std::string> modelAttValue;
        // knownProbs[a][y] is c if and only if the model has satisfied pr-atom pr(a = y) = c
        std::unordered_map<std::string, std::unordered_map<std::string, double>> knownProbs;

        bool isQueryTrue = false;

        for (const Clingo::Symbol &s : atvec) {
            auto const name = s.name();
            // truly_random:
            if (startswith(name, "__t")) {
                if (s.arguments().size() == 1) {
                    trulyRandomAtts.emplace_back(
                            std::make_pair<std::string, std::string>(s.arguments()[0].to_string(), ""));
                } else {
                    trulyRandomAtts.emplace_back(std::make_pair<std::string, std::string>(s.arguments()[0].to_string(),
                                                                                          s.arguments()[1].to_string()));
                }

                continue;
            }
            if (startswith(name, "__q")) {
                isQueryTrue = true;
                continue;
            }
            //pr-atom
            if (startswith(name, "__pr")) {
                auto const attribute_term = s.arguments()[0].to_string();
                auto const value = s.arguments()[1].to_string();
                auto const numQuotedString = s.arguments()[2].to_string();
                auto const num = std::stoi(numQuotedString.substr(1, numQuotedString.size() - 2));
                auto const denumQuotedString = s.arguments()[3].to_string();
                auto const denum = std::stoi(denumQuotedString.substr(1, denumQuotedString.size() - 2));
                knownProbs[attribute_term][value] = double(num) / denum;
                continue;
            }

            if (!startswith(name, "_")) {
                std::string attribute_term = name;
                if (s.arguments().size() > 1) {
                    attribute_term += "(";
                    for (size_t i = 0; i < s.arguments().size() - 1; i++) {
                        if (i != 0) {
                            attribute_term += ",";
                        }
                        attribute_term += s.arguments()[i].to_string();
                    }
                    attribute_term += ")";
                }
                auto const &value = s.arguments().back().to_string();
                modelAttValue[attribute_term] = value;
            }
        }

        double probability = 1.0;
        for (auto const &truly_random_att_pair : trulyRandomAtts) {
            auto const &truly_random_att = truly_random_att_pair.first;
            auto const &dyn_range_att = truly_random_att_pair.second;
            auto const &value = modelAttValue.at(truly_random_att);
            // defined probability:
            auto knownProbsForAtt = knownProbs.find(truly_random_att);
            if (knownProbsForAtt != knownProbs.end()) {
                auto knownProbForAttValue = knownProbsForAtt->second.find(value);
                if (knownProbForAttValue != knownProbsForAtt->second.end()) {
                    probability *= knownProbForAttValue->second;
                    continue;
                }
            }

            // default probability:
            double sumKnownProb = 0.0;
            // the number of values for which we have a defined probability
            size_t definedProbValueCount = 0;
            if (knownProbsForAtt != knownProbs.end()) {
                for (auto const &attProb: knownProbsForAtt->second) {
                    // only add this probability if it belongs to dynamic range
                    if (dyn_range_att.empty() || isTrueInModel(dyn_range_att + "(" + value + ")", modelAttValue)) {
                        sumKnownProb += attProb.second;
                        ++definedProbValueCount;
                    }
                }
            }
            std::string attName;
            auto lParenPos = truly_random_att.find('(');
            if (lParenPos == std::string::npos) {
                attName = truly_random_att;
            } else {
                attName = truly_random_att.substr(0, lParenPos);
            }
            probability *= (1.0 - sumKnownProb) /
                           (getAttributeRangeElemCount(attName, dyn_range_att, modelAttValue, inputProgram) -
                            definedProbValueCount);
        }
        return {probability, isQueryTrue};
    }
}
