//
// Created by iensen on 8/17/16.
//

#ifndef PLOG_DEPENDENCY_GRAPH_H
#define PLOG_DEPENDENCY_GRAPH_H

#include "program.h"
#include<vector>


namespace  GroundPlog {
class DepGraph {
   std::vector< std::vector<ATTID > >  arcs;
public:
    DepGraph(Program *pr);
};
} // namespace Asp
#endif //PLOG_DEPENDENCY_GRAPH_H
