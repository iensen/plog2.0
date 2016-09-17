//
// Created by iensen on 9/3/16.
//

#ifndef PLOG_PLOGPARSER_H
#define PLOG_PLOGPARSER_H
// {{{ GPL License

// This file is part of gringo - a grounder for logic programs.
// Copyright (C) 2013  Roland Kaminski

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// }}}

#include "programbuilder.h"
#include <gringo/lexerstate.hh>
#include <memory>
#include <iosfwd>
#include <set>
#include<gringo/lexerstate.hh>
#include<gringo/logger.hh>
#include <plog/programbuilder.h>
using Logger = Gringo::Logger;
using Location = Gringo::Location;

template<class T>
using LexerState = Gringo::LexerState<T>;

// {{{ declaration of NonGroundParser

        using StringVec   = std::vector<std::string>;
        using ProgramVec  = std::vector<std::tuple<std::string, IdVec, std::string>>;

        class PlogParser : private LexerState<std::pair<std::string, std::pair<std::string, IdVec>>> {
        private:
            enum Condition { yyccomment, yycnormal, yycdefinition };
        public:
            PlogParser(NonGroundProgramBuilder &pb);
            void parseError(Location const &loc, std::string const &token);
            void pushFile(std::string &&filename, Logger &log);
            void pushStream(std::string &&name, std::unique_ptr<std::istream>, Logger &log);
            void pushBlock(std::string const &name, IdVec const &vec, std::string const &block, Logger &log);
            int lex(void *pValue, Location &loc);
            bool parseDefine(std::string const &define, Logger &log);
            bool parse(Logger &log);
            bool empty();
            void include(std::string file, Location const &loc, bool include, Logger &log);
            NonGroundProgramBuilder &builder();
            // Note: only to be used during parsing
            Logger &logger() { assert(log_); return *log_; };
            ~PlogParser();

        private:
            int lex_impl(void *pValue, Location &loc);
            void lexerError(std::string token);
            bool push(std::string const &filename, bool include = false);
            bool push(std::string const &file, std::unique_ptr<std::istream> in);
            void pop();
            void _init();
            void condition(Condition cond);
            using LexerState<std::pair<std::string, std::pair<std::string, IdVec>>>::start;
            void start(Location &loc);
            Condition condition() const;
            std::string filename() const;

        private:
            std::set<std::string> filenames_;
             std::string not_;
            NonGroundProgramBuilder &pb_;
            int           _startSymbol;
            Condition     condition_ = yycnormal;
            std::string        _filename;
            Logger *log_ = nullptr;
        };

// }}}





#endif //PLOG_PLOGPARSER_H

