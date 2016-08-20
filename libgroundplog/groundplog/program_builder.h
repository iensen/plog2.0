//
// Created by iensen on 8/16/16.
//

#ifndef PLOG_PROGRAM_BUILDER_H
#define PLOG_PROGRAM_BUILDER_H

#include "shared_context.h"
#include<groundplog/literal.h>
#include <iosfwd>
#include<vector>

namespace GroundPlog {
//! Interface for defining an input program.
    class ProgramBuilder {
    public:

        ProgramBuilder();

        virtual ~ProgramBuilder();
        //! Starts the definition of a program.
        /*!
         * This function shall be called exactly once before a new program is defined.
         * It discards any previously added program.
         *
         * \param ctx The context object in which the program should be stored.
         */
        bool startProgram(SharedContext &ctx);

        //! Parses the given stream as a program of type() and adds it to this object.
        bool parseProgram(std::istream &prg);

        //! Unfreezes a currently frozen program.
        bool updateProgram();

        //! Loads the program into the shared context passed to startProgram().
        bool endProgram();
        //! Returns any assumptions that shall hold during solving.
        /*!
         * \pre frozen()
         */
        void getAssumptions(std::vector<Literal> &out) const;


        //! Returns true if the program is currently frozen.
        bool frozen() const { return frozen_; }

        //! Returns true if the program is not conflicting.
        virtual bool ok() const;

        //! Returns the stored context object.
        SharedContext *ctx() const { return ctx_; }


    protected:

        void setFrozen(bool frozen) { frozen_ = frozen; }

        void setCtx(SharedContext *x) { ctx_ = x; }

        void markOutputVariables() const;

    private:

        ProgramBuilder(const ProgramBuilder &);

        ProgramBuilder &operator=(ProgramBuilder &);

        virtual bool doStartProgram()                    = 0;

        virtual bool doUpdateProgram()                   = 0;

        virtual bool doEndProgram()                      = 0;

        virtual void doGetAssumptions(std::vector<Literal> &out) const = 0;

        virtual int doType() const = 0;


        SharedContext *ctx_;
        bool frozen_;
    };
}


#endif //PLOG_PROGRAM_BUILDER_H
