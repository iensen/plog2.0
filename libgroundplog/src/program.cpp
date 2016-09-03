//
// Created by iensen on 9/2/16.
//

#include<groundplog/program.h>

namespace GroundPlog{

    void Program::doGetAssumptions(std::vector<Literal>  &out) const {throw "not implemented";}

    Program::Program():input_(1,1) {
        throw "not implemented yet";
    }

    void Program::setOptions(const Program::PrepOptions &opts) {
        throw "not implemented yet";
    }

    Program::~Program() {
        throw "not implemented yet";
    }

    void Program::dispose(bool forceFullDispose) {
        throw "not implemented yet";
    }

    bool Program::clone(SharedContext &ctx) {
        throw "not implemented yet";
    }

    Atom_t Program::newAtom() {
        throw "not implemented yet";
    }

    bool Program::inProgram(Atom_t a) const {
        throw "not implemented yet";
    }

    bool Program::isDefined(Atom_t a) const {
        throw "not implemented yet";
    }

    bool Program::isFact(Atom_t a) const {
        throw "not implemented yet";
    }

    Literal Program::getLiteral(Id_t id) const {
        throw "not implemented yet";
    }

    Literal Program::getDomLiteral(Atom_t a) const {
        throw "not implemented yet";
    }

    bool Program::isFact(PrgAtom *a) const {
        throw "not implemented yet";
    }

    const char *Program::findName(Atom_t x) const {
        throw "not implemented yet";
    }

    Atom_t Program::falseAtom() {
        throw "not implemented yet";
    }

    std::vector<Id_t> &Program::getSupportedBodies(bool sorted) {
        throw "not implemented yet";
    }

    uint32 Program::update(PrgBody *b, uint32 oldHash, uint32 newHash) {
        throw "not implemented yet";
    }

    bool Program::assignValue(PrgAtom *a, ValueRep v, PrgEdge reason) {
        throw "not implemented yet";
    }

    bool Program::assignValue(PrgHead *h, ValueRep v, PrgEdge reason) {
        throw "not implemented yet";
    }

    PrgAtom *Program::setExternal(Atom_t atomId, ValueRep v) {
        throw "not implemented yet";
    }

    void Program::addFact(const Atom_t head) {
        throw "not implemented yet";
    }

    PrgBody *Program::getBodyFor(const Rule &r, bool addDeps) {
        throw "not implemented yet";
    }

    PrgBody *Program::getTrueBody() {
        throw "not implemented yet";
    }

    PrgBody *Program::assignBodyFor(const Rule &r, EdgeType x, bool strongSimp) {
        throw "not implemented yet";
    }

    ValueRep Program::litVal(const PrgAtom *a, bool pos) const {
        throw "not implemented yet";
    }

    bool Program::doStartProgram() {
        throw "not implemented yet";
    }

    bool Program::doUpdateProgram() {
        throw "not implemented yet";
    }

    bool Program::doEndProgram() {
        throw "not implemented yet";
    }

}