//
// Created by iensen on 9/21/16.
//

#include<plog/term.h>
#include<gringo/graph.hh>
#include<gringo/term.hh>

template<class T>
using Graph = Gringo::Graph<T>;
using Term = Gringo::Term;

void Defines::add(Location const &loc, String name, UTerm &&value, bool defaultDef, Logger &log) {
throw "not implemented yet";
}

void Defines::init(Logger &log) {
    using DefineGraph = Graph<Defines::DefMap::iterator>;
    using NodeMap     = std::unordered_map<String, DefineGraph::Node*>;

    DefineGraph graph;
    NodeMap nodes;
    for (auto it = defs_.begin(), end = defs_.end(); it != end; ++it) {
        nodes.emplace(it->first, &graph.insertNode(it));
    }
    for (auto &x : nodes) {
        Term::VarSet vals;
        std::get<2>(x.second->data->second)->collectIds(vals);
        for (auto &y : vals) {
            auto it = nodes.find(y);
            if (it != nodes.end()) { x.second->insertEdge(*it->second); }
        }
    }
    for (auto &scc : graph.tarjan()) {
        if (scc.size() > 1) {
            std::ostringstream msg;
            msg
                    << std::get<1>(scc.back()->data->second) << ": error: cyclic constant definition:\n"
                    << "  #const " << scc.back()->data->first << "=" << *std::get<2>(scc.back()->data->second) << ".\n";
            scc.pop_back();
            for (auto &x : scc) {
                msg
                        << std::get<1>(x->data->second) << ": note: cycle involves definition:\n"
                        << "  #const " << x->data->first << "=" << *std::get<2>(x->data->second) << ".\n";
            }
            PLOG_REPORT(log, plog_error_runtime) << msg.str();
        }
        for (auto &x : scc) { Term::replace(std::get<2>(x->data->second), std::get<2>(x->data->second)->replace(*this, true)); }
    }

}