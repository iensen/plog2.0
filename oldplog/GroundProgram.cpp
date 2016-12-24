#include "GroundProgram.h"
#include <iostream>

using namespace std;

GroundProgram::GroundProgram(void)
{
    hline = 0;
}

GroundProgram::~GroundProgram(void)
{
}

void GroundProgram::DrawLine(void)
{
    hline=regRule.size();
}

void GroundProgram::AddRule(GroundRule *gr)
{
	//Add the rules in
	regRule.push_back(gr);
	//Set the link between the literals and the rule
	gr->GetHead()->AddHeadRule(gr);
	size_t idx, sz;
	sz=gr->GetBodySize(true);
	for(idx=0;idx<sz;idx++){
		gr->GetBodyLit(idx,true)->AddPosRule(gr);
	}
	sz=gr->GetBodySize(false);
	for(idx=0;idx<sz;idx++){
		gr->GetBodyLit(idx,false)->AddNegRule(gr);
	}
	//gr->SetLink();
}

void GroundProgram::Show()
{
	/*
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
	*/
	cout<<"Regular RULE"<<endl;
	list<GroundRule*>::iterator itr_rule;
	itr_rule=regRule.begin();
	while(itr_rule!=regRule.end()){
		(*itr_rule)->Show();
		++itr_rule;
	}
	cout<<endl;

	cout<<"Random Rule"<<endl;
	map<string, RandomRule*>::iterator itr_rnd;
	itr_rnd=rndRule.begin();
	while(itr_rnd!=rndRule.end()){
		cout<<"Name "<<itr_rnd->first<<endl;
		itr_rnd->second->Show();
		++itr_rnd;
	}

	map<string, GroundTerm*>::iterator itr;
	itr=gndTerm.begin();
	while(itr!=gndTerm.end()){
		cout<<(*itr).first<<endl;
		++itr;
	}
}

GroundTerm* GroundProgram::GetTerm(std::string s)
{
	map<string, GroundTerm*>::iterator itr_tm=gndTerm.find(s);
	if(itr_tm!=gndTerm.end()){
		//if(itr_tm->second->GetProcessed()==true) return NULL; //processed term with no such literal
		return itr_tm->second;
	}
	else{//Not found, create a new one
		GroundTerm *nt=new GroundTerm(s);
		gndTerm[s]=nt;
		return nt;
	}
}


GroundLiteral* GroundProgram::GetLiteral(Literal *l)
{
	string name=l->GetName();
    //cout<<name<<" ";
	map<string, GroundLiteral*>::iterator itr_gl=gndLiteral.find(name);
	//TermTree *tm;
	//The literal is already in
	if(itr_gl!=gndLiteral.end()) return itr_gl->second;
	else{//Not found
		GroundLiteral *gl=new GroundLiteral(l->GetTerm(), l->GetValue(), l->GetSign());
		gndLiteral[name]=gl;
		map<string, GroundTerm*>::iterator itr_tm=gndTerm.find(l->GetTerm());
		if(itr_tm!=gndTerm.end()){
			if(itr_tm->second->GetProcessed()==true) return NULL; //processed term with no such literal
			itr_tm->second->AddLiteral(gl);
			gl->SetTerm(itr_tm->second);
		}
		else{//Not found, create a new one
			GroundTerm *nt=new GroundTerm(l->GetTerm());
			gndTerm[l->GetTerm()]=nt;
			gl->SetTerm(nt);
			nt->AddLiteral(gl);
		}
		return gl;
	}
	
}

void GroundProgram::BuildVectors()
{
	size_t idx=0;
	list<GroundRule*>::iterator itr_lst;
	//Build the vector for ground rules
	itr_lst=regRule.begin();
	while(itr_lst!=regRule.end()){
		(*itr_lst)->SetId(idx);
		gRule.push_back(*itr_lst);
		++idx;
		++itr_lst;
	}
	//Buid the vector for ground literals
	idx=0;
	map<string, GroundLiteral*>::iterator itr_map;
	itr_map=gndLiteral.begin();
	while(itr_map!=gndLiteral.end())
	{
		itr_map->second->SetId(idx);
		gLit.push_back(itr_map->second);
		++idx;
		++itr_map;
	}
}

RandomRule* GroundProgram::GetRandomRule(std::string name)
{
	if(rndRule.find(name)!=rndRule.end()) return rndRule[name];
	else{
		RandomRule *nr=new RandomRule(name);
		rndRule[name]=nr;
		return nr;
	}
}

bool GroundProgram::CheckPosBody(size_t id)
{
	GroundRule* gr=gRule[id];
	GroundLiteral* gl;
	size_t idx;
	size_t posSize=gr->GetBodySize(true);
	for(idx=0;idx<posSize;idx++){
		gl=gr->GetBodyLit(idx,true);
		if(gl->GetRndLit()==false) return false;
	}
	return true;
}

/*
bool GroundProgram::CheckRndLit(GroundLiteral* gl)
{
	size_t idx;
	size_t sz;
	map<string, RandomRule*>::iterator itr_map;
	itr_map=rndRule.begin();
	while(itr_map!=rndRule.end()){
		size_t sz=itr_map->second->GetHeadSize();
		for(idx=0;idx<sz;idx++){
			GroundLiteral* ghead=itr_map->second->GetHeadLiteral(idx);
			if(ghead==gl) return true;
		}
		++itr_map;
	}
	return false;
}
*/

void GroundProgram::BuildUpperBound()
{
        int id;
	//set<int> lid;
	size_t idx;
	size_t sz;
	//stack<int> stk_id;
	//Show(true,true,true);
	//cout<<endl;
	//clock_t start=clock();
	//cout<<endl;
	map<string, RandomRule*>::iterator itr_map;
	vector<GroundLiteral*>::iterator itr_lits;
	itr_map=rndRule.begin();
	while(itr_map!=rndRule.end()){
		RandomRule* rnds=itr_map->second;
		sz=rnds->GetHeadSize();
		for(idx=0;idx<sz;idx++){
			GroundLiteral* l=rnds->GetHeadLiteral(idx);
			l->SetRndLit(true);
		}
		++itr_map;
	}
	sz=gRule.size();
	for(idx=0;idx<sz;idx++){
		if(CheckPosBody(idx)) gRule[idx]->SetSpt(true);
		else gRule[idx]->SetSpt(false);
	}
}



