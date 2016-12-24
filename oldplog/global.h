#pragma once
#include <set>
#include <string>
#include <list>
#include <vector>
#include <map>


enum  TermType {identifier, num, oprt, var, sym, invalid};

bool IsOperator(std::string s);

//Return a term type of an term in the atom
TermType GetTermType(std::string s);

std::vector<std::string> BreakTerm(std::string s);

std::list<std::string> NextElement(std::string s);

std::string Calculate(std::string op1,std::string op2,std::string op);

std::string ReplaceExp(std::string s, std::list<std::string>& exp);

std::string Evaluate(std::string in);

std::string Replace(std::string in, std::map<std::string, std::string> vars);

std::string GetRoot(std::string s);

//Return the index to the last of 
int SubTree(int i, std::string target);

double ComputeProbability(std::string s, std::map< std::string, std::string> assignment);

void SubstractSet(std::set<std::string>& s1, std::set<std::string>& s2, std::set<std::string>& s3);

std::string GetPart(std::string in, int i);

std::string GetLastPart(std::string in);

std::string GetTerm(std::string l);


