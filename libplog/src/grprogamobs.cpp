//
// Created by iensen on 11/18/16.
//

#include<plog/grprogramobs.h>
#include<plog/input/utils.h>
#include<ctype.h>

void PlogGroundProgramBuilder::rule(bool choice, AtomSpan headats, LiteralSpan bodyLits) {

    GRule r;

    /*
    std::cout << "RULE:" << " ";
    std::cout << "HEAD: " << headats[0] << " ";
    std::cout << "BODY: ";
    for(literal_t lit: bodyLits) {
        std::cout << " " << lit;
    }
    std::cout << std::endl;
    */


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

    //std::cout << "ATOM ID: " << atom << " SYMBOL: " << symbol.to_string() << std::endl;
    std::string sname = symbol.name();
    if (sname.length()>=2 && sname[0]=='_' && isalpha(sname[1])) { // this is a sort fact!
        // we need to say that the sort contains the term
        Clingo::Symbol s_elem = symbol.arguments()[0];
        unsigned sort_id = insert(sname.substr(1),sortids);
        unsigned s_elem_id = insert(s_elem.to_string(), atids);
        sort_elems[sort_id].push_back(s_elem_id);
        term_str[s_elem_id] = s_elem.to_string();
        out.sortElem(sort_id,s_elem_id);// probably do it later to save some memory?
    }

    if(sname.length()>=3 && sname[0]=='_' && sname[1]=='_' && sname[2]=='r') {// range atom of the form range(a,s),
        // where a is an attribute name sort name and s is a sort name
        Clingo::Symbol asymb = symbol.arguments()[0];
        Clingo::Symbol ssymb = symbol.arguments()[1];

        unsigned sort_id = insert(ssymb.to_string(), sortids);
        unsigned a_id = insert(asymb.to_string(), aids);
        a_range_sort[a_id] = sort_id;
        out.rangeSort(a_id, sort_id); // probably do it later to save some memory?
    }

    if(sname.length()>=3 && sname[0]=='_' && sname[1]=='_' && sname[2]=='q') {// query atom ,
           addQueryToBackend(symbol);
    }

    if(sname == "obs") {
        addObservationToBackend(symbol);
       }

    if(sname == "do") {
        addActionToBackend(symbol);
    }






    // if the rule is random(a(t), p), need to add a(t) -> a to attributes
    if(!strcmp(symbol.name(),"random")) {
        // get the first argument:
        Clingo::Symbol aterm = symbol.arguments()[0];
        ATTID attid = insert(aterm.to_string(), attids);
        AId  aid = insert(aterm.name(),aids);
        out.atttoat(attid,aid);
        insert(aid, attid, attributes);
    } else {
        // else, if the atom is a(t), need to add a(t) -> a to attributes:
        unsigned aidd = insert(sname, aids);
        Atom_t plogatom = getGroundPlogAtom(symbol);
        // insert attribute term -> attribute into the map
        insert(aidd, plogatom.attid, attributes);

        // add random attribute term argument!
    }
     //std::cout << atom << " " <<symbol.to_string() << std::endl;
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

    if(!rulesPassedToBackend) {


        /*
        std::cout << "TERMS:" << std::endl;
        for(auto c:atids) {
            std::cout << c.first << " " << c.second << std::endl;
        }
        std::cout <<"Attribute Terms" << std::endl;
        for(auto c:attids) {
            std::cout << c.first << " " << c.second << std::endl;
        }

        std::cout << "Attributes" << std::endl;
        for(auto c:aids) {
            std::cout << c.first << " " << c.second << std::endl;
        }

        std::cout << "Sorts" << std::endl;
        for(auto c:sortids) {
            std::cout << c.first << " " << c.second << std::endl;
        }
        */



        for (auto rule:storedrules) {
            addRuleToBackend(rule);
            addAttributeMapToBackend();
        }



        // add the value for true
        out.registerTrueAtId(insert("true", atids));
        rulesPassedToBackend = true;
    }

}

