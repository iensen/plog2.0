#pragma once
#include <string>
#include <list>
#include <set>
#include <map>
#include <vector>

//enum TermType {id, num, oprt,var,invalid}; //identifier, number, operator and variable

class TermTree
{
public:
    TermTree(std::string s);
    TermTree(std::string s, std::list<TermTree*> chld);
    //Using the subtree of t rooted at ith position to create a new term tree
    TermTree(TermTree *t, size_t idx); 
    //Create a new term tree of t wtih expression evaluated by using value
    //TermTree(TermTree *t, std::map<std::string, std::string> value);
    TermTree(TermTree *t);

    ~TermTree(void);

public:
	//Get the root of the term tree
    std::string GetRoot();
	
	//Get the normal expression of a term. i.e., a(b(c), d(c))
    std::string GetName();

	//Get the ith element
    std::string GetName(size_t idx);

	//Get the parent of a node placed in idx-th position
    int GetParentPos(size_t idx);
    //TermType GetType(size_t idx);
	//Return the total number of symbols
    size_t GetSize();

	//
    int GetPosition(size_t idx);
	
	//Append the a new term tree at the end of this term tree
 	void Append(TermTree* t);

    //Append a list of subtree as the child of the node indicated by idx
    bool Append(int idx, std::list<TermTree&> chld); 

	//Replace a subtree  rooted at ith node by a string
	//size_t Replace(size_t idx, std::string s);
	//void CollectVariable(std::set<std::string>& addin);
	//void CollectVariable(std::set<std::string>& addin, std::set<std::string>& notin);
	//std::string Evaluate(std::map<std::string, std::string>& value);


private:

	//Get the height of a symobl in the tree
    int GetHeight(size_t idx); 
	

	//bool IsOperator(std::string);
private:
	//Two array representation of tree structure
	//For exmaple: a(b, c(d)) is represented as
	//Array term:     a  b  c  d
	//Array parent:   -1 0  0  2


	
	//A vector to storing all function terms
    std::vector<std::string> term;

	//A vector to indicate its parent position
    std::vector<int> parent;

	//The size of the arrays
    size_t size;

    //bool IsNonNegInteger(std::string s);
	//bool IsValidString(std::string s);
};
