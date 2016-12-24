#include "GroundLiteral.h"
#include <iostream>

using namespace std;

GroundLiteral::GroundLiteral(void):rndlit(false), support(0), truthValue(3)  //unknown
{
}

/*
GroundLiteral::GroundLiteral(Literal *l):lit(l)
{
	name=lit->GetName();
	headRule.size();
}
*/
/*
GroundLiteral::GroundLiteral(TermTree* tm)
{
	Atom *a=new Atom(tm);
	name=a->GetName();
}
*/
GroundLiteral::GroundLiteral(std::string s, string v, bool sn):name(s), value(v),
sign(sn), rndlit(false),support(0),truthValue(3) //unknown
{
	
}

/*
GroundLiteral::GroundLiteral(Atom* a)
{
	name=a->GetName();
}
*/


GroundLiteral::~GroundLiteral(void)
{
}

std::string GroundLiteral::GetName()
{
	if(sign) return name+"="+value;
    else return "-"+name+"="+value;
}

void GroundLiteral::AddPosRule(GroundRule *gr)
{
	posRule.push_back(gr);
}

void GroundLiteral::AddNegRule(GroundRule *gr)
{
	negRule.push_back(gr);
}
	
void GroundLiteral::AddHeadRule(GroundRule *gr)
{
	headRule.push_back(gr);
}
	
void GroundLiteral::SetTerm(GroundTerm *t)
{
	term=t;
}

GroundRule* GroundLiteral::GetEmptyRule()
{
	vector<GroundRule*>::iterator itr;
	itr=headRule.begin();
	while(itr!=headRule.end()){
		if((*itr)->GetType()==reg){
			
			//cout<<"The size of the rule "<<(*itr)->GetBodySize(true)+(*itr)->GetBodySize(false)<<":";
			//(*itr)->Show();
			if((*itr)->GetBodySize(true)+(*itr)->GetBodySize(false)==0){
				return *itr;
			}
		}
		++itr;
	}
	return NULL;
}


void GroundLiteral::Reduction(bool flag, stack<GroundLiteral*>& pos, stack<GroundLiteral*>& neg)
{
	//Remove all the rules that gl is its head
	//Remove all the rules that is falised
	//Remove all the rule gl is in its pos, 
	//if gr is emtpy size and regular, add head to stack
	vector<GroundRule*>::iterator itr;
	itr=headRule.begin();
	while(itr!=headRule.end()){
		(*itr)->SetValid(false);
		++itr;
	}
	//Remove all the links
	if(flag==true){
		itr=posRule.begin();
		while(itr!=posRule.end()){
			(*itr)->RemoveLiteral(true, this, pos, neg);
			++itr;
		}
		itr=negRule.begin();
		while(itr!=negRule.end()){
			//negRule.erase(itr);
			if((*itr)->GetValid()){
			    (*itr)->SetValid(false);
			    //(*itr)->Show();
			    (*itr)->GetHead()->CheckHead(pos,neg);
			}
			++itr;
		}
	}
	else{
		itr=negRule.begin();
		while(itr!=negRule.end()){
			(*itr)->RemoveLiteral(false, this, pos, neg);
			++itr;
		}
		itr=posRule.begin();
		while(itr!=posRule.end()){
			if((*itr)->GetValid()){
				(*itr)->SetValid(false);
				//(*itr)->Show();
				(*itr)->GetHead()->CheckHead(pos,neg);
			}
			++itr;
		}
	}
}

GroundTerm* GroundLiteral::GetTerm()
{
	return term;
}

void GroundLiteral::CheckHead(std::stack<GroundLiteral*>& pos, std::stack<GroundLiteral*>& neg)
{
	vector<GroundRule*>::iterator itr;
	itr=headRule.begin();
	while(itr!=headRule.end()){
		if((*itr)->GetValid()==true) return;
		++itr;
	}
	neg.push(this);
}
	
void GroundLiteral::CollectTerm(std::set<GroundTerm*>& stk, std::set<GroundTerm*>& checked)
{
	vector<GroundRule*>::iterator itr;
	GroundTerm *tm;
	itr=headRule.begin();
	size_t idx, sz;
	while(itr!=headRule.end()){
        if((*itr)->GetValid()==false){
            ++itr;
            continue;
        }
		sz=(*itr)->GetBodySize(true); //Positive
		for(idx=0;idx<sz;idx++){
			tm=(*itr)->GetBodyLit(idx, true)->GetTerm();
			if(checked.find(tm)==checked.end()) stk.insert(tm);
		}
		sz=(*itr)->GetBodySize(false); //Negtive
		for(idx=0;idx<sz;idx++){
			tm=(*itr)->GetBodyLit(idx, false)->GetTerm();
			if(checked.find(tm)==checked.end()) stk.insert(tm);
		}
		++itr;
	}
}

void GroundLiteral::SetId(size_t i)
{
	id=i;
}

size_t GroundLiteral::GetId()
{
	return id;
}

size_t GroundLiteral::GetHeadRuleSize()
{
	return headRule.size();
}

GroundRule* GroundLiteral::GetHeadRule(size_t idx)
{
	return headRule[idx];
}

size_t GroundLiteral::GetBodySize(bool flag)
{
	if(flag==true) return posRule.size();
	else return negRule.size();
}

GroundRule* GroundLiteral::GetBodyRule(size_t idx, bool flag)
{
	if(flag==true) return posRule[idx];
	else return negRule[idx];
}


int GroundLiteral::CountPositiveLiteral()
{
	size_t i, sz;
	int counter=0;
	sz=term->GetSize();
	for(i=0;i<sz;i++){
		GroundLiteral* gl=term->GetLiteral(i);
		if(gl->GetSign() && gl->GetValue()!=GetValue()) counter++;
	}
	return counter;
}

bool GroundLiteral::GetSign()const
{
	return sign;
}

string GroundLiteral::GetValue()const
{
	return value;
}
/*
string GroundLiteral::ToString() const
{
	string toString=term->GetName();
	size_t len=toString.length();
	if(toString[len-1]==')') toString[len-1]=',';
	else toString[len-1]='(';
	toString=toString+value+")";
	if(sign==false) toString="-"+toString;
	return toString;	
}
*/






