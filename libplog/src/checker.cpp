//
// Created by iensen on 11/26/21.
//

#include "plog/checker.h"
#include "plog/input/attributedeclaration.h"
#include "plog/input/sortdefinition.h"
#include "plog/input/statement.h"
#include "plog/sortexpression.h"

const char * OBS = "obs";
const  char * DO = "do";
const char * RANDOM = "random";

namespace {

    // Return the first definition D from the vector of definitions such that
    // nameFromDef(D) == name. In case no definitions found, returns nullptr.
    // In case there are multiple such definitions, returns the first one.
    template<typename T>
    const T* getDefinition(const Gringo::String name, const std::vector<std::unique_ptr<T>> & defs,
                           std::function<const Gringo::String(const T&)> nameFromDef) {
        const T* defPtr = nullptr;
        for (auto const &def: defs) {
            if(nameFromDef(*def) == name) {
                defPtr = def.get();
                break;
            }
        }
        return defPtr;
    }

    // Retrieve all records and their arities occurring in a given sort expression.
    // For example, consider expression f(#s) + {g(a,b), c}. The function will return
    // {f/1, g/2}.
    std::unordered_set<Plog::Record> getRecords(const SortExpression* sortExpr) {
        std::unordered_set<Plog::Record> records;

        if(auto funcSortExpr = dynamic_cast<const FuncSortExpr*>(sortExpr)) {
             records.insert(Plog::Record(funcSortExpr->fname.name(), funcSortExpr->vec.size()));
        }

        if(auto binOpExpr = dynamic_cast<const BinOpSortExpr*>(sortExpr)) {
            auto lhsRecords = getRecords(binOpExpr->left.get());
            auto rhsRecords = getRecords(binOpExpr->right.get());
            records.insert(lhsRecords.begin(), lhsRecords.end());
            records.insert(rhsRecords.begin(), rhsRecords.end());
        }

        if(auto curlyBracketSortExpr = dynamic_cast<const CurlyBrackets*>(sortExpr)) {
            for(auto const& term: curlyBracketSortExpr->termvec) {
                if (auto fterm = dynamic_cast<Gringo::FunctionTerm*>(term.get())) {
                    records.insert(Plog::Record(fterm->name, fterm->args.size()));
                }
            }
        }
        return records;
    }

    std::unordered_set<Plog::Record> getRecords(const USortDefVec & sortDefs) {
        std::unordered_set<Plog::Record> records;
        for (auto const &sortDef: sortDefs) {
              auto sortExpr = sortDef->getSortExpr().get();
              auto newRecords = getRecords(sortExpr);
              records.insert(newRecords.begin(), newRecords.end());
        };
        return records;
    }

    std::unordered_set<Gringo::String> getDefinedSorts(const USortDefVec & sortDefs) {
        std::unordered_set<Gringo::String> sorts;
        for (auto const &sortDef: sortDefs) {
            sorts.insert(sortDef->getSortName());
        };
        return sorts;
    }
}

namespace Plog {

    Checker::Checker(const Program &program, Logger &log) : program(program),
           log(log), records(getRecords(program.sortdefs_)) {
    }

    void Checker::check() {
        checkSortDefs();
        checkAttributeDecls();
        checkStatements();
    }

    // Return sort definition for the sort with a given name.
    // Asserts that the program contains at least one definition.
    // In case when the program is not well formed and there
    // are several definitions, returns the first one as stored
    // in program.sortdefs_ vector.
    const SortDefinition& Checker::getSortDefinition(Gringo::String sortName) {
        std::function<const Gringo::String(const SortDefinition&)> nameFromSortDef =
                [](const SortDefinition &sortDef) {return sortDef.getSortName();};
        return *getDefinition(sortName, program.sortdefs_, nameFromSortDef);
    }

    // Return attribute declaration for the attribute with a given name.
    // In case when the program is not well formed and there
    // are several declarations, returns the first one as stored
    // in program.attdecls_ vector. In case there are no declarations,
    // returns nullptr.
    const AttributeDeclaration* Checker::getAttributeDeclaration(Gringo::String attributeName) {
        std::function<const Gringo::String(const AttributeDeclaration&)> nameFromAttDecl =
                [](const AttributeDeclaration &attDecl) {return attDecl.attname;};
       return getDefinition(attributeName, program.attdecls_, nameFromAttDecl);
    }

    // check sort definitions of the program for errors
    void Checker::checkSortDefs() {
        std::unordered_set<Gringo::String> definedSorts;
        for (auto const &sortDef: program.sortdefs_) {

            // error if this sort was already defined in previous lines:
            if (definedSorts.find(sortDef->getSortName()) != definedSorts.end()) {
                // locate previous sort definition with the same name
                auto const &prevDefinition = getSortDefinition(sortDef->getSortName());
                PLOG_REPORT(log, plog_error_sort_definition)
                    << sortDef->loc() << ": incorrect sort definition. "
                    << "The sort " << sortDef->getSortName() << " was already defined at line "
                    << prevDefinition.loc().beginLine << ". Remove one of the definitions.";
            }

            // check current sort definition
            checkSortDef(*sortDef, definedSorts);

            // insert current sort to the set of defined sorts
            definedSorts.insert(sortDef->getSortName());
        }
    }

