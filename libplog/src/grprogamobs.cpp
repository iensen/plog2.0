//
// Created by iensen on 11/18/16.
//

#include<plog/grprogramobs.h>
#include<plog/input/utils.h>
#include<ctype.h>

void PlogGroundProgramBuilder::rule(bool choice, AtomSpan headats, LiteralSpan bodyLits) {
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
    std::string sname = symbol.name();

    if (sname.length()>=2 && sname[0]=='_' && isalpha(sname[1])) { // this is a sort fact!
        // we need to say that the sort contains the term
        Clingo::Symbol s_elem = symbol.arguments()[0];
        unsigned sort_id = insert(sname.substr(1),sortids);
        unsigned s_elem_id = insert(s_elem.to_string(), atids);
        out.sortElem(sort_id,s_elem_id);
    }

    if(sname.length()>=3 && sname[0]=='_' && sname[1]=='_' && sname[2]=='r') {// range atom of the form range(a,s),
        // where a is an attribute name sort name and s is a sort name
        Clingo::Symbol asymb = symbol.arguments()[0];
        Clingo::Symbol ssymb = symbol.arguments()[1];

        unsigned sort_id = insert(ssymb.to_string(), sortids);
        unsigned a_id = insert(asymb.to_string(), aids);
        out.rangeSort(a_id, sort_id);
    }

    if(sname.length()>=3 && sname[0]=='_' && sname[1]=='_' && sname[2]=='q') {// query atom of the form range(a,s),
           addQueryToBackend(symbol);
    }

    if(sname == "obs") {
        addObservationToBackend(symbol);
       }

    if(sname == "do") {
        addActionToBackend(symbol);
    }





    if(atom == 0 && sname.length()>=3 && sname[0]=='_' && sname[1]=='_' && sname[2]=='p') {// we have pr-atom which is a fact:
        std::tuple<AttId, ValueRep, double> pratomRep = prAtomFromSymbol(symbol);
        out.prAtom({std::get<0>(pratomRep), std::get<1>(pratomRep)}, {}, std::get<2>(pratomRep));
    }


    // if the rule is random(a(t), p), need to add a(t) -> a to attributes
    if(!strcmp(symbol.name(),"random")) {
        // get the first argument:
        Clingo::Symbol aterm = symbol.arguments()[0];
        AttId attid = insert(aterm.to_string(), attids);
        AId  aid = insert(aterm.name(),aids);
        insert(aid, attid, attributes);
    } else {
        // else, if the atom is a(t), need to add a(t) -> a to attributes:
        unsigned aidd = insert(sname, aids);
        Atom_t plogatom = getGroundPlogAtom(symbol);
        // insert attribute term -> attribute into the map
        insert(aidd, plogatom.attid, attributes);

        // add random attribute term argument!
    }
     std::cout << atom << " " <<symbol.to_string() << std::endl;
     if(atom==0u) { // this is a fact
         facts.insert(symbol);
     }
     else {
         while(atom >= symbols.size()) {
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
        addAttributeMapToBackend();
    }
}

void PlogGroundProgramBuilder::addRuleToBackend(GRule &rule) {
   rule . setSymbolTable(&symbols);
   if(rule.isRandom()) {
       addRandomRuleToBackend(rule);
   } else if(rule.isPrAtom()) {
       addPrAtomToBackend(rule);
   } else if(rule.isRegular()) {
       addRegularRuleToBackend(rule);
   }  else {
       // do nothing!
   }
    //throw std::logic_error("rule is of wrong type");

}



void PlogGroundProgramBuilder::addRegularRuleToBackend(PlogGroundProgramBuilder::GRule &rule) {
    const atom_t hsymbolid =  *rule.head.begin();

    if(hsymbolid>=symbols.size() || symbols[hsymbolid] == Clingo::Symbol()) {
        // this is a fact
        // what should we do with facts?
        // probably nothing
    } else {
        Clingo::Symbol hsymbol = symbols[hsymbolid];
        Atom_t head = getGroundPlogAtom(hsymbol);
        const int ex_atom_id = rule.body.back();
        rule.body.pop_back();
        std::vector<Lit_t> body = getGroundPlogBody(rule.body);
        out.rule(head, body, ex_atom_id);
    }
}

void PlogGroundProgramBuilder::addQueryToBackend(Clingo::Symbol &qsymb) {
    auto *h = qsymb.arguments().begin();
    Atom_t attr = getGroundPlogAtom(*h);
    bool classicNeg =  (h+1)->to_string()!="true";
    bool defaultNeg = false;
    out.query(Lit_t{attr.attid, attr.valid, defaultNeg,classicNeg});
}

void PlogGroundProgramBuilder::addRandomRuleToBackend(PlogGroundProgramBuilder::GRule &rule) {
    const atom_t hsymbolid =  *rule.head.begin();
    Clingo::Symbol hsymbol = symbols[hsymbolid];
    Clingo::SymbolSpan  args = hsymbol.arguments();
    unsigned  aid = aids[args[1].name()];
    Clingo::Symbol atsymb = args[0];
    unsigned atid = insert(atsymb.to_string(),attids);
    // extract the last element from the body:
    const int ex_atom_id = rule.body.back();
    rule.body.pop_back();
    out.randomRule({atid,atid},getGroundPlogBody(rule.body), ex_atom_id);

}

void PlogGroundProgramBuilder::addPrAtomToBackend(PlogGroundProgramBuilder::GRule &rule) {
 //  pr(x(a),true,"3","10") :- B
    const atom_t hsymbolid =  *rule.head.begin();
    Clingo::Symbol hsymbol = symbols[hsymbolid];
    std::tuple <AttId , ValueRep , double> pratomRep = prAtomFromSymbol(hsymbol);
    out.prAtom({std::get<0>(pratomRep), std::get<1>(pratomRep)}, getGroundPlogBody(rule.body),std::get<2>(pratomRep));
}



Atom_t PlogGroundProgramBuilder::getGroundPlogAtom(const Clingo::Symbol &s) {
    std::string hsymbolstr = std::string(s.name());
    if(s.arguments().size() > 1) hsymbolstr.push_back('(');

    // why is it if I replace auto with Clingo::Symbol it gives me an error?
    auto *h = s.arguments().begin();
    for(auto i=0; i<s.arguments().size()-1;i++) {
        hsymbolstr.append(h->to_string());
        if(i!=s.arguments().size()-2)
            hsymbolstr.append(",");
        h++;
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

std::vector<Lit_t> PlogGroundProgramBuilder::getGroundPlogBody(const std::vector<literal_t> gbody) {
    std::vector<Lit_t> body;
    for(literal_t lit:gbody) {
        int32_t  litpos = abs(lit);
        Clingo::Symbol hsymbol = symbols[litpos];
        Atom_t atom = getGroundPlogAtom(hsymbol);
        body.emplace_back(Lit_t{atom.attid, atom.valid, lit < 0, hsymbol.is_negative()});
    }
    return body;
}

void PlogGroundProgramBuilder::addSortAtomToBackend(PlogGroundProgramBuilder::GRule &rule) {
    throw "not implemented yet";
}

void PlogGroundProgramBuilder::addObservationToBackend(const Clingo::Symbol &symbol) {
    Clingo::Symbol attsymb = symbol.arguments()[0];
    Clingo::Symbol valsymb = symbol.arguments()[1];
    Clingo::Symbol truthval = symbol.arguments()[2];
    unsigned attid = insert(attsymb.to_string(), attids);
    unsigned valid = insert(valsymb.to_string(), atids);
    out.observation(attid, valid, truthval.to_string()=="true");

}

void PlogGroundProgramBuilder::addActionToBackend(const Clingo::Symbol &symbol) {
    Clingo::Symbol attsymb = symbol.arguments()[0];
    Clingo::Symbol valsymb = symbol.arguments()[1];
    unsigned attid = insert(attsymb.to_string(), attids);
    unsigned valid = insert(valsymb.to_string(), atids);
    out.action(attid, valid);

}

void PlogGroundProgramBuilder::addAttributeMapToBackend() {
    out.atMap(attributes);
}

std::tuple<AttId , ValueRep, double > PlogGroundProgramBuilder::prAtomFromSymbol(const Clingo::Symbol &s) {

    auto *h = s.arguments().begin();
    AttId attid = insert(h->to_string(), attids);
    ValueRep atid = insert((h+1)->to_string(),atids);
    std::string numstr = (h+2)->to_string();
    std::string denumstr = (h+3)->to_string();
    int probnum =   str_to_int(numstr.substr(1,numstr.length()-2));
    int probdenum = str_to_int(denumstr.substr(1,numstr.length()-2));
    double prob = ((double) probnum)/((double) probdenum);
    return std::tuple<AttId , ValueRep , double>(attid, atid, prob);
}

void PlogGroundProgramBuilder::insert(unsigned value, unsigned index, std::vector<unsigned> &dist) {
    while (index >= dist.size()) {
        dist.resize(2 * index + 1);
    }
    attributes[index] = value;
}


bool PlogGroundProgramBuilder::GRule::isRandom() {
    // to check if a rule is random we need to check that it's head is of the form random(...
    return getHeadAttrName()=="random";
}

bool PlogGroundProgramBuilder::GRule::isPrAtom() {
    return getHeadAttrName()=="__pr";
}

bool PlogGroundProgramBuilder::GRule::isRegular() {
    //  the rule is regular if it is not random and
    // the last atom in the body of the form ext(id,...) where id a number
    if(isRandom())
        return false;
    if(body.size()==0)
        return false;
    Clingo::literal_t lit = body[body.size()-1];
    if((abs(lit)) >= symbols->size() || symbols->at(abs(lit)) == Clingo::Symbol()) {
        return false;
    }
    Clingo::Symbol s = this-> symbols->at(abs(lit));
    return isRuleExternalSymbol(s);
}



std::string PlogGroundProgramBuilder::GRule::getHeadAttrName() {
    Clingo::Symbol hs = getHeadSymbol();
    if(hs == Clingo::Symbol()) {
        return "";
    }
    Clingo::Symbol hsymbol = this-> symbols->at(*head.begin());
    return std::string(hsymbol.name());
}

void PlogGroundProgramBuilder::GRule::setSymbolTable(std::vector<Clingo::Symbol> *symbols) {
   this -> symbols = symbols;
}

Clingo::Symbol PlogGroundProgramBuilder::GRule::getHeadSymbol() {
    if(head.size()==0)
        return Clingo::Symbol();
    return symbols->at(*head.begin());
}

bool PlogGroundProgramBuilder::GRule::isRuleExternalSymbol(Clingo::Symbol &hs) {
    if(hs == Clingo::Symbol()) {
        return false;
    }
    if(strcmp(hs.name(),"__ext")!=0)
        return false;
    Clingo::Symbol firstArg = *hs.arguments().begin();
    std::string firstArgStr = firstArg.to_string();
    return isdigit(firstArgStr[0]);
}
