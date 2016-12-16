//
// Created by evgenii on 12/16/16.
//

#ifndef PLOG_SOLVINGRES_H
#define PLOG_SOLVINGRES_H
#include<groundplog/util/platform.h>
/////////////////////////////////////////////////////////////////////////////////////////
// GroundPlogFacade
/////////////////////////////////////////////////////////////////////////////////////////
//! Result of a solving
namespace GroundPlog {

struct SolveResult {
    //! Possible solving results.
    enum Base {
        OK = 0,
        NOTDCO    = 1, /**< Given program is not DCO.                              */
    };
    enum Ext {
        EXT_EXHAUST  = 2, /**< Search space is exhausted.            */
        EXT_INTERRUPT= 4, /**< The run was interrupted from outside. */
    };
    bool notdco()      const { return *this == NOTDCO; }
    bool exhausted()  const { return (flags & EXT_EXHAUST)   != 0; }
    bool interrupted()const { return (flags & EXT_INTERRUPT) != 0; }
    operator Base()   const { return static_cast<Base>(flags & 3u);}
    operator double() const { return (double(signal)*256.0) + flags; }
    uint8 flags;  // result flags
    uint8 signal; // term signal or 0
};
}
#endif //PLOG_SOLVINGRES_H
