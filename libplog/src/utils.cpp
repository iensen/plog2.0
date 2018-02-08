//
// Created by KR_Lab on 11/26/16.
//
#include<plog/input/utils.h>

using Gringo::FunctionTerm;
using Gringo::String;
using Gringo::VarTerm;
using Gringo::ValTerm;
using Gringo::UTermVec;
using Gringo::Term;
using Gringo::BinOpTerm;
using Gringo::BinOp ;


static Clingo::AST::BinaryOperator gringoToClingoBinOp(Gringo::BinOp op) {
        switch(op) {
            case Gringo::BinOp::ADD: return Clingo::AST::BinaryOperator::Plus;
            default:throw "not implemented";

              }
}

Clingo::AST::Term negate(const UTerm &term) {
    // if it is a function term:
    FunctionTerm * fterm = dynamic_cast<FunctionTerm*>(term.get());

    if (fterm) {
        String name = fterm->name;
        UTermVec fargs = clone(fterm->args);
        std::vector<Clingo::AST::Term> args;
        for(const UTerm &t: fargs) {
            args.push_back(termToClingoTerm(t));
        }
        auto f_ = Clingo::AST::Function{name.c_str(), args};
        return {defaultLoc,f_};
    }

}

Clingo::AST::Term termToClingoTerm(const UTerm & term) {

    if(term.get()== nullptr) {
        printf("WTF!\n");
    }
    std::stringstream stream;
    term.get()->print(stream);


    // if it is a function term:
    FunctionTerm * fterm = dynamic_cast<FunctionTerm*>(term.get());

    if (fterm) {
        String name = fterm->name;
        UTermVec fargs = clone(fterm->args);
        std::vector<Clingo::AST::Term> args;
        for(const UTerm &t: fargs) {
            args.push_back(termToClingoTerm(t));
        }
        auto f_ = Clingo::AST::Function{name.c_str(), args};
        return {defaultLoc,f_};
    }

    // if term is a variable

    VarTerm * varT = dynamic_cast<VarTerm*>(term.get());

    if (varT) {
        String name = varT->name;
        //printf("%s\n",varT->name.c_str());
        auto f_ = Clingo::AST::Variable{name.c_str()};
        return {defaultLoc,f_};
    }

    // if term is a valterm:

    ValTerm * valT = dynamic_cast<ValTerm*>(term.get());

    if (valT) {
        std::stringstream ss;
        valT->print(ss);
        Clingo::Symbol sym = Clingo::parse_term(stream.str().c_str());
        return {defaultLoc,sym};
    }


    BinOpTerm * bterm = dynamic_cast<BinOpTerm*>(term.get());
    if(bterm) {
        UTerm leftc(bterm->left->clone());
        UTerm rightc(bterm->right->clone());
        return {defaultLoc, Clingo::AST::BinaryOperation{gringoToClingoBinOp(bterm->op),termToClingoTerm(leftc),termToClingoTerm(rightc)}};
    }

    //unary ops go here

    throw std::logic_error("cannot convert a term");
}


UTermVec clone(const UTermVec &vec) {
    UTermVec  res;
    for(const UTerm &term:vec) {
        std::unique_ptr<Term> ut(term->clone());
        res.emplace_back(std::move(ut));
    }
    return res;
}


std::string term_to_string (Clingo::AST::Term term) {
    std::stringstream ss;
    ss << term;
    std::string res;
    ss >> res;
    return res;
}

// not sure if this leaks.
// does String own the memory?
String concat(char prefix, String s) {
    char* raw = new char [2 + s.length()];
    raw[0] = prefix;
    for(int i=0;i<s.length();i++) {
        raw[i+1] = s.c_str()[i];
    }
    raw[s.length()+1] = '\0';
    return String(raw);
}


std::string int_to_str(int n) {
    std::stringstream ss;
    ss << n;
    return ss.str();
}

int str_to_int(std::string str) {
    std::stringstream ss;
    ss << str;
    int n;
    ss >> n;
    return n;
}

// given a term,
// if it is of the form f(t1,..,tn), return f
// if it is of the form a, return a
Gringo::String getAttrName(const UTerm &term) {
    String termName = "";
    FunctionTerm * faterm = (FunctionTerm*) term.get();

    if(faterm   && faterm->args.size()>0) {
        termName = faterm->name;
    }
    ValTerm *vaterm = (ValTerm*)term.get();
    if(( !faterm || faterm->args.size()==0) && vaterm) { // for some reason both casts work!
        if(vaterm->value.type()==Gringo::SymbolType::Fun)
           termName = vaterm->value.name();
    }
    return termName;
}


// given a term,
// if it is of the form f(t1,..,tn), return a vector of clingo terms {t1,,,tn}
// if it is of the form a, return {}
std::vector<Clingo::AST::Term> getAttrArgs(const UTerm &term) {
    FunctionTerm * faterm = (FunctionTerm*) term.get();
    String termName = "";
    std::vector<Clingo::AST::Term> result;
    if(faterm) {
        for(const UTerm &arg: faterm->args) {
            result.emplace_back(termToClingoTerm(arg));
        }
    }
    return result;
}




std::pair<const USortExprVec &, const USortExpr &> getSorts(String attrName, const UAttDeclVec &attdecls) {
    for (const auto& decl:attdecls) {
        if(decl.get()->attname == attrName) {
            return {decl.get()->svec, decl.get()->se};
        }
    }
    throw std::logic_error("attribute not found");
}

const USortExpr &getResultSort(String attrName, const UAttDeclVec &attdecls) {
    return getSorts(attrName,attdecls).second;
}

const USortExprVec &getArgSorts(String attrName, const UAttDeclVec &attdecls) {
    return getSorts(attrName,attdecls).first;
}