void PlogGroundProgramBuilder::addRuleToBackend(GRule &rule) {
    rule . setSymbolTable(&symbols);
    rule.normalize();
   if(rule.isRandom()) {
       addRandomRuleToBackend(rule);
   } else if(rule.isPrAtom()) {
       addPrAtomToBackend(rule);
   } else if(rule.isRegular()) {
       addRegularRuleToBackend(rule);
   }  else if(rule.isAtomExternal()){
       addAtomExternalToBackend(rule);
       registerAtomInBackend(rule.head[0]);
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
    // we need to support random rules with no range argument!
    const atom_t hsymbolid =  *rule.head.begin();
    Clingo::Symbol hsymbol = symbols[hsymbolid];
    Clingo::SymbolSpan  args = hsymbol.arguments();
    unsigned aid = args.size()==3 ? aids[args[1].name()]:UNASSIGNED;// args.size()==3 if atom is of the form
    // random(a,p), (the third argument is "true" after the translation")
    Clingo::Symbol atsymb = args[0];
    unsigned atid = insert(atsymb.to_string(),attids);
    // extract the last element from the body:
    const int ex_atom_id = rule.body.back();
    rule.body.pop_back();
    out.randomRule({atid,aid},getGroundPlogBody(rule.body), ex_atom_id);

    if(args.size()==3) {
        // store the map p,y -> attid for every y in the range of a!
        unsigned sort_id = a_range_sort[aids[args[0].name()]];
        const std::vector<ValueRep> &elems = sort_elems[sort_id];
        for (ValueRep val : elems) {
            // construct a string p(y) (would be more safe to actually form the symbol)
            std::string at = args[1].name();
            at.push_back('(');
            at += term_str[val];
            at.push_back(')');
            ATTID att_id = insert(at, attids);
            out.registerDynRangeAtom(aid, val, att_id);
        }
    }
}

void PlogGroundProgramBuilder::addPrAtomToBackend(PlogGroundProgramBuilder::GRule &rule) {
 //  pr(x(a),true,"3","10") :- B
    const atom_t hsymbolid =  *rule.head.begin();
    Clingo::Symbol hsymbol = symbols[hsymbolid];
    std::tuple <ATTID , ValueRep , double> pratomRep = prAtomFromSymbol(hsymbol);
    const int ex_atom_id = rule.body.back();
    rule.body.pop_back();
    std::vector<Lit_t> body = getGroundPlogBody(rule.body);
    out.prAtom({std::get<0>(pratomRep), std::get<1>(pratomRep)}, body ,std::get<2>(pratomRep), ex_atom_id);
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
    ATTID attid = insert(hsymbolstr, attids);
    ValueRep atid = insert(h->to_string(),atids);
    return {attid, atid};
}

unsigned PlogGroundProgramBuilder::insert(std::string value, std::unordered_map<std::string, unsigned> &dist) {
    auto respt = dist.find(value);
    if(respt == dist.end()) {
        // todo: add check that the value actually fits
        int sz = dist.size();
        dist[value] = sz;
    }
    return dist[value];
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
    Atom_t at = getGroundPlogAtom(symbol);
    out.action(at.attid, at.valid);

}

void PlogGroundProgramBuilder::addAttributeMapToBackend() {
    out.atMap(attributes);
}

std::tuple<ATTID , ValueRep, double > PlogGroundProgramBuilder::prAtomFromSymbol(const Clingo::Symbol &s) {

    auto *h = s.arguments().begin();
    ATTID attid = insert(h->to_string(), attids);
    ValueRep atid = insert((h+1)->to_string(),atids);
    std::string numstr = (h+2)->to_string();
    std::string denumstr = (h+3)->to_string();
    int probnum =   str_to_int(numstr.substr(1,numstr.length()-2));
    int probdenum = str_to_int(denumstr.substr(1,denumstr.length()-2));
    double prob = ((double) probnum)/((double) probdenum);
    return std::tuple<ATTID , ValueRep , double>(attid, atid, prob);
}

void PlogGroundProgramBuilder::insert(unsigned value, unsigned index, std::vector<unsigned> &dist) {
    while (index >= dist.size()) {
        dist.resize(2 * index + 1);
    }
    attributes[index] = value;
}

void PlogGroundProgramBuilder::addAtomExternalToBackend(PlogGroundProgramBuilder::GRule &rule) {
    // we need  to store the mapping from the pair <ATTID, AID> to ATOMS in Clingo
    const atom_t hsymbolid =  *rule.head.begin();
    Clingo::Symbol hsymbol = symbols[hsymbolid];
    Atom_t atom = getGroundPlogAtom(hsymbol);
    unsigned ex_atom_id = (unsigned) abs(*rule.body.begin());
    out.atomExternal(atom.attid, atom.valid, ex_atom_id);
}


void PlogGroundProgramBuilder::registerAtomInBackend(unsigned int &atom_id) {
    Clingo::Symbol hsymbol = symbols[atom_id];
    Atom_t atom = getGroundPlogAtom(hsymbol);
    out.registerLiteral(atom_id, atom.attid, atom.valid, false);
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


    // the loop is needed because gringo may reorder the atoms in the rule's body!

    Clingo::literal_t lit = body[body.size()-1];
    if ((abs(lit)) >= symbols->size() || symbols->at(abs(lit)) == Clingo::Symbol()) {
            return false;
    }
    Clingo::Symbol s = this->symbols->at(abs(lit));
    return getExternalSymbolType(s) == ExternalSymbolType::Rule;
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
    if(head.size()==0 || *head.begin() >=symbols->size())
        return Clingo::Symbol();
    return symbols->at(*head.begin());
}



ExternalSymbolType PlogGroundProgramBuilder::GRule::getExternalSymbolType(Clingo::Symbol &hs) {
    if(hs == Clingo::Symbol()) {
        return ExternalSymbolType ::None;
    }
    if(strcmp(hs.name(),"__ext")!=0)
        return ExternalSymbolType ::None;
    Clingo::Symbol firstArg = *hs.arguments().begin();
    std::string firstArgStr = firstArg.to_string();
    if(isdigit(firstArgStr[0]))
        return ExternalSymbolType :: Rule;
    else
        return ExternalSymbolType :: Atom;
}

bool PlogGroundProgramBuilder::GRule::isAtomExternal() {
    //  the rule is an atom external if
    // the last atom in the body of the form ext(t,...) where t is not  a number
    if(body.size()==0)
        return false;
    Clingo::literal_t lit = body[body.size()-1];
    if((abs(lit)) >= symbols->size() || symbols->at(abs(lit)) == Clingo::Symbol()) {
        return false;
    }
    Clingo::Symbol s = this-> symbols->at(abs(lit));
    return getExternalSymbolType(s) == ExternalSymbolType :: Atom;
}

void PlogGroundProgramBuilder::GRule::normalize() {
     assert(symbols!= nullptr);
    for(int i=0;i<body.size();i++) {
        Clingo::literal_t lit = body[i];
        if ((abs(lit)) >= symbols->size() || symbols->at(abs(lit)) == Clingo::Symbol()) {
            continue;
        }
        Clingo::Symbol s = this->symbols->at(abs(lit));
        if (getExternalSymbolType(s) != ExternalSymbolType::None) {
            std::swap(body[i], body[body.size()-1]);
            break;
        }
    }
}
