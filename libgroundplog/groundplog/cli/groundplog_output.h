// 
// Copyright (c) 2009-2013, Benjamin Kaufmann
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
#ifndef CLASP_CLI_OUTPUT_H_INCLUDED
#define CLASP_CLI_OUTPUT_H_INCLUDED
#include <groundplog/groundplog_facade.h>
#include <string>
namespace GroundPlog { namespace Cli {

/*!
 * \addtogroup cli
 */
//@{

/*!
 *
 * Interface for printing status and input format dependent information,
 * like models, optimization values, and summaries.
 */
class Output : public EventHandler {
public:
	virtual ~Output();

    Output();
	//! Shall be called once on startup.
	virtual void run(const char* solver, const char* version, const std::string* begInput, const std::string* endInput) = 0;
	//! Shall be called once on shutdown.
	virtual void shutdown(const GroundPlogFacade::Summary& summary);
	virtual void shutdown() = 0;
	//! Handles ClaspFacade events by forwarding calls to startStep() and stopStep().
	virtual void onEvent(const Event& ev);
	//! Checks quiet-levels and forwards to printLower() if appropriate.
	virtual bool onUnsat(const Solver& s);
	//! Called on unsat - may print new info.
	virtual void printUnsat();
	//! Print Probability.
	virtual void printProbability();
	//! A solving step has started.
	virtual void startStep(const GroundPlogFacade&);
	//! A solving step has stopped.
	virtual void stopStep(const GroundPlogFacade::Summary& summary);
protected:
private:
    typedef const GroundPlogFacade::Summary* SumPtr ;
    SumPtr    summary_ ; // summary of last step
    Output& operator=(const Output&);
};


//! Default clasp format printer.
/*!
 * Prints all output to stdout in given format:
 * - format_asp prints in clasp's default asp format
 * - format_aspcomp prints in in ASP competition format
 * - format_sat09 prints in SAT-competition format
 * - format_pb09 in PB-competition format
 * .
 * \see https://www.mat.unical.it/aspcomp2013/
 * \see http://www.satcompetition.org/2009/format-solvers2009.html
 * \see http://www.cril.univ-artois.fr/PB09/solver_req.html
 *
 */
class TextOutput : public Output {
public:
	TextOutput();
	~TextOutput();

	//! Prints a (comment) message containing the given solver and input.
	virtual void run(const char* solver, const char* version, const std::string* begInput, const std::string* endInput);
	virtual void shutdown();

	virtual void printUnsat();
	//! Called once a solving step has completed.
	/*!
	 * Always prints "format[cat_result] result[s.result()]".
	 * Furthermore, if verbosity() > 0, prints a summary consisting of
	 *   - the number of computed models m and whether the search space was exhausted
	 *   - the number of enumerated models e if e != m
	 *   - the state of any optimization and whether the last model was optimal
	 *   - the state of consequence computation and whether the last model corresponded to the consequences
	 *   - timing information
	 *   .
	 */
	virtual void onEvent(const Event& ev);
	//! A solving step has started.
	virtual void startStep(const GroundPlogFacade&);

    void comment(const char* fmt, ...) const;
protected:
private:
};
//@}

}}
#endif
