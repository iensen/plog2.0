#pragma once
#include <set>
#include <string>
#include "Query.h"

class AnswerSet
{
public:
	AnswerSet(void);
	AnswerSet(std::string line);

	//Return the atoms
	std::set<std::string>& GetAtoms();

	//Return the probability associated with this answer set
	double GetProbability();

	//Assign the probability
	void SetProbability(double p){prob=p;};

	
    void AddBasicFormula(Query *qry);
    void CollectFormula(Query *qry);
    void EvaluateQuery(Query *qry);
    bool EvaluateFormula(Formula *f);
	~AnswerSet(void);

private:
	
	double AssignProbability(std::string in);
	
	
	std::set<std::string> atoms;
	
	double prob;

};
