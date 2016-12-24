#pragma once

#include "GroundRule.h"
#include "GroundLiteral.h"
#include "GroundTerm.h"
#include <vector>
#include <string>
#include <set>

class GroundRule;
class GroundLiteral;
class GroundTerm;

class RandomRule
{
public:
	RandomRule(void);

	RandomRule(std::string name);

	~RandomRule(void);
	
	//Add the ground rule random rule class
	void AddPrRules(GroundRule *r);

	//Add the range
	void AddRange(GroundLiteral *gl);
	
	//Add the head
	void AddHead(GroundLiteral *gl);

	//Add the random rule
	void AddRandomRule(GroundRule* r);

	//Collect the dependency set of random rules
	void CollectTerm(std::set<GroundTerm*>& stk, std::set<GroundTerm*>& checked);

	//Get the number of head in the vector head
	size_t GetHeadSize();

	//Get the head literal
	GroundLiteral* GetHeadLiteral(size_t idx);

	GroundLiteral* GetRangeLiteral(size_t idx); 

	//Get the range vector
	std::vector<GroundLiteral*>& GetRange();

	//Get the pr rules
	std::vector<GroundRule*>& GetPrRule();

	inline GroundRule* GetRandomRule() const {return rndRule;};

	//Set the valid info for rules in rndRule
	void SetValid();
	
	//Show and print out the object
	void Show();

    //return the name of the rule
    std::string GetRuleName() const {return ruleName;};

private:
	std::string ruleName;
	GroundRule* rndRule;
	std::vector<GroundLiteral*> head;
	std::vector<GroundLiteral*> range;
	std::vector<GroundRule*> prRule;
};
