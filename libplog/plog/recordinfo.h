//
// Created by iensen on 11/27/21.
//

#ifndef TESTS_RECORDINFO_H
#define TESTS_RECORDINFO_H

#include<gringo/symbol.hh>

namespace Plog {
    struct Record {
        Record(Gringo::String recordName, int arity): recordName(recordName), arity(arity) {};
        Gringo::String recordName;
        int arity;
        bool operator ==(const Record &r) const {
            return r.recordName == recordName && r.arity == arity;
        }
    };
}
// custom specialization of std::hash
template<>
struct std::hash<Plog::Record>
{
    std::size_t operator()(Plog::Record const& r) const noexcept
    {
        std::size_t h1 = r.recordName.hash();
        return h1 ^ (static_cast<size_t>(r.arity) << 1u);
    }
};

#endif //TESTS_RECORDINFO_H