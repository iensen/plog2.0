//
// Created by evgenii on 12/16/16.
//

//
// Created by evgenii on 12/16/16.
//

#include<groundplog/dependency_graph.h>



GroundPlog::DepGraph::DepGraph(Program *pr) {


    // add acrs from rules:

    for(RegularRule r : pr->rules) {
        for(Lit_t bl:r.body) {
           addArc(bl.attid,r.head.attid);
        }
    }

    // add arcs from random selection rules:

    for(auto r: pr->randomrules) {
        for(Lit_t bl:r.body) {
            addArc(bl.attid,r.head.first);
        }
    }

    // add arcs from pr-atoms;

    for(auto prat: pr->pratoms) {
        for(Lit_t bl: prat.body) {
            addArc(bl.attid,prat.head.attid );
        }
    }
}

void GroundPlog::DepGraph::addArc(GroundPlog::ATTID from, GroundPlog::ATTID to) {
   if (from >= arcs.size()) {
       arcs.resize(2*from +1);
   }
    arcs[from].push_back(to);
}

std::vector<GroundPlog::ATTID> GroundPlog::DepGraph::children(GroundPlog::ATTID node) {
    if(node >= arcs.size())
        return {};
    else
        return arcs[node];
}
