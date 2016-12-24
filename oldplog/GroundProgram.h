#pragma once

#include "GroundRule.h"
#include "GroundLiteral.h"
#include "GroundTerm.h"

class GroundProgram
{
public:
	GroundProgram(void);
	~GroundProgram(void);
	//add a ground rule to regRule or rndRule
	//proper links are created too
	void AddRule(GroundRule *gr);

	//Print to terminal all the rules in program,
	//mainly for debugging purpose.
	void Show();

	//Return a ground literal, if l is not present before
	//then create a new one, add it to the map gndLiteral
	//If the ground term does not exists, then a ground
	//term also created and added to gndTerm. 
	//Proper links between ground literals and ground terms
	//are created.
	GroundLiteral* GetLiteral(Literal *l);

	GroundTerm* GetTerm(std::string s);

	//map rulse and literals to vectors, for index based
	//access at inference stage
	void BuildVectors();

	//Get Random Rules
	RandomRule* GetRandomRule(std::string name);

	//Check rules body
	bool CheckPosBody(size_t idx);

    //"draw a line" between rules associated with conditions and formulas    
    void DrawLine();


	//Check random rule
	//bool CheckRndLit(GroundLiteral* gl);

	//Build upper bound stack
	void BuildUpperBound();

public:
	std::list<GroundRule*> regRule;
	std::map<std::string, RandomRule*> rndRule;
	std::map<std::string, GroundLiteral*> gndLiteral;
	std::map<std::string, GroundTerm*> gndTerm;

	//vectors representation of ruls and atoms
	//fast inference with the value of atoms
	std::vector<GroundRule*> gRule;
	std::vector<GroundLiteral*> gLit;
	std::set<int> upperBound;

    int hline; //
	
};
