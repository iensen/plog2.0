//
// Created by iensen on 9/16/16.
//

#ifndef PLOG_TYPES_H
#define PLOG_TYPES_H

#include "probability.h"

#include<vector>
#include <memory>

struct Statement;
class AttributeDeclaration;
class SortExpression;
class SortDefinition;

using UStm = std::unique_ptr<Statement>;
using USortDef = std::unique_ptr<SortDefinition>;
using UAttDecl = std::unique_ptr<AttributeDeclaration>;
using UStmVec = std::vector<UStm>;
using USortDefVec = std::vector<USortDef>;
using UAttDeclVec = std::vector<UAttDecl>;
using USortExpr = std::unique_ptr<SortExpression>;
using USortExprVec = std::vector<USortExpr>;

using UProb =  std::unique_ptr<Probability>;
#endif //PLOG_TYPES_H
