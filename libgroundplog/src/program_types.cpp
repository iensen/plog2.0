//
// Created by iensen on 9/3/16.
//

#include <groundplog/program_types.h>

bool GroundPlog::RegularRule::constructedFrom(const std::unordered_set<GroundPlog::ATTID> &atts) {
    if(atts.find(head.attid) == atts.end())
        return false;
    for(Lit_t lit:body)
        if(atts.find(lit.attid) == atts.end())
            return false;
    return true;
}

unsigned GroundPlog::RegularRule::countPositiveBodyLiterals() const {
    unsigned countPosBodyLit = 0;
    for(const Lit_t lit:body) {
        if(!lit.defaultNeg)
            ++countPosBodyLit;

    }
    return countPosBodyLit;
}

bool GroundPlog::RandomRule::constructedFrom(const std::unordered_set<GroundPlog::ATTID> &atts) {
    if(atts.find(head.first) == atts.end())
        return false;
    for(Lit_t lit:body)
        if(atts.find(lit.attid) == atts.end())
            return false;
    return true;
}

bool GroundPlog::PrAtom::constructedFrom(const std::unordered_set<GroundPlog::ATTID> &atts) {
    if(atts.find(head.attid) == atts.end())
        return false;
    for(Lit_t lit:body)
        if(atts.find(lit.attid) == atts.end())
            return false;
    return true;

}

GroundPlog::Rule::~Rule() {

}
