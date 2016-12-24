#pragma once

#include "Program.h"
#include "Query.h"
#include <string>

class TrEngine
{
public:
	TrEngine(void);
	TrEngine(Program *p, Query *q, std::string inf);
	~TrEngine(void);
	
	//Return false in case there are errors in the program.
	//Erro can be one of the following cases:
	//Contain cr rules while using non crmodels inference engine.
	bool Solve();
	bool Translate();
	std::string GetOutput();


private:
	Program *prg;
	Query *qry;
	std::string solver;
	std::string output; //The output string
	std::set<std::string> atoms;
	//Rename a term by replace last character of "plus", "minus", "times" and "div"
	//to '_' in order to avoid inference engine (lparse or gringo) to evaluate them
	std::string ReNameTerm(std::string exp);
	std::string GetPart(std::string in, int i);
};
