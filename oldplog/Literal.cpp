#include "Literal.h"
#include "global.h"
#include <stack>
#include <iostream>
using namespace std;


Literal::Literal(void):sign(true),naf(true),type(regl),id(-1)
{
    
}



Literal::Literal(string tm, string vl):term(tm), value(vl),sign(true),naf(true),type(regl),id(-1)
{
    GetName();
}

Literal::Literal(Literal *l):term(l->GetTerm()), value(l->GetValue()),
                sign(l->GetSign()), type(l->GetType()),naf(l->GetNaf()),id(-1)
{
    GetName();
}

Literal::Literal(Literal *l, map<string, string> val):sign(l->GetSign()), type(l->GetType()), naf(l->GetNaf()), id(-1)
{
    string s=Replace(l->GetTerm(), val);
    term=Evaluate(s);
    s=Replace(l->GetValue(),val);
    value=Evaluate(s);
    GetName();
}

Literal::Literal(std::string s, map<string, string> val):sign(true), type(regl), naf(true), id(-1)
{
    string s1=Replace(s, val);
    term=Evaluate(s1);
    //s=Replace(l->GetValue(),val);
    value="true";
   
}

Literal::~Literal(void)
{
}

std::string Literal::GetName()
{
   
    name=term;
    if(value!="") name=name+"="+value;
	//if(sign==false) name="-"+name;
    return name;
}

std::string Literal::ToString()
{
	string s(term);
    if(type==predefined) return term;
	if(s.length()==0) return "";
	if(s[s.length()-1]==')'){//term has the form of a(t)
		if(value!=""){
			s[s.length()-1]=',';
			s+=value+")";
		}
	}
	else{
		if(value!="")	s+="("+value+")";
	}
	return s;
}

//Add variable v to set addin
void Literal::CollectVariable(std::set<std::string>& addin)
{
	string element;
    //cout<<name<<endl;
    list<string> lstElement=NextElement(name);
    list<string>::iterator itr_lst=lstElement.begin();
    while(itr_lst!=lstElement.end()){
        if(GetTermType(*itr_lst)==var) addin.insert(*itr_lst);
        ++itr_lst;
    }	
}

void Literal::CollectHeadVariable(std::set<std::string>& addin)
{
    vector<string> sol;
    int i=0;
    list<string> lstElement=NextElement(term);
    list<string>::iterator itr_lst=lstElement.begin();
    while(itr_lst!=lstElement.end()){
        if(GetTermType(*itr_lst)==var) addin.insert(*itr_lst);
        ++itr_lst;
    }	
}

/*
bool Literal::GetSolution(map<string, string>& assignment, set<string>& pos, set<string>& neg, bool flag)
{
	//Reset();//Reset the free variables
	map<string,string> V;
	map<string,string>::iterator itr;

	if(!solution.empty()){
		solution.erase(++solution.begin(), solution.end());
	}
	itr=assignment.begin();
	while(itr!=assignment.end()){
		V[itr->first]=itr->second;
		//cout<<itr->first<<" "<<itr->second<<" ";
		++itr;
	}
	//cout<<"Before init"<<endl;
	bool init=true;
	do{
		if(NextValue(V,init)){
			init=false;
			if(Test(pos, neg, flag,V))
			{
				AddSolution(V);
			}
		}
		else break; //Out of the loop
	}while(true);
	//cout<<"solu "<<solution.size()<<endl;
	if(solution.size()==1) return false;
	else return true;
}

void Literal::Reset()
{
	//cout<<"RESET"<<endl;
	list<Variable*>::iterator itr;
	itr=variable.begin();
	while(itr!=variable.end()){
		//(*itr)->Show();
		(*itr)->Reset(false);
		++itr;
	}
	//cout<<"RESET END"<<endl;
}

bool Literal::NextValue(map<string,string>& value, bool init)
{
	std::list<Variable*>::iterator itr;
	if(init==true){
		Reset();
		
		//cout<<variable.size()<<endl;
		itr=variable.begin();
		while(itr!=variable.end()){
			value[(*itr)->GetName()]=(*itr)->GetValue();
			//cout<<(*itr)->GetName()<<" "<<(*itr)->GetValue()<<endl;
			++itr;
		}
		return true;
	}
	bool flag=false;
	itr=variable.begin();
	do{
		if((*itr)->NextValue()){
			flag=true;
		}
		value[(*itr)->GetName()]=(*itr)->GetValue();
	    //cout<<(*itr)->GetName()<<" "<<(*itr)->GetValue()<<endl;
		++itr;
	}while(itr!=variable.end() && flag==false);
	return flag;
}

//Evaluate the constraint
bool Literal::Test(set<string>& pos, set<string>& neg, bool flag, map<string,string>& value)
{
    
    Literal *atm=new Literal(this,value);    
    if(type==regl) return atm->CheckValue(pos,neg,flag);
	else if(type==predefined){
	    //cout<<"TEST "<<s<<endl;
		if(atm->GetTerm()=="true") return true;
		else return false;
	}
	else return true;
    
    return true;
}

void Literal::AddSolution(map<string, string>& V)
{
	vector<string> newSol;
	solution.begin();
	vector<string>::iterator itr;
	itr=solution.begin()->begin();
	while(itr!=solution.begin()->end()){
		newSol.push_back(V[*itr]);
		++itr;
	}
	solution.push_back(newSol);
}

vector< vector<string> >& Literal::GetSolution()
{
	return solution;
}

bool Literal::CheckValue(set<string>& positiveAtom, 
	set<string>& negtiveAtom, bool fFact)
{
	string s=GetName();
	if(s=="true") return true;
	if(s=="false") return false;
	
	bool saf=sign;
	if(fFact){
		if(naf){
			//cout<<"pos "<<s<<endl;
			if(positiveAtom.find(s)!=positiveAtom.end()){ return true;}
			else {return false;}
			
		}
		else{
			//cout<<"neg "<<s<<endl;
			if(positiveAtom.find(s)!=positiveAtom.end()) {return false;}
			else {return true;}
		}
	}
	else{
		if(naf){
			if(negtiveAtom.find(s)!=negtiveAtom.end()) return false;
			else return true;
		}
		else{
			if(positiveAtom.find(s)!=positiveAtom.end()) return false;
			else return true;
		}
	}
}*/

bool Literal::IsGround()
{
    //set<string> vars;
    //CollectVariable(vars);
    //if(vars.empty()) return true;
    //else return false;
	
    if(variable.empty()) return true;
	else return false;
}


void Literal::SetVariable(std::set<std::string>& fixed)
{
    
    set<string> all;
    CollectVariable(all);
    //cout<<"setvariable "<<name<<" "<<all.size()<<endl;    
    variable.clear();
    SubstractSet(all, fixed, variable);
  
}
/*
//Replace a subtree at position i by another string s, return the string that has been replaced
int Literal::SubTree(int i, std::string target)
{
   
    //if(flag==true) target=term;
    //else target=value;    
    int pos=i;
    int lev=0;
    do{
        if(target[pos]=='(') lev++;
        else if(target[pos]==',' && lev==0) break; //pos=last_replacing_character+1
        else if(target[pos]==')' && lev==0) break;
        else if(target[pos]==')' && lev>0) lev--;
        pos++;
    }while(pos<target.size());
    return pos+1;
}   
*/
