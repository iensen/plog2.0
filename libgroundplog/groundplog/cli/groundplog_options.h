// 
// Copyright (c) 2006-2013, Benjamin Kaufmann
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
#ifndef GROUNDPLOG_CLI_GROUNDPLOG_OPTIONS_H_INCLUDED
#define GROUNDPLOG_CLI_GROUNDPLOG_OPTIONS_H_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#include <groundplog/groundplog_facade.h>
#include <string>
#include <iosfwd>
namespace ProgramOptions {
class OptionContext;
class OptionGroup;
class ParsedOptions;
}
namespace GroundPlog {
//! Namespace for types and functions used by the command-line interface.
namespace Cli {

/**
 * \defgroup cli Types to be used by the command-line interface.
 */
//@{
class GroundPlogCliConfig;
class ConfigIter {
public:
	const char* name() const;
	const char* base() const;
	const char* args() const;
	bool        valid()const;
	bool        next();
private:
	friend class ClaspCliConfig;
	ConfigIter(const char* x);
	const char* base_;
};
//! Valid configuration keys.
enum ConfigKey {
#define CONFIG(id,k,c,s,p) config_##k,
#define CLASP_CLI_DEFAULT_CONFIGS config_default = 0,
#define CLASP_CLI_AUX_CONFIGS     config_default_max_value,
#include <groundplog/cli/groundplog_cli_configs.inl>
	config_aux_max_value,
	config_many, // default portfolio
	config_max_value,
	config_asp_default   = config_tweety,
	config_sat_default   = config_trendy,
	config_tester_default= config_tester,
};
/*!
 * Configuration object for storing/processing command-line options.
 *
 * Caveats (when using incrementally, e.g. from clingo):
 * - supp-models: State Transition (yes<->no) not supported.
 *     - supp-models=yes is irreversible for a step
 *       because it enables possibly destructive simplifications
 *       and skips SCC-checking (i.e. new SCCs are silently discarded).
 *     - Nogoods learnt during supp-models=no are not tagged and
 *       hence can't simply be removed on transition to yes.
 *     .
 * - stats: Stats level can only be increased.
 *     - A stats level once activated stays activated even if 
 *       level is subsequently decreased via option.
 *     .
 * - save-progress, sign-fix, opt-heuristic: No unset of previously set values.
 *     - Once set, signs are only unset if forgetOnStep includes sign.
 *     . 
 * - no-lookback: State Transition (yes<->no) not supported.
 *     - noLookback=yes is a destructive meta-option that disables lookback-options by changing their value
 *     - noLookback=no does not re-enable those options. 
 *     .
 */
class GroundPlogCliConfig:GroundPlogConfig{
public:
	uint32             numSolver()const {return 0;};
    void validate(const char* ctx, const SolverParams& solver) {}

};


}

}

#endif