    void Checker::checkSortDef(const SortDefinition &sortDef,
                               const std::unordered_set<Gringo::String> &definedSorts) {
        auto const &sortExpr = sortDef.getSortExpr().get();
        checkSortExpr(sortExpr, definedSorts);
    }

    void Checker::checkSortExpr(const SortExpression *sortExpr,
                                const std::unordered_set<Gringo::String> &definedSorts) {
        if (auto rangeSortExpr = dynamic_cast<const Range *>(sortExpr)) {
            checkRangeSortExpr(*rangeSortExpr);
        }
        if (auto setBinOpSortExpr = dynamic_cast<const BinOpSortExpr *>(sortExpr)) {
            checkSetBinOpSortExpr(*setBinOpSortExpr, definedSorts);
        }
        if (auto sortNameSortExpr = dynamic_cast<const SortNameExpr *>(sortExpr)) {
            checkSortNameSortExpr(*sortNameSortExpr, definedSorts);
        }
        if(auto functionSortExpr = dynamic_cast<const FuncSortExpr*>(sortExpr)) {
            checkFuncSortExpr(*functionSortExpr, definedSorts);
        }
    }

    void Checker::checkSortNameSortExpr(const SortNameExpr &sortNameSortExpr,
                                        const std::unordered_set<Gringo::String> &definedSorts) {
        if (definedSorts.find(sortNameSortExpr.name) == definedSorts.end()) {
            auto loc = sortNameSortExpr.loc();
            PLOG_REPORT(log, plog_error_sort_definition)
                << loc << ": undefined sort #" << sortNameSortExpr.name << ".";
        }
    }

    void Checker::checkFuncSortExpr(const FuncSortExpr & funcSortExpr,
                                        const std::unordered_set<Gringo::String> &definedSorts) {
        for(auto const& varSortExpr: funcSortExpr.vec) {
            checkSortExpr(varSortExpr->expr.get(), definedSorts);
        }
    }


    void Checker::checkSetBinOpSortExpr(const BinOpSortExpr &binopSortExpr,
                                        const std::unordered_set<Gringo::String> &definedSorts) {

        auto lhs = binopSortExpr.left.get();
        checkSortExpr(lhs, definedSorts);
        auto rhs = binopSortExpr.right.get();
        checkSortExpr(rhs, definedSorts);
    }

    void Checker::checkRangeSortExpr(const Range &rSortExpr) {
        auto const &fromTerm = rSortExpr.from;
        auto const &toTerm = rSortExpr.to;
        bool hasUndefinedSymbols = false;
        int fromNum = fromTerm->toNum(hasUndefinedSymbols, glog);
        int toNum = toTerm->toNum(hasUndefinedSymbols, glog);
        if (hasUndefinedSymbols) {
            // Despite the name "check", this actually sets 'hasError' flag on the logger object
            // All we want to do here is to say that an error has occurred, so that the solving
            // process does not continue.
            log.check(plog_error_sort_definition);
        }
        // report error if in range expression num1..num2, num2 < num1.
        if (toNum < fromNum) {
            PLOG_REPORT(log, plog_error_sort_definition)
                << rSortExpr.loc() << ": invalid range definition. "
                << "The second number in the range must be greater or equal to the first." << "\n";
        }
    }

    // Check attribute terms of the program for correctness.
    // Firstly, check that no attribute is defined twice. Secondly, check each
    // declaration independently (see checkAttributeDecl function).
    void Checker::checkAttributeDecls() {
        const std::unordered_set<Gringo::String> programSorts = getDefinedSorts(program.sortdefs_);
        std::unordered_set<Gringo::String> definedAttributes;
        for (auto const &attDecl: program.attdecls_) {
            // error if this attribute was already defined in previous lines:
            if (definedAttributes.find(attDecl->attname) != definedAttributes.end()) {
                // locate previous sort definition with the same name
                auto const prevDeclaration = getAttributeDeclaration(attDecl->attname);
                assert(prevDeclaration);
                PLOG_REPORT(log, plog_error_attribute_declaration)
                    << attDecl->loc()
                    << ": attribute " << attDecl->attname << " was already defined in line "
                    << prevDeclaration->loc().beginLine << ". Remove one of the definitions.";
            }

            // check current attribute declaration (independently from others)
            checkAttDecl(*attDecl, programSorts);

            // insert current sort to the set of defined sorts
            definedAttributes.insert(attDecl->attname);
        }
    }

