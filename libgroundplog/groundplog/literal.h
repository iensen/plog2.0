//
// Created by iensen on 8/16/16.
//

#ifndef PLOG_LITERAL_H
#define PLOG_LITERAL_H
//! A literal is a variable or its negation.
/*!
 * \par Implementation:
 * A literal's state is stored in a single 64-bit integer as follows:
 *  - 32-bits   : attribute term id
 *  - 30-bits   : term id
 *  - 1-bit     : sign, 1 if negative, 0 if positive
 *  - 1-bit     : general purpose flag for marking a literal instance
 */
#include<groundplog/util/platform.h>
#include<algorithm>

namespace GroundPlog {
    //! A variable is an integer in the range [0..varMax).
    typedef uint32 ATTID;
    typedef uint32 TID;
    class Literal {
    public:
        static const uint64 sign_bit = 2u;
        static const uint64 flag_bit = 1u;

        //! The default constructor creates the positive literal of the special sentinel var.
        Literal() : rep_(0) {}

        //! Creates a literal of the variable var with sign s.
        /*!
         * \param var The literal's variable.
         * \param s true if new literal should be negative.
         * \pre var < varMax
         */
        Literal(ATTID atterm, TID term, bool sign)  {
            throw "NOT IMPLEMENTED YET";
        }

        //! Returns the variable of the literal.
        ATTID atterm() const {
            throw "NOT IMPLEMENTED YET";
        }

        TID term() const {
            throw "NOT IMPLEMENETED YET";
        }

        //! Returns the sign of the literal.
        /*!
         * \return true if the literal is negative. Otherwise false.
         */
        bool sign() const {
            throw "NOT IMPLEMENETED YET";
        }

        //! Returns var and sign encoded in a unique id.
        /*!
         * \note The watch-flag is ignored and thus the id of a literal can be stored in 31-bits.
         */
        uint32 id() const { throw "NOT IMPLEMENETED YET"; }

        uint32 var() const { throw "NOT IMPLEMENETED YET"; }

        //! Returns the stored representation of this literal.
        uint64 &rep() { return rep_; }

        uint64 rep() const { return rep_; }

        //! Creates a literal from an id.
        static Literal fromId(uint64 id) {
            throw "NOT IMPLEMENETED YET";
        }

        //! Creates a literal from an unsigned integer.
        static Literal fromRep(uint64 rep) { return Literal(rep); }

        void swap(Literal &other) { std::swap(rep_, other.rep_); }

        //! Sets the watched-flag of this literal.
        Literal &flag() {
            throw "NOT IMPLEMENETED YET";
        }

        //! Clears the watched-flag of this literal.
        Literal &unflag() {
            throw "NOT IMPLEMENETED YET";
        }

        //! Returns true if the watched-flag of this literal is set.
        bool flagged() const { throw "NOT IMPLEMENETED YET"; }

        //! Returns the complimentary literal of this literal.
        /*!
         *  The complementary Literal of a Literal is a Literal referring to the
         *  same variable but with inverted sign.
         */
        inline Literal operator~() const {
            throw "NOT IMPLEMENETED YET";
        }

    private:
        Literal(uint32 rep) : rep_(rep) {}

        uint64 rep_;
    };
}
#endif //PLOG_LITERAL_H
