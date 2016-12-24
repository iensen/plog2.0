#pragma once
//#include "TermTree.h"
#include "Variable.h"
#include <vector>
#include <string>
#include <list>
#include <map>
#include <set>

enum  LiteralType {regl, obs, dos, predefined}; 

class Literal
{
public:
	Literal();

	Literal(std::string, std::string);

	//Create a new literal by replacing variables in the l with its value
	Literal(Literal *l, std::map<std::string, std::string> val);

    Literal(std::string s, std::map<std::string, std::string> val);
	
	//Create a copy of l
	Literal(Literal *l);

	~Literal(void);

//Member function:
    void SetTerm(std::string s){term=s;};
	//Get the Term of the atom
	std::string GetTerm() const {return term; }

	//Return the type of an atom
	LiteralType GetType() const {return type;};

	//Set the type of an atom
	void SetType(LiteralType at){type=at;};

	//Return the sign of the atom
	bool GetSign() const {return sign;};

	//Set the sign of atom
	void SetSign(bool s){sign=s;};

	//set value to atom
	void SetValue(std::string s){value=s;};

	//Get the expression of the atom
	std::string GetValue() const {return value;}

	//Get and set the value of naf
	bool GetNaf(){return naf;};
    
	void SetNaf(bool flag){naf=flag;};

	//Get and set the Id
    void SetId(int i){id=i;};
    
	int GetId() const { return id; };

    //Get the string representation of an atom and stored in member 'name'
	std::string GetName();

	//Get a string representation of atom a(t)=y -> a(t,y)
	//-a(t)=y -> -a(t,y)
	//a -> a(true)
	//-a -> -a(true)
	//a=false -> a(false)
	std::string ToString();

	//Add variable v to set addin
	void CollectVariable(std::set<std::string>& addin);

    void CollectHeadVariable(std::set<std::string>& addin);

    std::set<std::string>& GetVariable(){return variable;};

    void SetVariable(std::set<std::string>& fixed);
       
    /*
	//Compute the solution of the literal
	bool GetSolution(std::map<std::string, std::string>& assignment, 
		std::set<std::string>& pos, std::set<std::string>& neg, bool flag);

	//Return the solution
	std::vector< std::vector<std::string> >& GetSolution(); */

	//Check whether the literal is ground or not
	bool IsGround(); //Return true if the literal is a literal with no variables
    /*
	//check whether a ground atom is valid or not
	bool CheckValue(std::set<std::string>& positiveAtom, 
	                std::set<std::string>& negativeAtom, 
	                bool fFact);
    */

private:
    std::string name;
	std::string term;
	std::string value;
	int id;
	bool sign; 
	bool naf;
	LiteralType type;
	std::vector< std::vector<std::string> > solution;
	
    std::set<std::string> variable;
      

    //Reset all the variables
	void Reset();

	//Get the next valid assignment of free variables
	bool NextValue(std::map<std::string,std::string>& value, bool init);

	//Test wheather a literal is true or not
	bool Test(std::set<std::string>& pos, std::set<std::string>& neg,
		bool flag, std::map<std::string,std::string>& value);

	//Add the solution to the solution of the literal
	void AddSolution(std::map<std::string, std::string>& V);

    /*
    bool CheckTerm(std::string a, std::string b,std::map<std::string, 
                    std::string>& assignment, std::map<std::string, Variable*>& vars);

    vector<std::string> BreakTerm(std::string s);

    bool Match(std::string s1, std::string s2, std::map<std::string, std::string>& assignment, std::map<std::string, Variable*>& vars)
    */

    
};
