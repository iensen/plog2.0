#ifndef STATE_H
#define STATE_H



#include "GroundProgram.h"
#include "Grounder.h"
#include "Formula.h"

#include <string>
#include <list>
#include <stack>
#include <vector>


const int TRUE=5;
const int MBT=4;
const int UNKNOWN=3;
const int MBF=2;
const int FALSE=1;

class State{
public:
	static long clkAtMost;
	static long cntClose;

public:
	State();

	//Copy Constructor
	State(State *s);

	//Constructor a state from a ground program
	State(GroundProgram* p, Grounder* grnd);

	virtual ~State();

public:
	double prob; //The probability of this

	//the number of literals
	int asize;

	//the number of ground rules
	int rsize;

	//std::set<std::string> pos;

    //std::set<std::string> neg;
	
	//std::set<int> upper;

	//The pointer to the program
	GroundProgram* prg;

	//The value of each literal
	int* aval;

	//The number of weakly supporting rule
	int* atom;
	
	//The number of regular supporing rule
	int* rspt;

	//The number of regular rule
	int* rule;

	//The number of negative supporting rule
	//int* aspt;
	
	//The set of fired random selection rule
   	std::set<std::string> firedRndRule;

	bool upped;

    int rank;

public:
    void SetDebugLevel(int i){debug_level=i;};

    int GetDebugLevel(void){return debug_level;};

	void SetUpped(bool f){upped=f;};
	
	bool GetUpped() const {return upped;};
	//void Update(State *s);
	bool Close(int aid, int value);
	//void lClose(int id, bool val,int aid, int rid);

	//Inference from Head to Body
	//void HeadToBody(GroundRule *r, bool val, std::stack< std::pair<int, int> >& stk);

	bool UpClosure();

	bool AtMost(std::stack< std::pair<int,int> >& stk);

	//Inference from Body to Head
	//void BodyToHead(GroundRule* r, std::stack< std::pair<int,int> >& stk);
    int Satisify(std::vector<GroundLiteral*>& gvec, bool flag) const;

	int KnowTerm(std::list<GroundTerm*>& gndTerm, Formula* f) const;

    //knwon the vector
    bool KnownLiteral(std::list<int>& glst, Formula *f);

    bool Known(std::vector<GroundLiteral*>& gvec);

    //Copy
	void Copy(State *s);

    int EvaluateFormula(Formula *f);


	//Output the state
	void Show(bool bAtom, bool bRule, bool bKnown);
    

private:
    int debug_level;
    //A Set of rules for inference
    bool UpdateRule_1(GroundLiteral* gl, std::stack< std::pair<int,int> >& stk_1, std::stack< std::pair<int,int> >& stk_2);
    bool UpdateRule_2(GroundLiteral* gl, std::stack< std::pair<int,int> >& stk_1, std::stack< std::pair<int,int> >& stk_2);
    bool UpdateRule_3(GroundLiteral* gl, std::stack< std::pair<int,int> >& stk_1, std::stack< std::pair<int,int> >& stk_2);
    bool UpdateRule_4(GroundLiteral* gl, std::stack< std::pair<int,int> >& stk_1, std::stack< std::pair<int,int> >& stk_2);
    bool UpdateRule_5(GroundLiteral* gl, std::stack< std::pair<int,int> >& stk_1, std::stack< std::pair<int,int> >& stk_2);
    bool UpdateRule_6(GroundLiteral* gl, std::stack< std::pair<int,int> >& stk_1, std::stack< std::pair<int,int> >& stk_2);
    bool UpdateRule_7(GroundLiteral* gl, std::stack< std::pair<int,int> >& stk_1, std::stack< std::pair<int,int> >& stk_2);
    bool UpdateRule_8(GroundLiteral* gl, std::stack< std::pair<int,int> >& stk_1, std::stack< std::pair<int,int> >& stk_2);
    bool UpdateRule_9(GroundLiteral* gl, std::stack< std::pair<int,int> >& stk_1, std::stack< std::pair<int,int> >& stk_2);
 	
    int negVal(int val);

    //Get the minimun value of the body
    bool CountMValue(GroundRule *r);

    void SetGroundRuleFalse(GroundRule* r, std::stack< std::pair<int,int> >& stk_2);

    void SetGroundRuleTrue(GroundRule* r, std::stack< std::pair<int,int> >& stk_2);

    //Check the consistency of attemped assigning value
    bool CheckValueConsistency(int id, int new_value);


};

#endif
