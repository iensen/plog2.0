#pragma once

#include <vector>
#include <string>
#include "Literal.h"
//#include "Constraint.h"

enum ruleType {reg, rnd_, pr,cr}; //
enum bodyLiteral {_pos, _neg, _con};

class Rule
{
public:
	Rule(void);
	~Rule(void);

	Rule(std::string s, ruleType rt);
	Rule(ruleType rt);
	Rule(Rule* r);

public:
	//Add an atom as the the head of the rule
	void AddHead(Literal* l){head=l;};

    //Get the head of the rule, return NULL, if it is a constraint rule
	Literal* GetHead() const {return head;};

    //Get the name of the rule
	std::string GetRuleName() const {return name;};

    //Add the range atom to it
	void AddRange(Literal *a){range=a;};

    //Get the range may used in the random selection rule, return NULL if no range specified.
	Literal* GetRange() const {return range;};

    //Set the probability term for pr rules
	void SetPrProbability(std::string e){exp=e;};

    //Get the probability may used in pr rules, return NULL if no probability specified.
	std::string GetProbability() const {return exp;};

    //Return the rule type
	ruleType GetType() const {return rType;};

    //Add the variable
	void AddVar(std::string s){var=s;};

	//Return the sort
	std::string GetRndVar() const {return var;};

    //return the size of the body
	size_t GetBodySize(){return body.size();};
    
    //Add a literal to the body of the rule
	void AddBody(Literal *l){body.push_back(l);};

    //IMPLEMENTED IN CPP

	//return the literal in the body
	Literal* GetLiteral(size_t idx);
	
	//Get the string representation of the name of the rule
	//std::string GetName();

	//String representation of body of rule, recognizable by lparse and crmodels
	std::string BodyToString();

    //Collect Vairiables (variables occured in the body but not in the head)
	//This must be called after preprocessing.
	void CollectVariable();

    //Return the set of free variables
	std::set<std::string> GetVariable();

    //Return the set of list Variable
    std::set<std::string>& GetListVar() {return listVariable;};

	//Replace the arithmetic expressions of 
	//the head by a constraint in the body
	void Normalize();

    //Get the grounded
	bool IsGround();

    void CheckFact(std::set<std::string>& facts);

    //For debugging only
	void Show();

    //NOT SURE NEED THOSE INTERFACE OR NOT
    /*
	//The total number of literals in body, including postive, negtive and constraints
	size_t GetTotalSize();

	//Get the size of positive literals
	size_t GetPosSize();

	//Get the size of negtive literals
	size_t GetNegSize();

	//Get the size of constraint
	size_t GetConSize();

	//Return the pointer to the literal in the body
	Literal* GetLiteral(size_t idx, bodyLiteral bl);

	
	
    */

	
	
	

private:
	Literal *head;
	std::string name;
	Literal *range;
    std::string var; //For random selecton rule onely
	ruleType rType;
	std::string exp;
	std::vector<Literal*> body;
	

	//All the variables appeared in the body but not in the head
	std::set<std::string> freeVariable;

    //All the variables that has no restriction
    std::set<std::string>  listVariable;
	
	//the number of positive literals
	//size_t posSize;

	//the number of negtive literals
	//size_t negSize;
	
	//the number of constraints
	//size_t conSize;

	//whether a rule contains any variable
	//bool grounded;
};
