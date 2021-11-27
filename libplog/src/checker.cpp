//
// Created by iensen on 11/26/21.
//

#include "plog/checker.h"
#include "plog/input/attributedeclaration.h"
#include "plog/input/sortdefinition.h"
#include "plog/sortexpression.h"

namespace {

    // Return the first definition D from the vector of definitions such that
    // nameFromDef(D) == name. Asserts that the vector contains at least one such
    // definition. In case there are multiple such definitions, returns the first one.
    template<typename T>
    const T& getDefinition(const Gringo::String name, const std::vector<std::unique_ptr<T>> & defs,
                           std::function<const Gringo::String(const T&)> nameFromDef) {
        const T* defPtr = nullptr;
        for (auto const &def: defs) {
            if(nameFromDef(*def) == name) {
                defPtr = def.get();
                break;
            }
        }
        assert(defPtr);
        return *defPtr;
    }

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
    }

    // Return sort definition for the sort with a given name.
    // Asserts that the program contains at least one definition.
    // In case when the program is not well formed and there
    // are several definitions, returns the first one as stored
    // in program.sortdefs_ vector.
    const SortDefinition& Checker::getSortDefinition(Gringo::String sortName) {
        std::function<const Gringo::String(const SortDefinition&)> nameFromSortDef =
                [](const SortDefinition &sortDef) {return sortDef.getSortName();};
        return getDefinition(sortName, program.sortdefs_, nameFromSortDef);
    }

    // Return attribute declaration for the attribute with a given name.
    // Asserts that the program contains at least one declaration.
    // In case when the program is not well formed and there
    // are several declarations, returns the first one as stored
    // in program.attdecls_ vector.
    const AttributeDeclaration& Checker::getAttributeDeclaration(Gringo::String attributeName) {
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
                << loc << ": undefined sort #" << sortNameSortExpr.name << ". "
                << "Insert a definition of sort #" << sortNameSortExpr.name
                << " before line " << loc.beginLine << ".";
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
        Gringo::Logger glog;
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
                auto const &prevDeclaration = getAttributeDeclaration(attDecl->attname);
                PLOG_REPORT(log, plog_error_attribute_declaration)
                    << attDecl->loc()
                    << ": the attribute " << attDecl->attname << " was already defined at line "
                    << prevDeclaration.loc().beginLine << ". Remove one of the definitions.";
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

        // check if record with the same name and arity exists. If so, produce an error to avoid
        // resolve ambiguity in, for example,  f(a) = 5 (is this record "f(a)", or attribute term?)
        Plog::Record record(declaration.attname, declaration.svec.size());
        if(records.find(record) != records.end()) {
            PLOG_REPORT(log, plog_error_attribute_declaration) << declaration.loc() << ":"
                << " the name and arity of declared attribute " << declaration.attname
                << " coincide with a record occurring in sort definitions of the program." <<
                   " Rename the attribute to resolve the issue.";
        }

        // check that the sort expressions used to define sorts
        for(auto const & sortExpr: declaration.svec) {
            checkSortExpr(sortExpr.get(), programSorts);
        }
    }
}