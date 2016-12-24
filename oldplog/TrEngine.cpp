#include "TrEngine.h"
#include "AnswerSet.h"
#include "global.h"
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <utility>
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

TrEngine::TrEngine(void)
{
}

TrEngine::TrEngine(Program *p, Query *q, std::string inf):prg(p), qry(q), solver(inf)
{
	output="";
}


TrEngine::~TrEngine(void)
{
}

bool TrEngine::Solve()
{
	clock_t start=clock();
	Translate();
	ofstream fileOut("out.txt");
	if(fileOut){
		fileOut<<output;
	}
	fileOut.close();
	//Call lparse and smodels
	string command("lparse --true-negation -W none out.txt|smodels 0 >result.txt");
	system(command.c_str());
	list<AnswerSet*> answersets;
	list<AnswerSet*>::iterator itr;
	//
	ifstream fileIn("result.txt");
	string line, word;
	double totalProb=0.0;
	clock_t end=clock();
	//cout<<"Answer Sets computed and its duration:"<<((double)end-(double)start)/CLOCKS_PER_SEC<<endl;
	start=clock();
	if(fileIn){
		double prob=0.0;
		while(getline(fileIn, line))
		{
			if(line.substr(0,12)=="Stable Model"){
				AnswerSet *ans=new AnswerSet(line.substr(12));
				answersets.push_back(ans);
				if(qry->GetType()==3) ans->AddBasicFormula(qry); 
				if(qry->GetType()==2) ans->CollectFormula(qry); 
				//cout<<ans->GetProbability()<<endl;
				totalProb+=ans->GetProbability();
			}
            else if(line.substr(0, 9)=="Duration:"){
                cout<<"Smodels computation time: "<<line.substr(9, line.size()-9)<<endl;
            }
           
		}
	}
	//cout<<totalProb<<endl;  //To deleted for release
	fileIn.close();
	itr=answersets.begin();
	while(itr!=answersets.end()){
		(*itr)->SetProbability((*itr)->GetProbability()/totalProb);
		(*itr)->EvaluateQuery(qry);
		++itr;
	}
	qry->GetMaximunFormula();
	qry->ShowAnswer();
	end=clock();
	cout<<"Probability Computing Time:"<<((double)end-(double)start)/CLOCKS_PER_SEC<<endl;
	return true;
}



