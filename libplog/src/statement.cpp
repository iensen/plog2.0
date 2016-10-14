//
// Created by iensen on 10/14/16.
//
#include<plog/input/statement.h>

Statement::Statement(ULit &&head, ULitVec &&body):head(std::move(head)),body(std::move(body)),type(StatementType::RULE){
}

Statement::Statement(ULit &&head, ULitVec &&body, UProb &&prob):head(std::move(head)),body(std::move(body)),type(StatementType::PR_ATOM){
}

Statement::Statement(ULit &&query):head(std::move(query)),type(StatementType::QUERY) {
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
    throw "not implemented yet";
}
