//
// Created by iensen on 9/16/16.
//

#include<plog/plogoutput.h>

void GroundPlogBackend::rule(Atom_t &head, const std::vector<Lit_t> &body, int ex_atom_id) {
    if (auto p = prg()) { p->addRule(head, body, ex_atom_id); }
}

void GroundPlogBackend::randomRule(std::pair<ATTID, AId> head, const std::vector<Lit_t> &body, int ex_atom_id) {
    if (auto p = prg()) { p->addRandomRule(head, body, ex_atom_id); }
}

void GroundPlogBackend::prAtom(const Atom_t &head, const std::vector<Lit_t> &body, double prob, int ex_atom_id) {
    if (auto p = prg()) { p->addPratom(head, body, prob, ex_atom_id); }
}

void GroundPlogBackend::query(const Lit_t &query) {
    if (auto p = prg()) { p->addQuery(query); }
}

GroundPlog::Program *GroundPlogBackend::prg() {
    return ctl_.update() ? (ctl_.groundplog_->program()) : nullptr;
}

void GroundPlogBackend::atMap(std::vector<unsigned> mp) {
    if (auto p = prg()) { p->addAttributeMap(mp); }
}

void GroundPlogBackend::sortElem(unsigned sort_id, unsigned sort_elem_id) {
    if (auto p = prg()) { p->addSortElem(sort_id, sort_elem_id); }
}

void GroundPlogBackend::rangeSort(unsigned a_id, unsigned sort_id) {
    if (auto p = prg()) { p->addAtRangeSort(a_id, sort_id); }
}

void GroundPlogBackend::observation(unsigned att_id, unsigned val_id, bool positive) {
    if (auto p = prg()) { p->addObservation(att_id, val_id, positive); }
}

void GroundPlogBackend::action(unsigned att_id, unsigned val_id) {
    if (auto p = prg()) { p->addAction(att_id, val_id); }
}

void GroundPlogBackend::atomExternal(unsigned att_id, unsigned val_id, unsigned ex_atom_id) {
    if (auto p = prg()) { p->addAtomExternal(att_id, val_id, ex_atom_id); }
}

void GroundPlogBackend::registerLiteral(unsigned atom_id, unsigned att_id, unsigned val_id, bool neg) {
    if (auto p = prg()) { p->registerLiteral(att_id,val_id,!neg,atom_id);}
}

void GroundPlogBackend::registerDynRangeAtom(unsigned a_id, unsigned arg_id, unsigned att_id) {
    if (auto p = prg()) { p->registerDynRangeAtom(a_id,arg_id,att_id);}
}

void GroundPlogBackend::registerTrueAtId(unsigned true_id) {
    if (auto p = prg()) { p->registerTrueAtId(true_id);}
}

