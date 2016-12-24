#pragma once 

#include <list>
#include <map>
#include <fstream>
#include "TermTree.h"
#include "Program.h"
#include "Query.h"

//Define the size of Parse Table, and To Go Table
#define dfptbl 855
#define dfsym  66
#define dfgra  70
	
class CParse
{
public:
	CParse(Program* p, Query *q);
	virtual ~CParse();

private:
	std::map<std::string, int> symbolTable;
	int symbolId; //The current token
	char* memblock;
	int readPos;
	int memSize;
	int igr[dfgra][2];
	int shift[dfptbl][dfsym];
	int reduce[dfptbl][dfsym];
	Program *prg;
	Query *qry;

	//Private Member Functions
	std::string GetNextToken();
	bool ShiftAction(int istate, std::string tname);
	bool ReduceAction(int rid);
	bool ReadFile(std::string fileName);
	void ErrorReport();


public:
	int SyntaxAnalysis(std::string fileName);


	//std::list<Symbols> symbol;
	//std::ifstream infile;
	std::list<std::string> lstSymbol;
	std::list<std::string> lstIDL;
	

	std::list<std::string> lstSym;
	std::list<Literal*> lstAtom;
	std::list<Literal*> lstLit;
	std::list< std::list<TermTree*> > lstTL;

	std::list<TermTree*> lstEXP;
	std::list<TermTree*> lstTTD;
	std::list<TermTree*> lstFCT;
	std::list<TermTree*> lstTerm;
	std::list<Literal*> lstBody;
	//std::list<Atom*> lstPos;
	//std::list<Atom*> lstNeg;
	//std::list<Atom*> lstCmp;
	//std::list<Atom*> lstDo;
	//std::list<Atom*> lstObs;
	std::list<Formula*> lstFML;
	std::list<Formula*> lstFMC;

	Rule *rndRule;
	Rule *prRule;
}; 

