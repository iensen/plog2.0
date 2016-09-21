// 
// Copyright (c) 2013-2016, Benjamin Kaufmann
// 
// This file is part of Clasp. See http://www.cs.uni-potsdam.de/clasp/ 
// 
// Clasp is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// Clasp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Clasp; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
/*!
 * \file 
 * Supermacros for describing clasp's options.
 * An option consists of:
 *  - a key  (valid and unique c identifier in 'snake_case')
 *  - a key extension ("[!][,<alias>][,@<level>]") as understood by ProgramOptions::OptionInitHelper
 *  - an arg description (ARG macro) as understood by ProgramOptions::Value
 *  - a description (string)
 *  - a set action to be executed when a value (string) for the option is found in a source
 *  - a get action to be executed when the current value for an option is requested
 *  . 
 * OPTION(key, "ext", ARG(...), "help", set, get).
 * 
 * \note In the implementation of ClaspCliConfig, each key is mapped to an enumeration constant and 
 * the stringified version of key (i.e. #key) is used to identify options. 
 * Furthermore, the key is also used for generating command-line option names.
 * As a convention, compound keys using 'snake_case' to separate words 
 * are mapped to dash-separated command-line option names. 
 * E.g. an <option_like_this> is mapped to the command-line option "option-like-this".
 *
 * \note ClaspCliConfig assumes a certain option order. In particular, context options shall
 * precede all solver/search options, which in turn shall precede global asp/solving options.
 *
 * \note The following set actions may be used:
 *  - STORE(obj): converts the string value to the type of obj and stores the result in obj.
 *  - STORE_LEQ(n, max): converts the string value to an unsinged int and stores the result in n if it is <= max.
 *  - STORE_FLAG(n): converts the string value to a bool and stores the result in n as either 0 or 1.
 *  - STORE_OR_FILL(n): converts the string value to an unsinged int t and sets n to std::min(t, maxValue(n)).
 *  - FUN(arg): anonymous function of type bool (ArgStream& arg), where arg provides the following interface:
 *    - arg.ok()     : returns whether arg is still valid
 *    - arg.empty()  : returns whether arg is empty (i.e. all tokens were extracted)
 *    - arg.off()    : returns whether arg contains a single token representing a valid off value
 *    - arg >> x     : extracts and converts the current token and stores it in x. Sets failbit if conversion fails.
 *    - arg >> opt(x): extracts an optional argument, shorthand for (!arg.empty() ? arg>>obj : arg)
 *    .
 *
 * \note The following get actions may be used:
 *  - GET_FUN(str)  : anonymous function of type void (OutputStream& str)
 *  - GET(obj...)   : shorthand for GET_FUN(str) { (str << obj)...; }
 *  - GET_IF(C, obj): shorthand for GET_FUN(str) { ITE(C, str << obj, str << off); }
 *  .
 *
 * \note The following primitives may be used in the set/get arguments:
 *  - off                  : singleton object representing a valid off value ("no", "off", "false", "0")
 *  - ITE(C, x, y)         : if-then-else expression, i.e. behaves like (C ? x : y).
 *  - SET(x, y)            : shorthand for (x=y) == y.
 *  - SET_LEQ(x, v, m)     : shorthand for (x <= m && SET(x, v)).
 *  - SET_GEQ(x, v, m)     : shorthand for (x >= m && SET(x, v)).
 *  - SET_OR_FILL(x, v)    : behaves like SET(x, min(v, maxValue(x)))
 *  - SET_OR_ZERO(x,v)     : behaves like ITE(v <= maxValue(x), SET(x, v), SET(x, 0)).
 *  .
 */
#if !defined(OPTION) || defined(SELF)
#error Invalid include context
#endif

#if !defined(GROUP_BEGIN)
#define GROUP_BEGIN(X)
#endif

#if !defined(GROUP_END)
#define GROUP_END(X)
#endif

//! Options for configuring a SharedContext object stored in a GroundPlog::ContextParams object.
#if defined(GROUNDPLOG_CONTEXT_OPTIONS)
#define SELF GROUNDPLOG_CONTEXT_OPTIONS
GROUP_BEGIN(SELF)
// define options here
GROUP_END(SELF)
#undef GROUNDPLOG_CONTEXT_OPTIONS
#undef SELF
#endif

//! Global options only valid in facade.
#if defined(GROUNDPLOG_GLOBAL_OPTIONS)
#define SELF GROUNDPLOG_GLOBAL_OPTIONS
GROUP_BEGIN(SELF)
//  define options here
GROUP_END(SELF)
#undef GROUNDPLOG_GLOBAL_OPTIONS
#undef SELF
#endif

//! Solver options (see SolverParams).
#if defined(GROUNDPLOG_SOLVER_OPTIONS)
#define SELF GROUNDPLOG_SOLVER_OPTIONS
GROUP_BEGIN(SELF)
// define options here
GROUP_END(SELF)
#undef GROUNDPLOG_SOLVER_OPTIONS
#undef SELF
#endif

//! Search-related options (see SolveParams).
#if defined(GROUNDPLOG_SEARCH_OPTIONS)
#define SELF GROUNDPLOG_SEARCH_OPTIONS
GROUP_BEGIN(SELF)
// define options here
#undef SELF

//! Options for configuring the restart strategy of a solver.
#define SELF GROUNDPLOG_SEARCH_RESTART_OPTIONS
#if defined(NOTIFY_SUBGROUPS)
GROUP_BEGIN(SELF)
#endif
// define options here
#if defined(NOTIFY_SUBGROUPS)
GROUP_END(SELF)
#endif
#undef SELF
#undef GROUNDPLOG_SEARCH_RESTART_OPTIONS
//! Options for configuring the deletion strategy of a solver.
#define SELF GROUNDPLOG_SEARCH_REDUCE_OPTIONS
#if defined(NOTIFY_SUBGROUPS)
GROUP_BEGIN(SELF)
#endif
// define options here
#if defined(NOTIFY_SUBGROUPS)
GROUP_END(SELF)
#endif
#undef SELF
#undef GROUNDPLOG_SEARCH_REDUCE_OPTIONS
GROUP_END(GROUNDPLOG_SEARCH_OPTIONS)
#undef GROUNDPLOG_SEARCH_OPTIONS
#endif

//! ASP-front-end options stored in an GroundPLog::Asp::LogicProgram::AspOptions object.
#if defined(GROUNDPLOG_ASP_OPTIONS)
#define SELF GROUNDPLOG_ASP_OPTIONS
GROUP_BEGIN(SELF)
// define options here
#undef GROUNDPLOG_ASP_OPTIONS
#undef SELF
#endif

//! Options for the solving algorithm (see GroundPlog::SolveOptions)
#if defined(GROUNDPLOG_SOLVE_OPTIONS)
#define SELF GROUNDPLOG_SOLVE_OPTIONS
GROUP_BEGIN(SELF)
// define some options

#if defined(WITH_THREADS) && WITH_THREADS == 1
// define parallel options
#endif
// define other options
GROUP_END(SELF)
#undef GROUNDPLOG_SOLVE_OPTIONS
#undef SELF
#endif

#undef GROUP_BEGIN
#undef GROUP_END
#undef OPTION
#undef NOTIFY_SUBGROUPS
#undef ARG
#undef ARG_EXT
#undef NO_ARG
