#pragma once

#include "Formula.h"
#include "Literal.h"
//#include "TermTree.h"
//#include "AnswerSet.h"

#include <list>
#include <set>

//class Grounder;
class Formula;

class Query
{
public:
	Query(void);
	~Query(void);
	//Conditions
	std::list<Literal*> condition;
	std::list<Formula*> formula; //Regular formulas for type 1
	std::list<Formula*> answers;
	std::list<Literal*> atoms;  //for type 3
	std::list<std::string> terms; //for type 2
	//std::set< std::set<std::string> > aset;
	//std::set<Atom*> aFormula;
	int type; 

public:
	//Collect atoms occured in formula
	void CollectFormulaAtom(std::set<std::string>& atomSet);

	//Evaluate formulas w.r.t. an answer set a
	//void EvaluateFormula(AnswerSet *a);

	//Collect atoms for type 3 
	void CollectAtoms(Literal* a);

	//Define a basic formula from type 2
	//void CollectFormula(AnswerSet *a);

	//Add conditions to the query
	void AddCondition(Literal *l);

	//Add Formulas in the query,type 1
	void AddFormula(Formula *f);

	//The type of the query
	void SetType(int i);

	//Return the type of the query
	int GetType();

	//Add formula according to answer set, type 3
	//void AddBasicFormula(AnswerSet *a);

    bool IsSuper(Formula *f);

	bool GetMaximunFormula(); //Return true if there exists one formula, its probability > 0
	void ShowAnswer();
	void Show();

};