bool TrEngine::Translate()
{
	if(prg==NULL) return false;
	// Sort:
	set<Sort*>::iterator itr_sort;
	itr_sort=prg->sort.begin();
	while(itr_sort!=prg->sort.end()){
		string sortName=(*itr_sort)->GetObject();
		if((*itr_sort)->GetSortType()==list_based)
		{
			size_t size=(*itr_sort)->GetDomainSize();
			for(size_t i=0;i<size;i++){
				output+=sortName+"("+(*itr_sort)->GetDomainElement(i)+").\n";
			}
		}
		else{
			stringstream sl, sh;
			sl<<(*itr_sort)->GetLow();
			sh<<(*itr_sort)->GetHight();	
			string str_l, str_h;
			sl>>str_l;
			sh>>str_h;
			output+=sortName+"("+str_l+".."
				+str_h+").\n";
		}
		++itr_sort;
	}
	//Variable Declaration
	set<Variable*>::iterator itr_var;
	itr_var=prg->variable.begin();
	while(itr_var!=prg->variable.end()){
		output+="#domain "+(*itr_var)->GetSort()
			+"("+(*itr_var)->GetName()+").\n";
		++itr_var;
	}

	//RULES //At here Feb 28
	list<Rule*>::iterator itr_rule;
	itr_rule=prg->rule.begin();
	while(itr_rule!=prg->rule.end()){
		string rules="";
		if((*itr_rule)->GetType()==reg){//Regular rules
			Literal *l=(*itr_rule)->GetHead();
			if(l!=NULL){//Constrain rule, rule with empty head
				rules=l->ToString();
			}
			if((*itr_rule)->GetBodySize()==0){
				rules+=".\n";
			}
			else{//
				rules+=":-"+(*itr_rule)->BodyToString()+".\n";
			}
			output+=rules;
		}
		else if((*itr_rule)->GetType()==cr){
			rules=(*itr_rule)->GetRuleName();
			Literal *l=(*itr_rule)->GetHead();
			rules+=" "+l->ToString();
			if((*itr_rule)->GetBodySize()==0){
				rules+="+-.\n";
			}
			else{//
				rules+="+-"+(*itr_rule)->BodyToString()+".\n";
			}
			output+=rules;
		}
		else if((*itr_rule)->GetType()==rnd_){
			Literal *a=(*itr_rule)->GetHead();
			string s=prg->GetAttributeRange(GetRoot(a->GetTerm()));
			string atomName=a->ToString();
			string ruleBody="";
			string sortRange="";
			if(a->GetValue()=="X_"){//random (a(t)).
				//atomName[atomName.length()-1]=',';
				//atomName+="X_)";
				//atomName.replace(
				sortRange=s+"(X_)";
				rules="1{"+atomName+":"+sortRange+"}1";
			}
			else{
				sortRange=s+"("+a->GetValue()+")";
				rules="1{"+atomName+":"+sortRange+"}1";
			}
			if((*itr_rule)->GetBodySize()==0){
				ruleBody="not intervene("+a->GetTerm()+")";
			}
			else{
				ruleBody="not intervene("+a->GetTerm()+"),"+(*itr_rule)->BodyToString();
			}
			rules+=":-"+ruleBody+".\n";
			output+=rules;
			//pd rules: for default probabiltiy 
			if((*itr_rule)->GetRange()==NULL){
				rules="pd("+(*itr_rule)->GetRuleName()+","+atomName+")";
				rules+=":-"+ruleBody+","+sortRange+".\n";
				output+=rules;
			}
			else
			//Constraints for dynamic range random selection rule
			{
				
				Literal *range=(*itr_rule)->GetRange();
				rules="pd("+(*itr_rule)->GetRuleName()+","+atomName+")";
				rules+=":-"+ruleBody+","+sortRange+","+range->ToString()+".\n";
				output+=rules;				
				rules=":-"+ruleBody+","+atomName+",not "+range->ToString()+","+sortRange+".\n";
				output+=rules;
			}
			output+="show "+atomName+".\n";
		}
		else if((*itr_rule)->GetType()==pr){
			rules="pa("+(*itr_rule)->GetRuleName()+","
				+(*itr_rule)->GetHead()->ToString()+","
				+ReNameTerm((*itr_rule)->GetProbability())+")";
			if((*itr_rule)->GetBodySize()==0){
				rules+=".\n";
			}
			else{
				rules+=":-"+(*itr_rule)->BodyToString()+".\n";
			}
			output+=rules;
		}
		++itr_rule;
	}
	//QUERY 
	string atomName;
	string litName;
	string doStatement;
	list<Literal*>::iterator itr_lit;
	itr_lit=qry->condition.begin();
	//cout<<"debuging codition size ";
	//cout<<qry->condition.size()<<endl;
	while(itr_lit!=qry->condition.end()){
		litName=(*itr_lit)->ToString();
		//atomName=(*itr_lit)->ToString();
		//cout<<litName<<" "<<atomName<<endl;
		if((*itr_lit)->GetType()==dos){
			//doStatement=atomName+":-"+litName+".\n";
			doStatement+=litName+".\n";
			output+=doStatement;
            
            output+="intervene("+(*itr_lit)->GetTerm()+").\n"; 

		}
		else if((*itr_lit)->GetType()==obs){
			output+=":- not "+litName+".\n";
			/*
			if((*itr_lit)->GetSign()==true){
				output+=":- not "+atomName+".\n";
			}
			else{
				output+=":- not -"+atomName+".\n";  
			}*/
		}
		++itr_lit;
	}
	//HIDE and Show Statements
	output+="\nhide.\n";
	output+="show pd(X,Y).\n";
	output+="show pa(X,Y,Z).\n";
	list<Literal*>::iterator itr_atm;
	itr_atm=qry->atoms.begin();
	while(itr_atm!=qry->atoms.end()){
		output+="show "+(*itr_atm)->ToString()+".\n";
		++itr_atm;
	}
	return true;
}
std::string TrEngine::GetOutput()
{
	return output;
}

string TrEngine::ReNameTerm(string exp)
{
	string out=exp;
	size_t pos=0;
	while(pos<=exp.length() && (pos=exp.find('(',pos))!=string::npos){
		out[pos-1]='_';
		++pos;
	}
	return out;
}

std::string TrEngine::GetPart(std::string in, int i)
{
	int pcount=0;
	int comaCount=0;
	int ilength=in.length();
	int j;
	if(i==0) return in.substr(0,in.find('('));
	j=in.find("(");
	int prePosition=j+1;
	for(++j;j<ilength;j++){
		if(in[j]=='(') pcount++;
		else if(in[j]==')') pcount--;
		if((in[j]==',' && pcount==0) || pcount<0){
			comaCount++;
			if(comaCount==i-1){
				prePosition=j+1;
			}
			else if(comaCount==i){
				return in.substr(prePosition, j-prePosition);
			}
		}
	}
	return "";
}
