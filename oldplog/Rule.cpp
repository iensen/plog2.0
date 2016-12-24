#include "Rule.h"
#include "global.h"
#include <iostream>

using namespace std;
Rule::Rule(void)
{
}

Rule::~Rule(void)
{
}

Rule::Rule(string s, ruleType rt):name(s),rType(rt), range(NULL)
{
	
}

Rule::Rule(ruleType rt):rType(rt),range(NULL)
{
}

Rule::Rule(Rule *r)
{
	rType=r->GetType();
	name=r->GetRuleName();
	exp=r->GetProbability();
	range=r->GetRange();
}

Literal* Rule::GetLiteral(size_t idx)
{
	if(idx<body.size()&& idx>=0) return body[idx];
	else return NULL;
}

std::string Rule::BodyToString()
{
	size_t i, j;
	string output="";
	vector<Literal*>::iterator itr;
	i=GetBodySize();
	j=0;
	itr=body.begin();
	while(itr!=body.end()){
		if((*itr)->GetNaf()==false) output+="not ";
		output+=(*itr)->ToString();
		++itr;
		++j;
		if(j!=i) output+=",";
	}
	return output;
}

void Rule::CollectVariable()
{
	
	set<string> fixedVariable;
    set<string> allVariable;
    set<string> ctrVariable;
	//head->CollectAttributeVariable(fixedVariable);
	head->CollectHeadVariable(fixedVariable);
    if(rType==rnd_) head->CollectHeadVariable(allVariable);
    else{
        head->CollectVariable(allVariable);
        head->SetVariable(fixedVariable);
    }
	//if(fixedVariable.empty() && freeVariable.empty()) grounded=true;
	vector<Literal*>::iterator itr;
	itr=body.begin();
	while(itr!=body.end()){
        if((*itr)->GetType()==predefined) (*itr)->CollectVariable(ctrVariable);
		(*itr)->CollectVariable(allVariable);
        (*itr)->SetVariable(fixedVariable);
		++itr;			
	}
    SubstractSet(allVariable, fixedVariable, freeVariable);
    SubstractSet(freeVariable, ctrVariable, listVariable);
}

std::set<std::string> Rule::GetVariable()
{
	return freeVariable;
}

//Replace expression by special symbol #
void Rule::Normalize()
{
    list<string>::iterator itr;
    list<string> lstLit;
	head->SetTerm(ReplaceExp(head->GetTerm(),lstLit));
    itr=lstLit.begin();
    while(itr!=lstLit.end()){
        Literal *l=new Literal(*itr, "true");
        l->SetType(predefined);
        AddBody(l);
        ++itr;
    }
}

bool Rule::IsGround()
{
    set<string> vars;
    head->CollectVariable(vars);
    if(vars.empty()) return true;
    else return false;
}

void Rule::CheckFact(std::set<std::string>& facts)
{
    vector<Literal*>::iterator itr_l;
    itr_l=body.begin();
    while(itr_l!=body.end()){
        if((*itr_l)->GetType()==regl){
            if(facts.find(GetRoot((*itr_l)->GetName()))!=facts.end()){
                (*itr_l)->SetType(predefined);
             }
        }
        ++itr_l;
    }
}

void Rule::Show()
{
	if(rType==reg) cout<<"(l)"; //Regular logic rule
	else if(rType==cr) cout<<"(c)"; //Cr rules
	else if(rType==rnd_) cout<<"(r)"; //Random selection rule
	else if(rType==pr) cout<<"(p)";		//Pr rules
	cout<<"  "<<head->GetName()<<":-";
	
	cout<<BodyToString()<<endl;
	cout<<"Free Variables: ";
	set<string>::iterator itrs;
	itrs=freeVariable.begin();
	while(itrs!=freeVariable.end()){
		cout<<(*itrs)<<" ";
		++itrs;
	}
    cout<<"List Variables: ";
	//set<string>::iterator itrs;
	itrs=listVariable.begin();
	while(itrs!=listVariable.end()){
		cout<<(*itrs)<<" ";
		++itrs;
	}
	cout<<endl;
	if(name!="") cout<<"Rule Name: "<<name<<endl;
	if(range!=NULL) cout<<"Range: "<<range->GetName()<<endl;
	if(exp!="") cout<<"Probability: "<<exp<<endl;
	cout<<endl;
}


/*
void Rule::AddBody(Atom *l)
{
	body.push_back(l);
    
	if(l->GetType()==regl){
		if(l->GetNaf()==true) posSize++;
		else negSize++;
	}
	else if(l->GetType()==predefined){
		conSize++;
	}
}*/

/*
void Rule::AddNegBody(Literal *l)
{
	negBody.push_back(l);
}

void Rule::AddConstraint(Literal *c)
{
	constraint.push_back(c);
}
*/


/*
size_t Rule::GetTotalSize()
{
	return posSize+negSize+conSize;
}
*/

/*
size_t Rule::GetPosSize()
{
	return posSize;
}

size_t Rule::GetNegSize()
{
	return negSize;
}

//Get the size of constriants
size_t Rule::GetConSize()
{
	return conSize;
}

Atom* Rule::GetLiteral(size_t idx, bodyLiteral bl)
{
	if(bl==_pos) return body[idx];
	else if(bl==_neg) return body[posSize+idx];
	else if(bl==_con) return body[posSize+conSize+idx];
	else return NULL;
}

TermTree* Rule::GetRuleName()
{
	return name;
}




bool Rule::GetGround()
{
	return grounded;
}


/*
void Rule::AddSort(Sort* s)
{
	st=s;
}
*/






