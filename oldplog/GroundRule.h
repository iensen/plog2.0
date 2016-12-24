#pragma once

#include "Rule.h"
#include "GroundLiteral.h"
#include <vector>
#include <string>
//#include "TermTree.h"
#include <map>

class GroundLiteral;

class GroundRule
{
public:
	GroundRule(void);
	GroundRule(Rule *r);
	~GroundRule(void);

	void AddLiteral(GroundLiteral *gl, bool sign);
	void AddName(std::string s);
	void AddHead(GroundLiteral *gl);
	void AddRange(GroundLiteral *gl);
	
	void SetLink();
	void Show();

	GroundLiteral* GetHead();
	size_t GetBodySize(bool flag);
	GroundLiteral* GetBodyLit(size_t idx, bool flag);
	
	//bool GetSign(); //???
	void RemoveLiteral(bool flag, GroundLiteral* gl, 
		std::stack<GroundLiteral*>& pos, std::stack<GroundLiteral*>& neg);

    //Return the whole body of the ground rule
	std::vector<GroundLiteral*>& ReturnBody(bool flag);

    //Return the rule type
    ruleType GetType() const {return type;};	

    //Set and Get the variable dependent
    void SetDependent(bool flag){dependent=flag;};
	
	bool GetDependent() const {return dependent;};

    //Set and Get the variable dependent    
    void SetValid(bool flag){valid=flag;};

    bool GetValid() const {return valid;};

   	//Set the rule id for the ground rule
	void SetId(size_t i){id=i;};

	//Return the rule id
	size_t GetId() const {return id;};
    
    //Add the probability
    void AddProbability(double p){probability=p;};

	//Return the probability of rule
	inline double GetProbability() const {return probability;};

	void SetSpt(bool t){spt=t;};
	
	bool GetSpt() const {return spt;}; 

private:
	std::vector<GroundLiteral*> posBody;
	std::vector<GroundLiteral*> negBody;
	GroundLiteral *head;
	GroundLiteral *range; //??
	std::string ruleName;
	double probability;
	ruleType type;
	bool dependent;
	bool valid;
	//bool sign;
	bool spt;
	size_t id;
};
