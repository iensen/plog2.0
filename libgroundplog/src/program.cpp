//
// Created by iensen on 9/2/16.
//

#include<groundplog/program.h>
#include<clasp/util/misc_types.h>



namespace GroundPlog{
    using DestroyObject= Clasp::DestroyObject;

    void Program::doGetAssumptions(std::vector<Literal>  &out) const {throw "not implemented";}

    Program::Program():input_(0,0) {

    }

    void Program::setOptions(const Program::PrepOptions &opts) {
        opts_ = opts;
    }

    Program::~Program() {
        dispose(true);
    }

    void Program::dispose(bool force) {
        // remove rules
        std::for_each(bodies_.begin(), bodies_.end(), DestroyObject());
        std::vector<PrgBody*>().swap(bodies_);
        std::vector<Atom_t>().swap(heads_);
        if (force) {
            deleteAtoms(0);
            std::vector<PrgAtom*>().swap(atoms_);
            std::vector<Atom_t>().swap(propQ_);
        }
        rule_.clear();
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
        dispose(true);
        input_   = AttRange(0, -1);
        return true;
    }

    bool Program::doUpdateProgram() {
        throw "not implemented yet";
    }

    bool Program::doEndProgram() {
        throw "not implemented yet";
    }

    void Program::deleteAtoms(uint32 start) {
        for (auto it = atoms_.begin() + start, end = atoms_.end(); it != end; ++it) {
              delete *it;
        }
    }

    Program &Program::addRule(Atom_t head, std::vector<Lit_t> body, int ex_id) {
        // need to change this to add the dependency (and do not add the whole body)
        rules.emplace_back(Rule{head,body});
        ruleExternals.push_back(ex_id);
        return *this;
    }

    Program &Program::addRandomRule(std::pair<AttId, AId > head, const std::vector<Lit_t> body, int ex_id) {
        randomrules.emplace_back(RandomRule{head,body});
        randomRuleExternals.push_back(ex_id);
        return *this;
    }

    Program &Program::addPratom(Atom_t head, const std::vector<Lit_t> body, double prob) {
        pratoms.emplace_back(PrAtom{head,body, prob});
        return *this;
    }

    Program &Program::addQuery(Lit_t query) {
        this->query = query;
        return *this;
    }

    void Program::addAttributeMap(std::vector<unsigned int> vector) {
         this->attmap = vector;
    }

    void Program::addSortElem(unsigned int sort_id, unsigned int sort_elem_id) {
        if(sort_elems.size()<=sort_id)
                 sort_elems.resize(sort_id+1);
        sort_elems[sort_id].push_back(sort_elem_id);

    }

    void Program::addAtRangeSort(unsigned int a_id, unsigned int sort_id) {
        if(a_ranges.size()<=a_id)
            a_ranges.resize(a_id+1);
        a_ranges[a_id] = sort_id;
    }

    void Program::addObservation(unsigned int att_id, unsigned int val_id, bool positive){
         observations.emplace_back(Observation{att_id,val_id,positive});
    }

    void Program::addAction(unsigned int att_id, unsigned int val_id) {
         actions.emplace_back(Action{att_id,val_id});
    }

}