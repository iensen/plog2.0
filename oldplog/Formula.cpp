#include "Formula.h"
#include <iostream>

//const int TRUE=5;
//const int UNKNOWN=3;
//const int FALSE=1;

using namespace std;

Formula::Formula(void):min(0.0), max(1.0), prob(0.0), atom(NULL), formula_1(NULL), formula_2(NULL), valid(true)
{
}

Formula::Formula(std::string op, Formula *f1, Formula *f2):operation(op),formula_1(f1), formula_2(f2)
{
	min=0.0;
	max=1.0;
	prob=0.0;
	atom=NULL;
    valid=true;
}

Formula::Formula(set<Literal*> atms):min(0.0), max(1.0)
{
	set<Literal*>::iterator itr;
	itr=atms.begin();
	while(itr!=atms.end()){
		aset.insert(*itr);
		++itr;
	}

	formula_1=NULL;
	formula_2=NULL;
	operation="";
	atom=NULL;
	prob=0.0;
    valid=true;
}


Formula::Formula(Literal* a):atom(a),min(0.0), max(1.0)
{
	//aset.insert(a);
	operation="";
	formula_1=NULL;
	formula_2=NULL;
	prob=0.0;
    valid=true;
}


Formula::~Formula(void)
{
}

double Formula::GetProbability()
{
	return prob;
}

void Formula::AddProbability(double pb)
{
	prob+=pb;
}

set<Literal*>& Formula::GetASet()
{
	return aset;
}


int Formula::IsSubset(Formula *f)
{
	int longer;

	set<Literal*>& aset_2=f->GetASet();
    set<string> s1, s2;
    set<Literal*>::iterator itr1, itr2;
    set<string>::iterator itr_s1, itr_s2;
    itr1=aset.begin();
    while(itr1!=aset.end()){
        s1.insert((*itr1)->GetName());
        ++itr1;
    }
    itr1=aset_2.begin();
    while(itr1!=aset_2.end()){
        s2.insert((*itr1)->GetName());
        ++itr1;
    }
    int i=aset.size();
	int j=aset_2.size();
    
    itr_s1=s1.begin();
    itr_s2=s2.begin();
    if(i<j){
        while(itr_s1!=s1.end() && itr_s2!=s2.end()){
            if((*itr_s1)!=(*itr_s2)) ++itr_s2;
            else{
                ++itr_s1;
                ++itr_s2;
            }
        }
        if(itr_s1==s1.end()) return -1;
        else return 0;
    }
    else{
        while(itr_s1!=s1.end() && itr_s2!=s2.end()){
            if((*itr_s1)!=(*itr_s2)) ++itr_s1;
            else{
                ++itr_s1;
                ++itr_s2;
            }
        }
        if(itr_s2==s2.end()) return 1;
        else return 0;
    }
}


std::string Formula::GetName()
{
	if(operation==""){
        if(aset.empty()) return atom->GetName();
		string s;
		set<Literal*>::iterator itr=aset.begin();
		while(itr!=aset.end()){
			s=s+(*itr)->GetName()+" ";
			++itr;
		}
		return s;
	}
	else if(operation=="!"){
		if(formula_1!=NULL) return "! "+formula_1->GetName();
		else return "";
	}
	else{
		if(formula_1!=NULL && formula_2!=NULL){
			return "( "+formula_1->GetName()+" "+operation+" "+formula_2->GetName()+" )";
		}
		else return "";
	}
}

void Formula::CollectAtom(std::set<string>& atomSet)
{
	if(atom!=NULL) atomSet.insert(atom->GetName());
	else{
		if(formula_1!=NULL) formula_1->CollectAtom(atomSet);
		if(formula_2!=NULL) formula_2->CollectAtom(atomSet);
	}
}

void Formula::CollectLiteral(set<Literal*>& litSet)
{
    if(atom!=NULL) litSet.insert(atom);
    else{
        if(formula_1!=NULL) formula_1->CollectLiteral(litSet);
        if(formula_2!=NULL) formula_2->CollectLiteral(litSet);
    }
    if(!aset.empty()){
        set<Literal*>::iterator itr_lit;
        itr_lit=aset.begin();
        while(itr_lit!=aset.end()){
            litSet.insert(*itr_lit);
            ++itr_lit;
        }
    }
}

void Formula::UpdateProbability(double l, bool f)
{
	if(f==true) min+=l;
	else max=max-l;
}


bool Formula::IsEqual(Formula* f)
{
	set<Literal*>::iterator itr_atm;
	itr_atm=aset.begin();
	while(itr_atm!=aset.end()){
		if(f->GetASet().find(*itr_atm)==f->GetASet().end()) return false;
		++itr_atm;
	}
	return true;
}

void Formula::Show()
{
	set<Literal*>::iterator itr;
	if(atom!=NULL){
		cout<<atom->GetName()<<" ";
	}
	else if(operation==""){
		itr=aset.begin();
		while(itr!=aset.end()){
			cout<<(*itr)->GetName()<<",";
			++itr;
		}
	}
	else{
		cout<<"(";
		formula_1->Show();
		cout<<" "<<operation<<" ";
		formula_2->Show();
		cout<<")";
	}
	cout<<min<<" "<<max<<endl;
}

