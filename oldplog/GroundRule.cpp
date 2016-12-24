#include "GroundRule.h"
#include <sstream>
#include <iostream>
using namespace std;

GroundRule::GroundRule(void):valid(true)
{
}

GroundRule::GroundRule(Rule *r):type(r->GetType()), range(NULL),head(NULL),valid(true)
{
}


GroundRule::~GroundRule(void)
{
}

void GroundRule::AddLiteral(GroundLiteral *gl, bool sign)
{
	if(sign==true){
		posBody.push_back(gl);
	}
	else{
		negBody.push_back(gl);
	}
}

void GroundRule::AddName(std::string s)
{
	ruleName=s;
}

void GroundRule::AddHead(GroundLiteral *gl)
{
	head=gl;
}


void GroundRule::AddRange(GroundLiteral *gl)
{
	range=gl;
}

/*
void GroundRule::AddProbability(TermTree *exp, map<string, string>& assignment)
{
	//TermTree* tm=new TermTree(exp, assignment);
	//probability=AssignedProbability(tm->GetName());	
	stringstream ss;
	//cout<<exp->GetName()<<endl;
	ss<<exp->Evaluate(assignment);
	ss>>probability;
	//cout<<probability<<endl;
	
}*/

void GroundRule::Show()
{
	if(type==reg) cout<<"(l)"; //Regular logic rule
	else if(type==cr) cout<<"(c)"; //Cr rules
	else if(type==rnd_) cout<<"(r)"; //Random selection rule
	else if(type==pr) cout<<"(p)";		//Pr rules
	//cout<<endl;
	cout<<"  "<<head->GetName();
	if(posBody.size()+negBody.size()!=0) cout<<":-";
	vector<GroundLiteral*>::iterator itr_lit;
	itr_lit=posBody.begin();
	while(itr_lit!=posBody.end()){
		cout<<(*itr_lit)->GetName()<<" ";
		++itr_lit;
	}
	itr_lit=negBody.begin();
	while(itr_lit!=negBody.end()){
		cout<<"not "<<(*itr_lit)->GetName()<<" ";
		++itr_lit;
	}
	cout<<". Valid="<<valid;
	//if(type!=reg) cout<<endl<<"Rule Name: "<<ruleName<<endl;
	if(range!=NULL) cout<<"Range: "<<range->GetName()<<endl;
	if(type==pr) cout<<"Probability: "<<probability<<endl;
	cout<<endl;

}

GroundLiteral* GroundRule::GetHead()
{
	return head;
}

size_t GroundRule::GetBodySize(bool flag)
{
	if(flag==true) return posBody.size();
	else return negBody.size();
}

GroundLiteral* GroundRule::GetBodyLit(size_t idx, bool flag)
{
	if(flag==true){
		if(idx>=0 && idx<=posBody.size()) return posBody[idx];
	}
	else{
		if(idx>=0 && idx<=negBody.size()) return negBody[idx];
	}
	return NULL;
}

void GroundRule::SetLink()
{
	head->AddHeadRule(this);
	size_t idx,size;
	size=posBody.size();
	for(idx=0;idx<size;idx++){
		posBody[idx]->AddPosRule(this); 
	}
	size=negBody.size();
	for(idx=0;idx<size;idx++){
		negBody[idx]->AddNegRule(this); 
	}
}

void GroundRule::RemoveLiteral(bool flag, GroundLiteral* gl, 
		stack<GroundLiteral*>& pos, stack<GroundLiteral*>& neg)
{
	vector<GroundLiteral*>::iterator itr, itr1;
	
	if(flag==true){
		itr=posBody.begin();
		while(itr!=posBody.end()){
			if((*itr)==gl){
			    itr=posBody.erase(itr);
	    
			}
			else ++itr;
		}
	}
	else{
		itr=negBody.begin();
		while(itr!=negBody.end()){
			if((*itr)==gl){
			    itr=negBody.erase(itr);
			}
			else ++itr;
		}
	}
	if(GetBodySize(true)+GetBodySize(false)==0 && type==reg){
		pos.push(head);
		
	}
}

vector<GroundLiteral*>& GroundRule::ReturnBody(bool flag)
{
    //cout<<"heoe"<<endl;
    if(flag==true) return posBody;
    else return negBody;
}











