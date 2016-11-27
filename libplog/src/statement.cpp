//
// Created by iensen on 10/14/16.
//
#include<plog/input/statement.h>
#include<gringo/input/statement.hh>
#include<gringo/locatable.hh>
#include<src/input/nongroundgrammar/grammar.hh>
#include <sstream>

using Gringo::make_locatable;
using Gringo::gringo_make_unique;
using Gringo::FunctionTerm;
using Gringo::VarTermSet;
using Gringo::ValTerm;
using Gringo::VarTerm;
using Gringo::Symbol;
using Gringo::Location;
using Gringo::make_locatable;
using Gringo::Input::PredicateLiteral;
using GStatement = Gringo::Input::Statement;
using GStatementType = Gringo::Input::StatementType ;
using Gringo::Input::SimpleHeadLiteral;
using Gringo::Input::SimpleBodyLiteral;
using USimpleHeadLit = std::unique_ptr<SimpleHeadLiteral>;
// TODO: move all "locations" to a static variable
// TODO: add consts to function signatures (expecially those which are unique pointers references)
int Statement::rule_id = 0;
const Clingo::Location Statement::defaultLoc = {"<test>", "<test>", 1, 1, 1, 1};


Statement::Statement(ULit &&head, ULitVec &&body):head_(std::move(head)),body_(std::move(body)),type_(StatementType::RULE){

}

Statement::Statement(ULit &&head, ULitVec &&body, UProb &&prob):head_(std::move(head)),body_(std::move(body)),probability_(std::move(prob)),type_(StatementType::PR_ATOM){

}

Statement::Statement(ULit &&query):head_(std::move(query)),type_(StatementType::QUERY) {

}

void Statement::print(std::ostream &out) const {
    throw "not implemented yet";
}

void Statement::check(Logger &log) const {
    throw "not implemented yet";
}

void Statement::replace(Defines &dx) {
    throw "not implemented yet";
}

void Statement::toGround(ToGroundArg &x, UStmVec &stms) const {
    throw "not implemented yet";
}

Statement::~Statement() {
    // need to remove numbuf and denumbuf if they were created!
    throw "not implemented yet";
}


// for a(t) = y, return <a(t,y), true>
// for a(t) != y, return <a(t,y), false>
// to do: get rid of this and construct clingo terms directly
std::pair<Gringo::UTerm,bool>  Statement::term(ULit & lit) {
    FunctionTerm * fterm = dynamic_cast<FunctionTerm*>(lit->lt.get());

    String name = fterm->name;
    UTermVec& args = fterm->args;
    std::unique_ptr<Term> ut(lit->rt->clone());
    args.push_back(std::move(ut));
    Gringo::UTerm term = make_locatable<FunctionTerm>(DefaultLocation(), name,clone(args));
    bool pos = lit->rel==Relation::EQ;
    return {std::move(term),pos};
}





StatementType Statement::getType() {
    return type_;
}



Clingo::AST::Statement Statement::toGringoAST(const UAttDeclVec & attdecls, const USortDefVec &sortDefVec) {
    switch(type_) {
        case StatementType::PR_ATOM: return prAtomToGringoAST(attdecls, sortDefVec);
        case StatementType::QUERY:   return queryToGringoAST();
        default: return ruleToGringoAST(attdecls, sortDefVec);
    }
}

Clingo::AST::Term Statement::termToClingoTerm(const UTerm & term) {
    std::stringstream stream;
    term.get()->print(stream);

    Clingo::Location loc("<test>", "<test>", 1, 1, 1, 1);

    // if it is a function term:
    FunctionTerm * fterm = dynamic_cast<FunctionTerm*>(term.get());

    if (fterm) {
        String name = fterm->name;
        UTermVec fargs = this->clone(fterm->args);
        std::vector<Clingo::AST::Term> args;
        for(const UTerm &t: fargs) {
            args.push_back(termToClingoTerm(t));
        }
        auto f_ = Clingo::AST::Function{name.c_str(), args};
        return {loc,f_};
    }

    // if term is a variable

    VarTerm * varT = dynamic_cast<VarTerm*>(term.get());

    if (varT) {
        String name = varT->name;
        //printf("%s\n",varT->name.c_str());
        auto f_ = Clingo::AST::Variable{name.c_str()};
        return {loc,f_};
    }

    // if term is a valterm:

    ValTerm * valT = dynamic_cast<ValTerm*>(term.get());

    if (valT) {
        std::stringstream ss;
        valT->print(ss);
        Clingo::Symbol sym = Clingo::parse_term(stream.str().c_str());
        return {loc,sym};
    }

    // bin op and un op terms go here

    throw std::logic_error("cannot convert a term");

}

