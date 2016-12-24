#pragma once
#include "GroundLiteral.h"
#include "RandomRule.h"
#include <vector>

class GroundLiteral;
class RandomRule;

class GroundTerm
{
public:
	GroundTerm(void);

	GroundTerm(std::string s);

	~GroundTerm(void);

    //Return the name of the term
    std::string GetName() const {return name;};

    //set the processed 
	void SetProcessed(bool flag){processed=flag;};

	//get the value of processed
	bool GetProcessed() const {return processed;};

    //Add a literal
	void AddLiteral(GroundLiteral* gl);
	
	//get the specific ground literal
	GroundLiteral* GetLiteral(size_t idx);

    //get the number of literals linked to the term
	size_t GetSize();


	//Return the 'ground version' termtree
	//TermTree* GetTermTree();

	//Compute the dependency set of this term
	void CollectTerm(std::set<GroundTerm*>& stk, std::set<GroundTerm*>& checked);

	//Add the a random rule to
	void AddRandomRule(RandomRule* nr);

    //add dependant random rules to the set
    void CollectRandomRule(std::set<std::string>& rndRuleName);

private:
	//TermTree* term;
    std::string name;
	std::vector<GroundLiteral*> gndLiteral;
	std::vector<RandomRule*> rndRule;
	bool processed;

};
