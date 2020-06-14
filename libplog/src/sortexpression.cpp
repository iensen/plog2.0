//
// Created by iensen on 10/2/16.
//

#include <plog/sortexpression.h>
#include<plog/input/utils.h>
#include<plog/input/sortdefinition.h>

Range::Range(UTerm &&from, UTerm &&to):from(std::move(from)), to(std::move(to)) {

}


std::vector<Clingo::AST::Term> Range::generate( const USortDefVec &sortDefVec) {
    bool undefined;
    Gringo::Logger log;

    int n_from = from->toNum(undefined,log);
    int n_to =  to->toNum(undefined,log);

    std::vector<Clingo::AST::Term> result;
    for(int i=n_from;i<=n_to;i++) {
        Clingo::Symbol sym = Clingo::Number(i);
        result.push_back({defaultLoc,sym});
    }
    return result;

}

std::string Range::toString() const{
    throw "not implemented yet";
}

Concatenation::Concatenation(USortExprVec vec):sexprvec(std::move(vec)) {

}


std::vector<Clingo::AST::Term> Concatenation::generate( const USortDefVec &sortDefVec) {
    throw "not implemented yet";
}

std::string Concatenation::toString() const {
    return std::string();
}

struct ClingoTermHash {
    size_t operator()(const Clingo::AST::Term& t) const
    {
        std::stringstream  ss;
        ss << t;
        return std::hash<std::string>{}(ss.str());
    }
};

struct ClingoTermEquality {
    size_t operator()(const Clingo::AST::Term& t1,const Clingo::AST::Term& t2) const
    {
        std::stringstream  ss;
        ss << t1;
        auto term1Str = ss.str();
        ss.str("");
        ss.clear();
        ss << t2;
        auto term2Str = ss.str();
        return term1Str == ss.str();
    }
};

std::vector<Clingo::AST::Term> BinOpSortExpr::generate( const USortDefVec &sortDefVec) {
    std::vector<Clingo::AST::Term> lhsTerms = left->generate(sortDefVec);
    std::vector<Clingo::AST::Term> rhsTerms = right->generate(sortDefVec);
    std::unordered_set<Clingo::AST::Term,ClingoTermHash,  ClingoTermEquality> rhsTermsSet(rhsTerms.begin(), rhsTerms.end());
    std::vector<Clingo::AST::Term> result;
    switch(op) {
        // no C++17, so just do it stupid way:
        case SEBinOp::INTERSECT: {
            for (auto const& lElement : lhsTerms) {
                if (rhsTermsSet.count(lElement) > 0) {
                    result.push_back(lElement);
                }
            }
            break;
        }
        case SEBinOp::SUBTRACT:  {
            for (auto const& lElement : lhsTerms) {
                if (rhsTermsSet.count(lElement) == 0) {
                    result.push_back(lElement);
                }
            }
            break;
        }
        default:
            assert(op == SEBinOp::UNION);
            result.insert(result.end(), lhsTerms.begin(), lhsTerms.end());
            result.insert(result.end(), rhsTerms.begin(), rhsTerms.end());
    }
    return result;
}

std::string BinOpSortExpr::toString() const{
    return std::string();
}

std::vector<Clingo::AST::Term> FuncSortExpr::generate( const USortDefVec &sortDefVec, std::vector<Clingo::AST::Term> &args) {
   size_t argIndex = args.size();
   if(argIndex >= vec.size()) {
       return {{defaultLoc, Clingo::AST::Function{fname.name().c_str(), args, false}}};
   } else {
       std::vector<Clingo::AST::Term> ithArgs = vec.at(argIndex)->expr->generate(sortDefVec);
       std::vector<Clingo::AST::Term> result;
       for(auto const &t: ithArgs) {
           args.push_back(t);
           auto terms = generate(sortDefVec, args);
           result.insert(result.end(), terms.begin(), terms.end());
           args.pop_back();
       }
       return result;
   }

}

std::vector<Clingo::AST::Term> FuncSortExpr::generate( const USortDefVec &sortDefVec) {
    std::vector<Clingo::AST::Term> argSet;// just a holder for current set of arguments
    return generate(sortDefVec,argSet);
}

std::string FuncSortExpr::toString() const {
    throw "not implemented yet";
}

void BinOpCondition::print(std::ostream &out) const {
    throw "not implemented yet";
}

void UnaryCondition::print(std::ostream &out) const {
    throw "not implemented yet";
}


std::vector<Clingo::AST::Term> SortNameExpr::generate( const USortDefVec &sortDefVec) {
    for(const USortDef& def : sortDefVec) {
        if(def->getSortName()==this->name) {
            return def->getSortExpr()->generate(sortDefVec);
        }
    }
}

std::string SortNameExpr::toString() const {
    return std::string(name.c_str());
}

std::vector<Clingo::AST::Term> CurlyBrackets::generate( const USortDefVec &sortDefVec) {
    std::vector<Clingo::AST::Term> result;
    for(const UTerm& term: termvec) {
        result.emplace_back(termToClingoTerm(term));
    }
    return result;
}

std::string CurlyBrackets::toString() const {
    throw "not implemented yet";

}

void SortExpression::print(std::ostream &out) const {
   out << toString();
}
