//
// Created by iensen on 9/3/16.
//

#include <groundplog/program_types.h>

void GroundPlog::PrgBody::destroy() {
    this->~PrgBody();
    ::operator delete(this);
}

GroundPlog::PrgBody::~PrgBody() {
    head_ = 0;
}
