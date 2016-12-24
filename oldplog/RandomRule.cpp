#include "RandomRule.h"
#include <iostream>

using namespace std;

RandomRule::RandomRule(void)
{
}

RandomRule::~RandomRule(void)
{
}

RandomRule::RandomRule(std::string name):ruleName(name),rndRule(NULL)
{
	
}

void RandomRule::AddPrRules(GroundRule* r)
{
	prRule.push_back(r);
}

void RandomRule::AddRange(GroundLiteral* gl)
{
	//rng->GetSolution();
	range.push_back(gl);
}

void RandomRule::AddHead(GroundLiteral* gl)
{
	head.push_back(gl);
}

void RandomRule::AddRandomRule(GroundRule* r)
{
	rndRule=r;
}


void RandomRule::CollectTerm(set<GroundTerm*>& stk, set<GroundTerm*>& checked)
{
	GroundTerm* tm;
	size_t sz=rndRule->GetBodySize(true);
	size_t idx;
	for(idx=0;idx<sz;idx++){
		tm=rndRule->GetBodyLit(idx,true)->GetTerm();
		if(checked.find(tm)==checked.end()) stk.insert(tm);
	}
	sz=rndRule->GetBodySize(false);
	for(idx=0;idx<sz;idx++){
		tm=rndRule->GetBodyLit(idx,false)->GetTerm();
		if(checked.find(tm)==checked.end()) stk.insert(tm);
	}
	vector<GroundRule*>::iterator itr;
	//cout<<prRule.size()<<endl;
	itr=prRule.begin();
	while(itr!=prRule.end()){
		sz=(*itr)->GetBodySize(true);
		for(idx=0;idx<sz;idx++){
			tm=(*itr)->GetBodyLit(idx,true)->GetTerm();
			if(checked.find(tm)==checked.end()) stk.insert(tm);
		}
		sz=(*itr)->GetBodySize(false);
		for(idx=0;idx<sz;idx++){
			tm=(*itr)->GetBodyLit(idx,false)->GetTerm();
			if(checked.find(tm)==checked.end()) stk.insert(tm);
		}
		++itr;
	}
	vector<GroundLiteral*>::iterator itr_glit;
	itr_glit=range.begin();
	while(itr_glit!=range.end()){
		tm=(*itr_glit)->GetTerm();
		if(checked.find(tm)==checked.end()) stk.insert(tm);
		++itr_glit;
	}

}

//Get the number of head in the vector head
size_t RandomRule::GetHeadSize()
{
	return head.size();
}

GroundLiteral* RandomRule::GetRangeLiteral(size_t idx)
{ 
	if(range.size()!=0) return range[idx];
	else return NULL;
}

//Get the head literal
GroundLiteral* RandomRule::GetHeadLiteral(size_t idx)
{
	if(idx>=0 && idx<head.size()) return head[idx];
	else return NULL;
}


void RandomRule::SetValid()
{
	size_t sz=rndRule->GetBodySize(true);
	size_t idx;
	GroundLiteral* gl;
	for(idx=0;idx<sz;idx++){
		gl=rndRule->GetBodyLit(idx,true);
		if(gl->GetTruthValue()==1) rndRule->SetValid(false);  //Falsified
	}
	sz=rndRule->GetBodySize(false);
	for(idx=0;idx<sz;idx++){
		gl=rndRule->GetBodyLit(idx,false);
		if(gl->GetTruthValue()==5) rndRule->SetValid(false);  //Falsified
	}
	vector<GroundRule*>::iterator itr;
	//cout<<prRule.size()<<endl;
	itr=prRule.begin();
	while(itr!=prRule.end()){
		sz=(*itr)->GetBodySize(true);
		for(idx=0;idx<sz;idx++){
			gl=(*itr)->GetBodyLit(idx,true);
			if(gl->GetTruthValue()==1) (*itr)->SetValid(false);  //Falsified
		}
		sz=(*itr)->GetBodySize(false);
		for(idx=0;idx<sz;idx++){
			gl=(*itr)->GetBodyLit(idx,false);
			if(gl->GetTruthValue()==5) (*itr)->SetValid(false);  //Falsified
		}
		++itr;
	}
	
}

//Get the range vector
vector<GroundLiteral*>& RandomRule::GetRange()
{
	return range;
}

	//Get the pr rules
vector<GroundRule*>& RandomRule::GetPrRule()
{
	return prRule;
}

void RandomRule::Show()
{
	rndRule->Show();
	vector<GroundRule*>::iterator itr_gr;
	vector<GroundLiteral*>::iterator itr_gl;
	if(range.size()!=0){
		cout<<"Range: ";
		itr_gl=range.begin();
		while(itr_gl!=range.end()){
			cout<<(*itr_gl)->GetName()<<" ";
			++itr_gl;
		}
		cout<<endl;
	}
	itr_gr=prRule.begin();
	while(itr_gr!=prRule.end()){
		(*itr_gr)->Show();
		++itr_gr;
	}
}
