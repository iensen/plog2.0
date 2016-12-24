#pragma once
#include "Sort.h"
#include "Attribute.h"
#include "Variable.h"
#include "Rule.h"
//#include "Formula.h"

#include <set>
#include <list>
#include <string>

//class Formula;

class Program
{
public:
	Program(void);
	~Program(void);

	void AddRule(Rule* r);
	void AddSort(Sort* s);
	void AddAttribute(Attribute* a);
	void AddVariable(Variable *v);
	//void AddDoStatement(Atom *a);
	//void AddObsStatement(Atom *l);
	//void AddFormula(Formula *f);

	std::string GetAttributeRange(std::string att);

	Sort* GetSort(std::string name);

	void Show();

public:
	std::list<Rule*> rule;
	std::set<Sort*>  sort;
	std::set<Attribute*> attr;
	std::set<Variable*> variable;
	//std::list<Atom*> dos;  //do statement
	//std::list<Atom*> obs; //obs statement
};
