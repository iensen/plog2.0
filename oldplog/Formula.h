#pragma once
#include <string>
//#include "Atom.h"
#include "Literal.h"
#include <set>
//#include "State.h"
//#include "GroundProgram.h"
//#include "GroundLiteral.h"

class State;
class GroundProgram;
//class GroundLiteral;

class Formula
{
public:
	Formula(void);
	Formula(std::string op, Formula *f1, Formula *f2);
	Formula(Literal* a);
	Formula(std::set<Literal*> atms);
	~Formula(void);

	std::string GetName();

	//
	void AddProbability(double pb);
	double GetProbability();

	//Evaluate the truth value of the formula with a set of string 
	//bool Evaluate(const std::set<std::string>& atoms);

	//int Evaluate(const std::set<std::string>& pos, const std::set<std::string>& neg);
	//void SetFormulaId(GroundProgram* gnd);

	//int Evaluate(State* s);

	//Check whether f is a subset of this formula,or vice versa
	int IsSubset(Formula *f);

	//
	std::set<Literal*>& GetASet();

	//Collecting the atoms occurring in the formula
	void CollectAtom(std::set<std::string>& atomSet);

	//Update the upperbound and lowerbound of the probability
	void UpdateProbability(double l, bool f);

	//Set Valid
	inline void SetValid(bool f){valid=f;};

	//Get Valid
	inline bool GetValid() const {return valid;};

	//Get the min
	inline double GetMin() const {return min;};

	//Get the max
	inline double GetMax() const {return max;};

	//Check whethe two formula is same, only check aset
	bool IsEqual(Formula* f);

	//To print out the formula
	void Show();

	//Add a literal to aset
	void AddLiteral(Literal* a){aset.insert(a);};

    //Get the literal
    Literal* GetLiteral() const {return atom;};

    //Return the operator
    std::string GetOperation() const {return operation;};
    
    //Return the first formula
    Formula* GetFirstFormula() const {return formula_1;};

    //Return the second formula
    Formula* GetSecondFormula() const {return formula_2;};

    void CollectLiteral(std::set<Literal*>& litSet);

private:
	double min;
	double max;
	bool valid;
	double prob;
	std::set<Literal*> aset;  //A conjuctive form of formula
	Literal* atom;  //leaf node of Atom
	Formula *formula_1;
	Formula *formula_2;
	std::string operation;
};
