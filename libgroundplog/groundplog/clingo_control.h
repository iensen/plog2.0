//
// Created by iensen on 2/27/20.
//

#ifndef PLOG_CLINGO_CONTROL_H
#define PLOG_CLINGO_CONTROL_H

#include <unordered_set>
#include <functional>
#include <clingo.hh>

class PlogClingoControl {
public:
    PlogClingoControl(Clingo::Control *clingoCtrl,
                      const std::function<bool(unsigned int)>& isExternActive);
    Clingo::SolveHandle getModels();
    ~PlogClingoControl();

private:
    std::vector<Clingo::Symbol> assignExterns;
    Clingo::Control *clingoCtrl;
};

#endif //PLOG_CLINGO_CONTROL_H