    // Check given attribute declaration for errors
    // @param declaration declaration of the attribute term representing #a: s1,...,sn-> s
    //        where s1,...,sn,s are sort expressions
    // @param programSorts set of all sort names defined by the program
    //
    void Checker::checkAttDecl(const AttributeDeclaration &declaration,
                               const std::unordered_set<Gringo::String> & programSorts) {

        // check if attribute name is not DO, OBS or RANDOM:
        if(declaration.attname == DO || declaration.attname == OBS || declaration.attname == RANDOM) {
            PLOG_REPORT(log, plog_error_attribute_declaration) << declaration.loc() << ":"
                                                               << " the name of attribute " << declaration.attname
                                                               << " coincides with a built-in P-log keyword." <<
                                                                  " Do not name attributes as 'do', 'obs' or 'random'.";
        }

        // check if record with the same name and arity exists. If so, produce an error to avoid
        // resolve ambiguity in, for example,  f(a) = 5 (is this record "f(a)", or attribute term?)
        Plog::Record record(declaration.attname, declaration.svec.size());
        if(records.find(record) != records.end()) {
            PLOG_REPORT(log, plog_error_attribute_declaration) << declaration.loc() << ":"
                << " the definition of attribute " << declaration.attname
                << " conflicts with a record of the same name occurring in sort definitions of the program." <<
                   " Rename the attribute to resolve the issue.";
        }

        // check the sort expressions used to define sorts of attribute's arguments
        for(auto const & sortExpr: declaration.svec) {
            checkSortExpr(sortExpr.get(), programSorts);
        }
        // check the sort expression used to define the values of the attribute
        checkSortExpr(declaration.se.get(), programSorts);
    }

    void Checker::checkStatements() {
       for(auto const &stmt: program.stms_) {
           checkStatement(*stmt);
       }
    }

    void Checker::checkStatement(const Statement &statement) {
       switch(statement.getType()) {
           case StatementType::RULE: {
               if(statement.head_->getAttrName()==OBS) {
                   checkObsStatement(statement);
               } else if(statement.head_->getAttrName()==DO) {
                   checkDoStatement(statement);
               } else {
                   checkRule(statement);
               }
               break;
           }
           case StatementType::CRRULE:
               checkCRRule(statement);
               break;
           case StatementType::PR_ATOM:
               checkPrAtom(statement);
               break;
           case StatementType::QUERY:
               checkQuery(statement);
               break;
       }
    }

    // Check a rule of the form head :- body, where head is not formed by obs or do.
    void Checker::checkRule(const Statement& statement) {
         checkHead(statement.head_);
         checkBody(statement.body_);
    }

    void Checker::checkCRRule(const Statement& statement) {

    }

    void Checker::checkPrAtom(const Statement& statement) {

    }

    void Checker::checkQuery(const Statement& statement) {

    }

    // Returns true if given term is a zero value term
    // Warning: Call only if you are sure that term is a constant value term!
    //          The function will print errors to stderr if it's not the case
    bool Checker::isZeroValTerm(const Gringo::Term* term) {
        auto valTerm =  dynamic_cast<const Gringo::ValTerm*>(term);
        if(!valTerm) {
            return false;
        }
        return valTerm->isZero(glog);
    }

    void Checker::checkHead(const ULit &head) {
        auto attrName = head->getAttrName();

        // the grammar requires that the head is literal with =
        assert(head->rel == Relation::EQ);

        if (attrName == RANDOM) {
            checkRandomAtom(head);
            return;
        }

        // this head is a part of a constraint?
        bool isConstraint = false;

        // constraints are constructed as 0!=0, we need to recognize it here!
        auto headLeftTerm = static_cast<Gringo::Term *>(head->lt.get());
        if (!headLeftTerm->isNotNumeric()) {
            // assert that the term we have is actually 0 != 0:
            assert(isZeroValTerm(headLeftTerm));
            auto headRightTerm = static_cast<Gringo::Term *>(head->rt.get());
            assert(isZeroValTerm(headRightTerm));
            isConstraint = true;
        }
        if (!isConstraint) {
            checkAttributeAtom(head);
        }
    }

    void Checker::checkBody(const ULitVec &vector) {

    }

    void Checker::checkObsStatement(const Statement &statement) {

    }

    void Checker::checkDoStatement(const Statement &statement) {

    }

    void Checker::checkRandomAtom(const ULit &uniquePtr) {

    }

    // Checks an atom of the form a(t) = y, where a is an attribute term of the program
    void Checker::checkAttributeAtom(const ULit &atom) {
        auto attrName = atom->getAttrName();
        auto attrDecl = getAttributeDeclaration(attrName);
        if(attrDecl == nullptr) {
            PLOG_REPORT(log, plog_error_statement) << atom->loc() << ":"
            << " literal is formed by an undeclared attribute " << attrName << ".";
        }
    }
}