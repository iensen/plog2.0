#include "AnswerSet.h"
#include "global.h"
#include <sstream>
#include <map>
#include <set>
#include <utility>
#include <cstdlib>
#include <iostream>

using namespace std;

AnswerSet::AnswerSet(void)
{
}

AnswerSet::~AnswerSet(void)
{
}



AnswerSet::AnswerSet(string line)
{
	map< pair<string,string>, double> pd;
	map< pair<string,string>, double> pa;
	map< string, double> total;
	map< string, int> count;
	prob=1.0;
	string word;
	string rName;
	string atomName;
	istringstream stream(line);
	while(stream >> word)
	{
		if(word.substr(0,2)=="pd"){
			rName=GetPart(word,1);
			atomName=GetPart(word,2);
			pair<string,string> p(rName ,atomName );
			count[rName]++;
			total[rName]=1.0;
			pd[p]=-1.0;
		}
		else if(word.substr(0,2)=="pa"){
			pair<string,string> p(GetPart(word,1), GetPart(word,2));
			pa[p]=AssignProbability(GetPart(word,3));
		}
		else{
			atoms.insert(word);
			//cout<<word<<" ";
		}
	}
	//cout<<pa.size()<<endl;
	//cout<<pd.size()<<endl;
	//cout<<atoms.size()<<endl;
	map< pair<string, string>, double>::iterator itr;
	itr=pa.begin();
	while(itr!=pa.end()){
		if(pd.find(itr->first)!=pd.end()){
			pd[itr->first]=itr->second;
			count[itr->first.first]--;
			total[itr->first.first]-=itr->second;
		}
		++itr;
	}
	itr=pd.begin();
	while(itr!=pd.end()){
		//cout<<itr->first.second;
		if(atoms.find(itr->first.second)!=atoms.end()){
			if(pd[itr->first]<0.0){
				prob*=total[itr->first.first]/(double) count[itr->first.first];
			}
			else prob*=pd[itr->first];
			//cout<<itr->first.second<<" "<<prob<<endl;
		}
		++itr;
	}
}



double AnswerSet::AssignProbability(string in)
{
	double value=0.0;
	string opr;
	string op1, op2;
	if(in.find('(')!=string::npos){
		opr=GetPart(in,0);
		op1=GetPart(in,1);
		op2=GetPart(in,2);
		if(opr=="di_"){//divide
			value=AssignProbability(op1)/AssignProbability(op2);
		}
		else if(opr=="time_"){
			value=AssignProbability(op1)*AssignProbability(op2);
		}
		else if(opr=="plu_"){
			value=AssignProbability(op1)+AssignProbability(op2);
		}
		else if(opr=="minu_"){
			value=AssignProbability(op1)-AssignProbability(op2);
		}
	}
	else{
		value=atoi(in.c_str());
	}
	return value;
}

set<string> &AnswerSet::GetAtoms()
{
	return atoms;
}

double AnswerSet::GetProbability()
{
	return prob;
}


void AnswerSet::AddBasicFormula(Query *qry)
{
	string word;
	set<Literal*> atm;
	//set<string> &atom=a->GetAtoms();
	list<Literal*>::iterator itr_atm;
	itr_atm=qry->atoms.begin();
    //cout<<qry->atoms.size()<<endl;
	while(itr_atm!=qry->atoms.end())
	{
        		
        if(atoms.find((*itr_atm)->ToString())!=atoms.end()){
			atm.insert(*itr_atm);
		}
		++itr_atm;
	}
    //cout<<"Answer Set->AddBasicFormula "<<atm.size()<<endl;
	Formula *f=new Formula(atm);
	
	qry->AddFormula(f); //add new formula
}


void AnswerSet::CollectFormula(Query *qry)
{
	//set<string> &atom=a->GetAtoms();
	set<Literal*> atm;
	list<string>::iterator itr_tm;
	set<string>::iterator itr,itrs;
	itr_tm=qry->terms.begin();
    while(itr_tm!=qry->terms.end()){
        string s(*itr_tm);
		if(s.find('(')==string::npos) s=s+"(";
		else s[s.length()-1]=',';
        //cout<<"Collect Formula "<<s<<endl;
		itrs=atoms.begin();
		while(itrs!=atoms.end()){
			if(itrs->length()>s.length() && itrs->substr(0,s.length())==s){
                //cout<<"Collect Formula "<<*itrs<<endl;
				//Here find out the object Atom*
                Literal *l=new Literal(*itr_tm, GetLastPart(*itrs));
				atm.insert(l);
				break;
			}
			++itrs;
		}
		if(itrs==atoms.end()) return;
		++itr_tm;
	}
	qry->AddFormula(new Formula(atm));
}

void AnswerSet::EvaluateQuery(Query *qry)
{
    list<Formula*>::iterator itr_fml;
    itr_fml=qry->formula.begin();
    while(itr_fml!=qry->formula.end()){
        if(EvaluateFormula(*itr_fml)){
            (*itr_fml)->UpdateProbability(prob, true);
        }
        else{
            (*itr_fml)->UpdateProbability(prob, false);
        }
        ++itr_fml;
    }   
}

bool AnswerSet::EvaluateFormula(Formula *f)
{
    if(f->GetLiteral()!=NULL){
        if(atoms.find(f->GetLiteral()->ToString())!=atoms.end()) return true;
        else return false;
    }
    else if (f->GetOperation()==""){
        set<Literal*>::iterator itr_set=f->GetASet().begin();
        while(itr_set!=f->GetASet().end()){
            if(atoms.find((*itr_set)->ToString())==atoms.end()) return false;
            ++itr_set;
        }
        return true;
    }
    else if(f->GetOperation()=="and"){
        if(EvaluateFormula(f->GetFirstFormula()) && EvaluateFormula(f->GetSecondFormula())) return true;
        else return false;
    }
    else if(f->GetOperation()=="or"){
        if(EvaluateFormula(f->GetFirstFormula()) || EvaluateFormula(f->GetSecondFormula())) return true;
        else return false;
    }
    else if(f->GetOperation()=="!"){
        if(EvaluateFormula(f->GetFirstFormula())) return false;
        else return true;
    }
    else return false;
}

