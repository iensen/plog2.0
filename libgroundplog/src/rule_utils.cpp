//
// Created by iensen on 9/2/16.
//

#include <groundplog/rule_utils.h>

GroundPlog::RuleBuilder::RuleBuilder() {
    clear();
}

GroundPlog::RuleBuilder &GroundPlog::RuleBuilder::start() {
    throw "not implemented yet";
}

GroundPlog::RuleBuilder &GroundPlog::RuleBuilder::startBody() {
    throw "not implemented yet";
}

GroundPlog::RuleBuilder &GroundPlog::RuleBuilder::addHead(GroundPlog::Atom_t a) {
    throw "not implemented yet";
}

GroundPlog::RuleBuilder &GroundPlog::RuleBuilder::addGoal(GroundPlog::Lit_t lit) {
    throw "not implemented yet";
}

GroundPlog::RuleBuilder &GroundPlog::RuleBuilder::end() {
    throw "not implemented yet";
}

GroundPlog::RuleBuilder &GroundPlog::RuleBuilder::clear() {
    return *this;
}

GroundPlog::RuleBuilder &GroundPlog::RuleBuilder::clearBody() {
    throw "not implemented yet";
}



GroundPlog::Atom_t GroundPlog::RuleBuilder::head() const {
    throw "not implemented yet";
}

uint32_t GroundPlog::RuleBuilder::bodySize() const {
    throw "not implemented yet";
}

std::vector<GroundPlog::Lit_t> GroundPlog::RuleBuilder::body() const {
    throw "not implemented yet";
}

GroundPlog::Rule_t GroundPlog::RuleBuilder::rule() const {
    throw "not implemented yet";
}

void GroundPlog::RuleBuilder::endHead() {
    throw "not implemented yet";
}

void GroundPlog::RuleBuilder::endBody() {
    throw "not implemented yet";
}
