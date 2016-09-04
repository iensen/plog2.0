//
// Created by iensen on 8/18/16.
//

#ifndef PLOG_RULE_UTILS_H
#define PLOG_RULE_UTILS_H
//
// Copyright (c) 2016, Benjamin Kaufmann
//
// This file is part of Potassco. See http://potassco.sourceforge.net/
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef LIBLP_RULE_UTILS_H_INCLUDED
#define LIBLP_RULE_UTILS_H_INCLUDED
#include<groundplog/program_types.h>
#include<vector>

namespace GroundPlog {

//! A type that can represent an aspif rule.
    struct Rule_t {
        Head_t   ht;
        Atom_t head;
        std::vector<Lit_t> body;
        Rule_t(Head_t ht, Atom_t head, const std::vector<Lit_t>& body);
    };

//! A builder class for creating a rule.
    class RuleBuilder {
    public:
        RuleBuilder();
        /*!
         * \name Start functions
         * Functions for starting the definition of a rule's head or body.
         * If the active rule is frozen (i.e. end() was called), the active
         * rule is discarded.
         * \note The body of a rule can be defined before or after its head is defined
         * but definitions of head and body must not be mixed.
         */
        //@{
        //! Start definition of the rule's head, which can be either disjunctive or a choice.
        RuleBuilder& start();
        //! Start definition of a conjunction to be used as the rule's body.
        RuleBuilder& startBody();
        //@}

        /*!
         * \name Update functions
         * Functions for adding elements to the active rule.
         * \note Update function shall not be called once a rule is frozen.
         * \note Calling an update function implicitly starts the definition of the
         * corresponding rule part.
         */
        //@{
        //! Add a to the rule's head.
        RuleBuilder& addHead(Atom_t a);
        //! Add lit to the rule's body.
        RuleBuilder& addGoal(Lit_t lit);

        //! Stop definition of rule and add rule to out if given.
        /*!
         * Once end() was called, the active rule is considered frozen.
       */
        RuleBuilder& end();
        //! Discard active rule.
        RuleBuilder& clear();
        //! Discard body of active rule but keep head if any.
        RuleBuilder& clearBody();

        /*!
         * \name Query functions
         * Functions for accessing parts of the active rule.
         * \note The result of these functions is only valid until the next call to
         * an update function.
         */
        //@{
        Atom_t      head()     const;
        uint32_t     bodySize() const;
        std::vector<Lit_t>       body()     const;
        Rule_t       rule()     const;
        //@}
    private:
        void endHead();
        void endBody();
    };

}
#endif

#endif //PLOG_RULE_UTILS_H
