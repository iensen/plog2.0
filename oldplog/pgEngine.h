#pragma once

#include "Program.h"
#include "GroundProgram.h"
#include "Query.h"
#include "State.h"
#include "Grounder.h"

#include <stack>
#include <list>

class pgEngine
{
public:
    pgEngine(void);
    pgEngine(Program* p, Query* q);
    ~pgEngine(void);

    void Run();

    bool FireRandomRule(State* s, std::map<int,double>& po);

    State* GetNewState(State* s);

    void RemoveState(State *s);

    //Answer query type one
    void Query_1();
	
    //Answer query type two
    void Query_2();

    //Answer query type three
    void Query_3();

    //Set the id of literals in the formula, for easy truth value checking
    void SetFormulaId(Formula *f);

    void AddState(State* s, std::list<State*>& lstState);

    void SetDebugLevel(int iLevel){debug_level=iLevel;};

    void BuildRandomDependant(std::set<Literal*>& litSet);

private:
    int debug_level;
    Grounder* grounder;
    Program* prg;
    GroundProgram* gnd;
    Query* qry;
	std::list<State*> statePool;
	std::list<State*> states;
	std::list<State*> ans;

    std::set<std::string> rndDependant;

    bool stage;

};
