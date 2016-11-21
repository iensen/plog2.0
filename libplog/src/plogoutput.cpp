//
// Created by iensen on 9/16/16.
//

#include<plog/plogoutput.h>

void GroundPlogBackend::rule(Atom_t &head, const std::vector<Lit_t> &body) {
    if (auto p = prg()) { p->addRule(head, body); }
}

void GroundPlogBackend::randomRule(std::vector<std::pair<Atom_t,AttId>> head, const std::vector<Lit_t> &body) {
    if (auto p = prg()) { p->addRandomRule(head, body); }
}

void GroundPlogBackend::prAtom(Atom_t &head, const std::vector<Lit_t> &body) {
    if (auto p = prg()) { p->addPratom(head, body); }
}

void GroundPlogBackend::query(Lit_t &query) {
    if (auto p = prg()) { p->addQuery(query); }
}

GroundPlog::Program *GroundPlogBackend::prg() {
    return ctl_.update() ? static_cast<GroundPlog::Program *>(ctl_.groundplog_->program()) : nullptr;
}
