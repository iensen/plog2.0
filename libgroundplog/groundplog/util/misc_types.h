//
// Created by iensen on 8/16/16.
//

#ifndef PLOG_MISC_TYPES_H
#define PLOG_MISC_TYPES_H

#include <groundplog/util/platform.h>
#include<clasp/util/misc_types.h>

namespace  GroundPlog {
    struct Event {
        enum Subsystem {
            subsystem_solve = 3//???
        };

        explicit Event(Subsystem sys, uint32 evId) : system(sys), op(0),
                                                     id(evId) {}

        uint32 system : 2; // one of Event::Subsystem - subsystem that produced the event
        uint32 op     : 8; // operation that triggered the event
        uint32 id     : 16;// type id of event
        static uint32 nextId();
    };


    template<class T>
    struct Event_t : Event {
        Event_t(Subsystem sys) : Event(sys, id_s) {}

        static const uint32 id_s;
    };


    using Ownership_t =Clasp::Ownership_t;
    template<class T, class D = Clasp::DeleteObject> using SingleOwnerPtr=Clasp::SingleOwnerPtr<T, D>;
}
#endif //PLOG_MISC_TYPES_H