// TODO: rename sortDefVec
Clingo::AST::Statement Statement::prAtomToGringoAST(const UAttDeclVec & attdecls, const USortDefVec &sortDefVec) {
    // construct head:
    Clingo::Location loc("<test>", "<test>", 1, 1, 1, 1);
    std::vector<Clingo::AST::Term> args;
    args.push_back(termToClingoTerm(head_->lt));
    args.push_back(termToClingoTerm(head_->rt));
    std::stringstream stream;
    stream << probability_->getNum();
    args.push_back(Clingo::AST::Term{loc,Clingo::String(stream.str().c_str())});
    stream.str("");
    stream << probability_->getDenum();
    args.push_back(Clingo::AST::Term{loc,Clingo::String(stream.str().c_str())});
    Clingo::AST::Function f_ = {"pr", args};
    Clingo::AST::Term f_t{loc, f_};
    Clingo::AST::Literal f_l{loc, Clingo::AST::Sign::None, f_t};
    Clingo::AST::Rule f_r{{loc, f_l}, gringobodyast(attdecls, sortDefVec)};
    return {loc, f_r};

}

Clingo::AST::Statement Statement::queryToGringoAST() {
    Clingo::Location loc("<test>", "<test>", 1, 1, 1, 1);
    std::vector<Clingo::AST::Term> args;
    auto   queryargs = term(head_);
    args.push_back(termToClingoTerm(queryargs.first));
    args.push_back(queryargs.second?Clingo::AST::Term{loc,Clingo::Id("true")}:Clingo::AST::Term{loc,Clingo::Id("false")});
    Clingo::AST::Function f_ = {"query", args};
    Clingo::AST::Term f_t{loc, f_};
    Clingo::AST::Literal f_l{loc, Clingo::AST::Sign::None, f_t};
    Clingo::AST::Rule f_r{{loc, f_l}, std::vector<Clingo::AST::BodyLiteral>()};
    return {loc, f_r};
}

Clingo::AST::Statement Statement::ruleToGringoAST(const UAttDeclVec & attdecls, const USortDefVec &sortDefVec) {
    //std::cout << "head" <<*head_.get();
    Clingo::Location loc("<test>", "<test>", 1, 1, 1, 1);
    auto    fterm = term(head_);
    Clingo::AST::Term f_ = termToClingoTerm(fterm.first);
    Clingo::AST::Literal f_l{loc, Clingo::AST::Sign::None, f_};
    Clingo::AST::Rule f_r{{loc, f_l}, gringobodyast(attdecls, sortDefVec)};

    //std::cout << f_r << std::endl;
    return {loc, f_r};
}




// do not pass e-literal here!
std::vector<Clingo::AST::BodyLiteral> Statement::getSortAtoms(const ULit & lit, const USortDefVec &sortDefVec,const UAttDeclVec & attdecls) {
    // add assert that it is not an e-literal

    std::vector<Clingo::AST::BodyLiteral> result;

    String attrName = lit->getAttrName();
    if(attrName == "") {
        return {};
    }
    FunctionTerm * fterm = dynamic_cast<FunctionTerm*>(lit->lt.get());
    if(attrName == "random" || attrName == "pr") {
        // take the term from the first argument!
        fterm = dynamic_cast<FunctionTerm*>(fterm->args[0].get());
        attrName = fterm->name;
    }


   // refactor common code:
    if(fterm) {
        std::vector<String> argSorts = findArgSorts(attrName, attdecls);
        const UTermVec  & targs = fterm->args;
        for(int i=0; i< argSorts.size()-1;i++) {
            // for now assume attribute declaration may only contain sort names.
            String sortName = argSorts[i];
            std::vector<Clingo::AST::Term> args;
            std::unique_ptr<Term> ut(targs[i]->clone());
            args.push_back(termToClingoTerm(ut));
            Clingo::AST::BodyLiteral bodylit = make_body_lit(concat('_',sortName),args);
            result.push_back(bodylit);
        }
        // add the sort for the value:
        std::vector<Clingo::AST::Term> args;
        std::unique_ptr<Term> ut(lit->rt->clone());
        args.push_back(termToClingoTerm(ut));
        String sortName = argSorts[argSorts.size()-1];
        Clingo::AST::BodyLiteral bodylit = make_body_lit(concat('_',sortName),args);
        result.push_back(bodylit);
    }

    return result;



}

