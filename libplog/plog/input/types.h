//
// Created by iensen on 9/16/16.
//

#ifndef PLOG_TYPES_H
#define PLOG_TYPES_H

#include "probability.h"
#include "attributedeclaration.h"
#include "sortdefinition.h"
#include<vector>
#include <memory>

struct Statement;
using UStm = std::unique_ptr<Statement>;
using USortDef = std::unique_ptr<SortDefinition>;
using UAttDecl = std::unique_ptr<AttributeDeclaration>;
using UStmVec = std::vector<UStm>;
using USortDefVec = std::vector<USortDef>;
using UAttDeclVec = std::vector<UAttDecl>;

using UProb =  std::unique_ptr<Probability>;
#endif //PLOG_TYPES_H
