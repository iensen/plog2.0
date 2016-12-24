#include "GroundTerm.h"

using namespace std;

GroundTerm::GroundTerm(void):processed(false)
{
}

GroundTerm::GroundTerm(string s): name(s), processed(false)
{
}

GroundTerm::~GroundTerm(void)
{
}

void GroundTerm::AddLiteral(GroundLiteral* gl)
{
	gndLiteral.push_back(gl);
}

size_t GroundTerm::GetSize()
{
	return gndLiteral.size();
}

GroundLiteral* GroundTerm::GetLiteral(size_t idx)
{
	if(idx>=0 && idx<=gndLiteral.size()) return gndLiteral[idx];
	else NULL;
}

void GroundTerm::CollectTerm(std::set<GroundTerm*>& stk, std::set<GroundTerm*>& checked)
{
	//size_t sz=tmp->GetSize();
	vector<GroundLiteral*>::iterator itr;
	itr=gndLiteral.begin();
	while(itr!=gndLiteral.end()){
		(*itr)->CollectTerm(stk, checked);
		++itr;
	}
	vector<RandomRule*>::iterator itr_rnd;
	itr_rnd=rndRule.begin();
	while(itr_rnd!=rndRule.end())
	{
		(*itr_rnd)->CollectTerm(stk, checked);
		++itr_rnd;
	}
}

void GroundTerm::CollectRandomRule(std::set<std::string>& rndRuleName)
{
    vector<RandomRule*>::iterator itr_rnd;
	itr_rnd=rndRule.begin();
	while(itr_rnd!=rndRule.end())
	{
		rndRuleName.insert((*itr_rnd)->GetRuleName());
		++itr_rnd;
	}
}

void GroundTerm::AddRandomRule(RandomRule* nr)
{
	size_t sz=rndRule.size();
	for(size_t idx=0; idx<sz; idx++){
		if(rndRule[idx]==nr) return;
	}
	rndRule.push_back(nr);
}




