//
// Created by iensen on 11/18/16.
//

#include<plog/grprogramobs.h>

void PlogGroundProgramBuilder::rule(bool choice, AtomSpan headats, LiteralSpan bodyLits) {
    printf("%d\n",*headats.begin());
    GRule r;
    for(auto c : headats) {
        r.head.push_back(c);
    }
    for(auto c : bodyLits) {
        r.body.push_back(c);
    }
    storedrules.push_back(r);
}

// question: why is it i need to include the namespace here? Is it C++ bug?
void PlogGroundProgramBuilder::output_atom(Clingo::Symbol symbol, Clingo::atom_t atom) {
     if(atom==0u) { // this is a fact
         facts.insert(symbol);
     }
    else {
         if(atom >= symbols.size()) {
             symbols.resize(2 * atom+1);
         }
         symbols[atom] = symbol;
     }
}

PlogGroundProgramBuilder::PlogGroundProgramBuilder(GroundPlogBackend &out):out(out) {

}

void PlogGroundProgramBuilder::end_step() {
    for (auto rule:storedrules) {
        addRuleToBackend(rule);
    }
}

void PlogGroundProgramBuilder::addRuleToBackend(GRule &rule) {
   if(rule.isRandom()) {
       addRandomRuleToBackend(rule);
   } else if(rule.isPrAtom()) {
       addPrAtomToBackend(rule);
   } else if(rule.isQuery()){
       addQueryToBackend(rule);
   } else {
       addRegularRuleToBackend(rule);
   }
}

void PlogGroundProgramBuilder::addRegularRuleToBackend(PlogGroundProgramBuilder::GRule &rule) {
    const atom_t hsymbolid =  *rule.head.begin();
    if(hsymbolid>=symbols.size() || symbols[hsymbolid] == Clingo::Symbol()) {
        // this is a fact
        // what should we do with facts?
        // probably nothing
        // we will do something later when we have a query
    } else {
        // o.k, this wasn't a fact
        // here the symbol is of the form a(t, X)
        Clingo::Symbol hsymbol = symbols[hsymbolid];
        // we need first to create a new attid for a(t),
        // note that this can be optimized if we store integers for every string, but in that case
        // we will need to write a hash function for such a symbol!
        Atom_t head = getGroundPlogAtom(hsymbol);
        // constructbody
        //std::vector<Lit_t> body = getGroundPlogBody(rule.)


    }
    printf("%d\n",hsymbolid);
}

void PlogGroundProgramBuilder::addQueryToBackend(PlogGroundProgramBuilder::GRule &rule) {

}

void PlogGroundProgramBuilder::addRandomRuleToBackend(PlogGroundProgramBuilder::GRule &rule) {

}

void PlogGroundProgramBuilder::addPrAtomToBackend(PlogGroundProgramBuilder::GRule &rule) {

}



Atom_t PlogGroundProgramBuilder::getGroundPlogAtom(Clingo::Symbol &s) {
    std::string hsymbolstr = std::string(s.name());
    if(s.arguments().size() > 1) hsymbolstr.push_back('(');

    // why is it if I replace auto with Clingo::Symbol it gives me an error?
    auto *h = s.arguments().begin();
    for(auto i=0; i<s.arguments().size()-1;i++) {
        hsymbolstr.append(h->to_string());
        if(i!=s.arguments().size()-2)
            hsymbolstr.append(",");
    }
    if(s.arguments().size() > 1) hsymbolstr.push_back(')');
    AttId attid = insert(hsymbolstr, attids);
    ValueRep atid = insert(h->to_string(),atids);

    return {attid, atid};
}

unsigned PlogGroundProgramBuilder::insert(std::string value, std::unordered_map<std::string, unsigned> &dist) {
    auto respt = dist.find(value);
    unsigned res;
    if(respt == attids.end()) {
        // todo: add check that the value actually fits
        attids[value] = (unsigned)attids.size();
        res = (unsigned )attids.size()-1;
    } else {
        res = respt->second;
    }
    return res;
}

bool PlogGroundProgramBuilder::GRule::isRandom() {
    return false;
}

bool PlogGroundProgramBuilder::GRule::isQuery() {
    return false;
}

bool PlogGroundProgramBuilder::GRule::isPrAtom() {
    return false;
}
