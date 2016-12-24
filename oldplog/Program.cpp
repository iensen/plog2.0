#include "Program.h"
#include <iostream>

using namespace std;

Program::Program(void)
{
}

Program::~Program(void)
{
}

void Program::AddRule(Rule* r)
{
	rule.push_back(r);
	
}

void Program::AddSort(Sort* s)
{
	sort.insert(s);
}

void Program::AddAttribute(Attribute* a)
{
	attr.insert(a);
}

/*
void Program::AddDoStatement(Atom *a)
{
	dos.push_back(a);
}
void Program::AddObsStatement(Atom *l)
{
	obs.push_back(l);
}
*/

void Program::AddVariable(Variable *v)
{
	variable.insert(v);
}

/*
void Program::AddFormula(Formula *f)
{
	formula.push_back(f);
}*/

std::string Program::GetAttributeRange(std::string att)
{
	set<Attribute*>::iterator itr;
	itr=attr.begin();
	while(itr!=attr.end()){
		if((*itr)->GetName()==att) return (*itr)->GetSortName();
		++itr;
	}
	//Not found , return empyt
	return "";
}

Sort* Program::GetSort(std::string name)
{
	set<Sort*>::iterator itr;
	itr=sort.begin();
	while(itr!=sort.end()){
		if((*itr)->GetObject()==name) return *itr;
		++itr;
	}
	return NULL;
}


void Program::Show()
{
	cout<<"SORT"<<endl;
	set<Sort*>::iterator itr_sort;
	itr_sort=sort.begin();
	while(itr_sort!=sort.end()){
		(*itr_sort)->Show();
		++itr_sort;
	}
	cout<<endl;
	cout<<"ATTRIBUTE "<<endl;
	set<Attribute*>::iterator itr_attr;
	itr_attr=attr.begin();
	while(itr_attr!=attr.end()){
		(*itr_attr)->Show();
		++itr_attr;
	}
	cout<<endl;
	cout<<"VARIABLE"<<endl;
	set<Variable*>::iterator itr_var;
	itr_var=variable.begin();
	while(itr_var!=variable.end()){
		(*itr_var)->Show();
		++itr_var;
	}
	cout<<endl;

	cout<<"RULE"<<endl;
	list<Rule*>::iterator itr_rule;
	itr_rule=rule.begin();
	while(itr_rule!=rule.end()){
		(*itr_rule)->Show();
		++itr_rule;
	}
	cout<<endl;
	
}
