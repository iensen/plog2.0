#pragma once
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <map>
#include "GroundProgram.h"
//#include "GroundAtom.h"
#include "Program.h"
#include "Query.h"
//#include "GroundTerm.h"


//class Program;
//class Query;

class Grounder
{
public:
	Grounder(void);

	Grounder(GroundProgram *gp, Program *p, Query *q);

	~Grounder(void);


public: 
	//Replace arithmetic expression and collect free variables
	bool Preprocessing(); 

    //The main function
	void Ground(std::string s);

    void SetDebugLevel(int iLevel){debug_level=iLevel;};

    void DependantSet(GroundTerm *t, std::set<GroundTerm*>& dependantSet);


	//bool Ground(std::string lit); 
	//bool IsMatch(TermTree *term_1, TermTree *term_2);
	

private:
    int debug_level;
	//A Ground Program, the output of grounding process
    GroundProgram *gndProgram;

    //A Non-Ground Program, the input of groudning process	
    Program *prg;

    Query *qry;
	
	//Assignment is a map from variable to its value
	std::map<std::string,std::string> assignment;

    //A map from string to Variable type
	std::map<std::string, Variable*> variables;

    //Atoms that always true
	std::set<std::string> positiveAtom;

	//Atoms that always false
	std::set<std::string> negtiveAtom;

    std::set<std::string> facts;



//Private member functions
private:

    //Link Variable in variables to its corressponding sort
	void VariableToSort();

    void GroundQuery();

    void GroundSort();

    std::list<Literal*> Ground(Literal *l);



    //Solution table:
	//First V1 V2 V3
	//      1  2  3

    //bool NextAssignment(std::vector< std::vector<std::string> > sol, std::list<Variable*> varlst);

	
	//Returnt the join of two tables
	std::vector<std::vector<std::string> > Join(std::vector<std::vector<std::string> >& sol_1,
		std::vector<std::vector<std::string> >& sol_2);

    //
	bool AppendSolution(std::vector<std::string>& newSol, std::vector<std::string> sol_1,
		std::vector<std::string> sol_2, std::list< std::pair<int, int> >& joinVariable);

    //Get a domain of a variable in solution format
	std::vector<std::vector<std::string> > GetVarSolution(std::string varName);

    

	/*std::list<GroundRule*> groundRules; */
	//std::map<std::string, int> varOrdering;
	//std::set<std::string> factAtom;

	//
	//Get all the ground instances of r
	bool GetGroundRule(Rule *r);
	
    //Evaluate a literal
    bool Evaluate(Literal* l);

    //Check the value of literal is known or not 
    bool CheckValue(Literal* l);

    bool GetSolution(Literal* l, std::vector<std::vector<std::string> >& sol);
	
	
	//Evaluet the the program, compute the consequences
	void Evaluate(GroundTerm *gndTerm);

	//Get the next ground term that is ready to be examed
	GroundTerm* ResetTerms(GroundTerm *t);

	void GetARule(Rule* r, std::list<GroundLiteral*> lstPosGroundLit,
		std::list<GroundLiteral*> lstNegGroundLit, GroundLiteral* gHead, 
			std::list<Literal*> lstLiteral);

    //Get All the positive literals
	inline std::set<std::string>& GetPostiveAtom() {return positiveAtom;};

    //Get All negtive literals	
    inline std::set<std::string>& GetNegtiveAtom() {return negtiveAtom;};

	
	bool CheckTerm(const std::string a, const std::string b);

	
	
	//Check whether a literal is a fact
	bool CheckFact(Literal *l);

	bool Match(std::string s1, std::string s2);
	
	bool NextAssignment(std::vector<std::vector<std::string> >& sol, int i);

    bool NextAssignment(std::list<Variable*>& varlist);

    void ResetVariable(std::list<Variable*>& varlst);

    void AddSolution(std::list<Variable*>& varlist, std::vector<std::vector<std::string> >& sol);

 	/*
	//Return a list of ground term of input term tm
	std::list<TermTree*> GroundingTerm(TermTree* tm);

	std::list<Atom*> GroundingAtom(Atom* atm);
    
    
	
    */
	
};
