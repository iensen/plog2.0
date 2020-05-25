//
// Created by iensen on 2/27/20.
//
#include "groundplog/clingo_control.h"

/* Compute all the models of the program stored in clingoCtrl
 *
 * @param clingoCtrl - clingo control that stores a clingo program internally
 * @param isExternActive a function which returns true for each external atom id if and only if
 *        we should assign it to true.
 */
Clingo::SolveHandle PlogClingoControl::getModels()  {
    return clingoCtrl->solve();
}

PlogClingoControl::PlogClingoControl(Clingo::Control *clingoCtrl,
                                     const std::function<bool(unsigned int)>& isExternActive):clingoCtrl(clingoCtrl){
    Clingo::SymbolicAtoms ats = clingoCtrl->symbolic_atoms();
    for(auto it = ats.begin(); it!=ats.end();it++) {
        if(isExternActive(abs(it->literal()))) {
            assignExterns.push_back(it->symbol());
            clingoCtrl->assign_external(it->symbol(), Clingo::TruthValue::True);
        }
    }
}

PlogClingoControl::~PlogClingoControl() {
    for(auto const &s: assignExterns) {
        clingoCtrl->assign_external(s, Clingo::TruthValue::False);
    }
}