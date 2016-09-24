//
// Created by iensen on 9/16/16.
//

#include<plog/programbuilder.h>

NonGroundProgramBuilder::NonGroundProgramBuilder(Program &prg, Defines &defs):prg_(prg)
        , defs_(defs)
{

}

IdVecUid NonGroundProgramBuilder::idvec() {
    return idvecs_.emplace();
}

IdVecUid NonGroundProgramBuilder::idvec(IdVecUid uid, Location const &loc, String id) {
    idvecs_[uid].emplace_back(loc, id);
    return uid;
}

//void NonGroundProgramBuilder::block(Location const &loc, String name, IdVecUid args) {
    //prg_.begin(loc, name, idvecs_.erase(args));
    // let's leave this empty for now and see what happens
//}
