#include "Query.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

Query::Query(void)
{
}

Query::~Query(void)
{
}
void Query::AddCondition(Literal *l)
{
	condition.push_back(l);
}
void Query::AddFormula(Formula *f)
{
    list<Formula*>::iterator itr_f;
    if(!f->GetASet().empty()){
	    itr_f=formula.begin();
	    while(itr_f!=formula.end()){
		    int i=f->IsSubset(*itr_f);
            //cout<<"Add Formula "<<i<<endl;
		    if(i==1) return;
		    else if(i==-1){//atm is the subset of (*itr_set)
			    itr_f=formula.erase(itr_f);
			    continue;
		    }
		    ++itr_f;
	    }	
    }
    formula.push_back(f);
}

/*
void Query::EvaluateFormula(AnswerSet *a)
{
	//static binggo;	
	list<Formula*>::iterator itr_fml;
	itr_fml=formula.begin();
	while(itr_fml!=formula.end()){
		if((*itr_fml)->Evaluate(a->GetAtoms())){
			(*itr_fml)->AddProbability(a->GetProbability());
			//cout<<(*itr_fml)->GetProbability()<<endl;
		}
		++itr_fml;
	}
}
*/


bool Query::GetMaximunFormula() //Return true if there exists one formula, its probability > 0
{
	list<Formula*>::iterator itr_fml;
	answers.clear();
	double maximun=0.0;
	double precision=0.00001; //Precision;
	itr_fml=formula.begin();
	while(itr_fml!=formula.end()){
		if((*itr_fml)->GetMin()-maximun>precision){
			answers.clear();
			answers.push_back(*itr_fml);
			maximun=(*itr_fml)->GetMin();
	    }
		else if( fabs((*itr_fml)->GetMin()-maximun)<precision)
		{
			answers.push_back(*itr_fml);
		}
		++itr_fml;
	}
	if(answers.size()==0) return false;
	else return true;
}

void Query::CollectFormulaAtom(std::set<string>& atomSet)
{
	if(type==1){
		list<Formula*>::iterator itr_fml;
		itr_fml=formula.begin();
		while(itr_fml!=formula.end()){
			(*itr_fml)->CollectAtom(atomSet);
			 ++itr_fml;
		}
	}
	else if(type==2){
		list<string>::iterator itr_tm;
		itr_tm=terms.begin();
		while(itr_tm!=terms.end()){
			atomSet.insert(*itr_tm);
			++itr_tm;
		}
	}
	else if(type==3){
		list<Literal*>::iterator itr_atm;
		itr_atm=atoms.begin();
		while(itr_atm!=atoms.end()){
			atomSet.insert((*itr_atm)->GetTerm());
			++itr_atm;
		}
	}
}


void Query::SetType(int i)
{
	type=i;
}

int Query::GetType()
{
	return type;
}

/*
void Query::AddBasicFormula(AnswerSet *a)
{
	string word;
	set<Atom*> atm;
	set<string> &atom=a->GetAtoms();
	list<Atom*>::iterator itr_atm;
	itr_atm=atoms.begin();
	while(itr_atm!=atoms.end())
	{
		if(atom.find((*itr_atm)->ToString())!=atom.end()){
			//atm.insert(gnd->gLit[(*itr_atm)->GetName()]);
		}
		++itr_atm;
	}
	Formula *f=new Formula(atm);
	list<Formula*>::iterator itr_f;
	itr_f=formula.begin();
	while(itr_f!=formula.end()){
		int i=f->IsSubset(*itr_f);
		if(i==1){
			return;
		}
		else if(i==-1){//atm is the subset of (*itr_set)
			formula.erase(itr_f);
			formula.push_front(f); 
			return;
		}
		++itr_f;
	}
	AddFormula(f); //add new formula
}


void Query::CollectFormula(AnswerSet *a)
{
	set<string> &atom=a->GetAtoms();
	set<Atom*> atm;
	list<TermTree*>::iterator itr_tm;
	set<string>::iterator itr,itrs;
	itr_tm=terms.begin();
	while(itr_tm!=terms.end()){
		string s=(*itr_tm)->GetName();
		if(s.find('(')==string::npos) s=s+"(";
		else s[itr->length()-1]=',';
		itrs=atom.begin();
		while(itrs!=atom.end()){
			if(itrs->length()>s.length() && itrs->substr(0,s.length())==s){
				//Here find out the object Atom*
				//atm.insert(*itrs);
				break;
			}
			++itrs;
		}
		if(itrs==atom.end()) return;
		++itr_tm;
	}
	AddFormula(new Formula(atm));
}

*/
bool Query::IsSuper(Formula *f)
{
    list<Formula*>::iterator itr_fml;
    itr_fml=formula.begin();
    while(itr_fml!=formula.end()){
        if(f->IsSubset(*itr_fml)==1) return true;
        ++itr_fml; 
    }
    return false;
}

void Query::CollectAtoms(Literal *a)
{
	atoms.push_back(a);
}

void Query::ShowAnswer()
{
	cout<<"Answer"<<endl;
	list<Formula*>::iterator itr_fml;
	itr_fml=answers.begin();
	while(itr_fml!=answers.end()){
		cout<<(*itr_fml)->GetName()<<" probability: "
			<<(*itr_fml)->GetMin()<<" "<<(*itr_fml)->GetMax()<<endl;
		++itr_fml;
	}
}


void Query::Show()
{
	cout<<"Query: "<<type<<endl;
	if(type==2){
		list<string>::iterator itr_atm;
		itr_atm=terms.begin();
		while(itr_atm!=terms.end()){
			cout<<(*itr_atm)<<" ";
			++itr_atm;
		}
		cout<<endl;	
	}
	list<Formula*>::iterator itr_f;
	itr_f=formula.begin();
	while(itr_f!=formula.end()){
		cout<<(*itr_f)->GetName()<<"  ";
		++itr_f;
	}
	cout<<endl;
	list<Literal*>::iterator itr_l;
	itr_l=condition.begin();
	while(itr_l!=condition.end()){
		cout<<(*itr_l)->GetName()<<"  ";
		++itr_l;
	}
	cout<<"Query end"<<endl;
}