std::vector<Clingo::AST::BodyLiteral> Statement::gringobodyast(const UAttDeclVec & attdecls, const USortDefVec &sortDefVec) {
    Clingo::Location loc("<test>", "<test>", 1, 1, 1, 1);
    std::vector<Clingo::AST::BodyLiteral> resvec;

    for (auto& lit: body_) {
        resvec.push_back(gringobodyelast(lit));
    }

    // add sorts here

    // add sorts for the head
    std::vector<Clingo::AST::BodyLiteral> sortAtoms = getSortAtoms(head_, sortDefVec, attdecls);
    resvec.insert(resvec.end(),resvec.begin(), resvec.end());

    // add sorts for the body:


    // add external __ext(id, X1,...,Xn) to the body of the rule
    std::vector<Clingo::AST::Term> args;

    Clingo::AST::Term idarg = Clingo::AST::Term{loc,Clingo::Id(int_to_str(rule_id).c_str())};
    args.push_back(idarg);
    ++rule_id;
    // insert all the variables
    auto varstrs = getVariables();
    for(const std::string &var: varstrs) {
        Clingo::AST::Term vararg = Clingo::AST::Term{loc,Clingo::AST::Variable{var.c_str()}};
        args.push_back(vararg);
    }

    resvec.push_back( make_body_lit("__ext", args));

    return resvec;
}


Clingo::AST::BodyLiteral Statement::gringobodyelast(ULit &lit) {
    Clingo::Location loc("<test>", "<test>", 1, 1, 1, 1);
    ELiteral* elit = dynamic_cast<ELiteral*>(lit.get());
    std::pair<Gringo::UTerm,bool> termb = term(elit->lit);
    Clingo::AST::Term f_t = termToClingoTerm(termb.first);
    if(!termb.second) {
        throw "not implemented yet";
        // negate f_t
    }
    Clingo::AST::Literal alit{loc, Clingo::AST::Sign::None, f_t};
    return Clingo::AST::BodyLiteral{loc, elit->neg?Clingo::AST::Sign::Negation:Clingo::AST::Sign::None, alit};
}

std::string Statement::int_to_str(int n) {
    std::stringstream ss;
    ss << n;
    return ss.str();
}

std::unordered_set<std::string> Statement::getVariables() {
    auto result = getVariables(head_->lt);
    auto hrtvars = getVariables(head_->rt);
    result.insert(hrtvars.begin(), hrtvars.end());
    // add variables from the body
    for(const auto& lit:body_) {
        ELiteral* elit = dynamic_cast<ELiteral*>(lit.get());
        auto blvarsl = getVariables(elit->lit->lt);
        auto blvarsr = getVariables(elit->lit->rt);
        result.insert(blvarsl.begin(), blvarsl.end());
        result.insert(blvarsr.begin(), blvarsr.end());

    }
    return result;
}

std::unordered_set<std::string> Statement::getVariables(const UTerm &term) {
    std::unordered_set<std::string> result;
    VarTermSet vars;
    term->collect(vars);
    for(const auto &var : vars) {
        std::string varstr {var.get().name.c_str()};
        result.insert(varstr);
    }
    return result;
}

UTermVec Statement::clone(const UTermVec &vec) {
    UTermVec  res;
    for(const UTerm &term:vec) {
        std::unique_ptr<Term> ut(term->clone());
        res.emplace_back(std::move(ut));
    }
    return res;
}


// not sure if this leaks.
// does String own the memory?
String Statement::concat(char prefix, String s) {
    char* raw = new char [2 + s.length()];
    raw[0] = prefix;
    for(int i=0;i<s.length();i++) {
        raw[i+1] = s.c_str()[i];
    }
    raw[s.length()-1] = '\0';
    return String(raw);
}

Clingo::AST::BodyLiteral Statement::make_body_lit(String name, std::vector<Clingo::AST::Term> args) {
    Clingo::AST::Function f_ = {name.c_str(), args};
    Clingo::AST::Term f_t = {defaultLoc, f_};
    Clingo::AST::Literal alit{defaultLoc, Clingo::AST::Sign::None, f_t};
    return {defaultLoc,Clingo::AST::Sign::None, alit};
}

std::vector<String> Statement::findArgSorts(String attrName,const UAttDeclVec & attdecls) {
    std::vector<String> argSorts;
    // find attribute declaration:
    for(const UAttDecl& dec: attdecls) {
        if( dec->attname == attrName) {
            String ressortName = ((SortNameExpr*)dec->se.get())->name;
            for(int i=0;i< dec->svec.size();i++) {
                String sortName = ((SortNameExpr*)dec->svec.at(i).get())->name;
                argSorts.push_back(sortName);
            }
            argSorts.push_back(ressortName);
        }
    }
    return argSorts;
}

