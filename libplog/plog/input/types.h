//
// Created by iensen on 9/16/16.
//

#ifndef PLOG_TYPES_H
#define PLOG_TYPES_H

#include "body.h"
#include "head.h"
#include "probability.h"
#include<vector>
#include <memory>

struct Statement;
using UStm = std::unique_ptr<Statement>;
using UStmVec = std::vector<UStm>;

using UProb =  std::unique_ptr<Probability>;
using UHead    = std::unique_ptr<Head>;
using UBody =   std::unique_ptr<Body>;
#endif //PLOG_TYPES_H
