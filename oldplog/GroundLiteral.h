#pragma once

#include <string>
#include <stack>
#include <vector>
#include "GroundTerm.h"
#include "GroundRule.h"

class GroundTerm;
class GroundRule;

class GroundLiteral
{
public:
	GroundLiteral(void);
	//GroundLiteral(A* l);
	//GroundLiteral(TermTree* tm);
	//GroundLiteral(Atom* a);
	GroundLiteral(std::string s, std::string v, bool sn);
	~GroundLiteral(void);

    //std::string GetNameTerm() const {return name;};

	//Get the name of the ground literal
	std::string GetName();

	//Add a rule where this literal is the positive part of the rule
	void AddPosRule(GroundRule *gr);

	//Add a rule to negRule indicate that this atom occures at the negative part
	//of the rule
	void AddNegRule(GroundRule *gr);

	//Add a rule to headRule indicate that is atom occures at the head of the rule
	void AddHeadRule(GroundRule *gr);

	//Set the link between the literal and the ground term
	void SetTerm(GroundTerm *t);

	//Get a ground rule whose body is empty?
	GroundRule* GetEmptyRule();

	//Remove 
	void Reduction(bool flag, std::stack<GroundLiteral*>& pos, std::stack<GroundLiteral*>& neg);

	//Return the ground term linked to the literal
	GroundTerm* GetTerm();

	//To check whether this literal has support
	void CheckHead(std::stack<GroundLiteral*>& pos, std::stack<GroundLiteral*>& neg);

	//Collect the dependancy of the ground literal
	void CollectTerm(std::set<GroundTerm*>& stk, std::set<GroundTerm*>& checked);

	//Set the id for the ground literal
	void SetId(size_t i);

	//Return the ground literal id
	size_t GetId();

	//Get The size of head Rule
	size_t GetHeadRuleSize();

	//Get a ground rule in the where this literal is
	//the head
	GroundRule* GetHeadRule(size_t idx);

	//Return the number of literals in the body
	size_t GetBodySize(bool flag);

	//Get a rule in where the literal is the body
	GroundRule* GetBodyRule(size_t idx, bool flag);

	//Count Positive literal
	int CountPositiveLiteral();

	//Get the sign of the literal
	bool GetSign() const;

	//Get the value of the literal
	std::string GetValue() const;
	
	//Get the neg supporting rule
	//int GetNegSprRuleSize();

	//Set this lit as random lit
	void SetRndLit(bool f){rndlit=f;};
	
	//Get this lit as random lit
	bool GetRndLit() const {return rndlit;}; 

	void IncreaseSupport(){support++;};
	
	size_t GetSupport() const {return support;};

	int GetTruthValue() const {return truthValue;};
	
	void SetTruthValue(int v){truthValue=v;};
    
    std::string GetTermName() const {return name;};

	//Set atom
	//void SetAtom(Atom* a){atom=a;};
	
	//Atom* GetAtom()const {return atom;};

private:
	size_t id;
	//Atom* atom;
	//Literal* lit;
	std::string name;
	bool sign;
	bool rndlit;
	size_t support;
	std::string value;
	GroundTerm* term;
	int truthValue;
	std::vector<GroundRule*> posRule;
	std::vector<GroundRule*> negRule;
	std::vector<GroundRule*> headRule;

};
