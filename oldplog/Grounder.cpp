#include "Grounder.h"
#include "global.h"
#include <list>
#include <stack>
#include <iostream>

using namespace std;

Grounder::Grounder(void)
{
}

Grounder::Grounder(GroundProgram *gp, Program *p, Query *q):gndProgram(gp), prg(p), qry(q)
{

}

Grounder::~Grounder(void)
{
}

bool Grounder::Preprocessing()//Replace arithmetic expression and collect free variables
{
	list<Rule*>::iterator itr_r;
	set<string> defined;
	//prg->Show();
	//Collect variables of the program
	//Initialize the variable "variables"
	set<Variable*>::iterator itr_var;
	itr_var=prg->variable.begin();
	while(itr_var!=prg->variable.end()){
		variables[(*itr_var)->GetName()]=(*itr_var);
		++itr_var;
	}
	//Link variables to their sort
	VariableToSort();
    
    //Grounding Sort (if necessary)
    GroundSort();
    
    //Grounding Query(if necessary)
    GroundQuery();
    

	//prg->Show();
	itr_r=prg->rule.begin();
	Literal* head;
	while(itr_r!=prg->rule.end()){
		(*itr_r)->Normalize(); //Replace expressions with new variable
		//(*itr_r)->CollectVariable(variables); //Set Free variables in the body
		//Record fact atoms
		head=(*itr_r)->GetHead(); 
        string fid=GetRoot(head->GetTerm());
		if((*itr_r)->GetBodySize()==0 && (*itr_r)->GetType()==reg
			&& (*itr_r)->IsGround()==true){//
			facts.insert(fid);
	    	positiveAtom.insert(head->GetName());
            if(debug_level==309) cout<<" "<<head->GetName();
			
		}
		else{
			 defined.insert(fid);
		}
        ++itr_r;
	}
	//Collect fact Ids
	set<string>::iterator itr;
	itr=facts.begin();
	while(itr!=facts.end()){
		if(defined.find(*itr)!=defined.end()) facts.erase(itr);
        //else cout<<*itr<<" . ";
		++itr;
	}
    
    //Set facts of literals and collect variables
    itr_r=prg->rule.begin();
    while(itr_r!=prg->rule.end()){
        (*itr_r)->CheckFact(facts);
        (*itr_r)->CollectVariable();
        ++itr_r;
    }
    if(debug_level==309) cout<<endl;
    if(debug_level==309) prg->Show();
	return true;
}

void Grounder::VariableToSort()
{
	set<Variable*>::iterator itrv;
	set<Sort*>::iterator itr;
	//Set sort for all variables and domain size for all variables
	itrv=prg->variable.begin();
	while(itrv!=prg->variable.end()){
		itr=prg->sort.begin();
		while(itr!=prg->sort.end()){
			if((*itrv)->GetSort()==(*itr)->GetObject()){
				(*itrv)->SetSort(*itr);
				(*itrv)->SortSize((*itr)->GetDomainSize());
				break;
			}
			++itr;
		}
		++itrv;
	}
}

void Grounder::GroundSort()
{
    set<Sort*>::iterator itr_sort;
    list<Literal*>::iterator itr_l;
    itr_sort=prg->sort.begin();
    Literal *l;
    while(itr_sort!=prg->sort.end()){
        if((*itr_sort)->GetSortType()==range_based){
            ++itr_sort;
            continue;
        }
        size_t idx=0;
        string obj;
        size_t sz=(*itr_sort)->GetDomainSize();
        list<Literal*> lstObj, lstTemp;
        for(idx=0;idx<sz;idx++){
            obj=(*itr_sort)->GetDomainElement(idx);
            l=new Literal(obj,"");
            lstObj.push_back(l);
        }
        (*itr_sort)->ClearDomain();
        itr_l=lstObj.begin();
        while(itr_l!=lstObj.end()){
            lstTemp=Ground(*itr_l);
            list<Literal*>::iterator itr_l2;
            itr_l2=lstTemp.begin();
            while(itr_l2!=lstTemp.end()){
                (*itr_sort)->Add((*itr_l2)->GetTerm());
                ++itr_l2;
            }
            ++itr_l;
        }
        ++itr_sort; 
    }
    //cout<<"end"<<endl;	
}

void Grounder::GroundQuery()
{
	size_t idx=0;
    string obj;
    size_t sz=qry->terms.size();
    list<Literal*> lstObj, lstTemp;
    list<Literal*>::iterator itr_l;
     Literal *l;
    if(debug_level==302 ) cout<<"start"<<endl;
    if(qry->GetType()==2){
        list<string>::iterator itr_s;
        itr_s=qry->terms.begin();
        while(itr_s!=qry->terms.end()){
            l=new Literal(*itr_s,"");
            lstObj.push_back(l);
            ++itr_s;
        }
        qry->terms.clear();
    }
    else if(qry->GetType()==3){
        itr_l=qry->atoms.begin();
        while(itr_l!=qry->atoms.end()){
            lstObj.push_back(*itr_l);
            ++itr_l;
        }
        qry->atoms.clear();
    }
    if(debug_level==302) cout<<"here"<<endl;
    while(!lstObj.empty()){
        l=lstObj.front();
        lstObj.pop_front();
        lstTemp.clear();
        if(debug_level==302) cout<<"Before calling ground(l)"<<endl;
        lstTemp=Ground(l);
        if(debug_level==302) cout<<"After calling ground(l)"<<endl;
        itr_l=lstTemp.begin();
        while(itr_l!=lstTemp.end()){
            if(qry->GetType()==2)  qry->terms.push_back((*itr_l)->GetTerm());
            else if(qry->GetType()==3){
                if(debug_level==302) cout<<(*itr_l)->GetName()<<" ";
                qry->atoms.push_back(*itr_l);
            }
            ++itr_l;
        }
    }
    if(debug_level==302) qry->Show();
}

list<Literal*> Grounder::Ground(Literal* atm)
{
	set<string> vset;
	vector< vector<string> > sol;
	set<Variable*>::iterator itr_var;	
	list<Literal*> lstAtom;
    list<Literal*> lstOut;
	if(debug_level==301) cout<<atm->GetName()<<endl;
    lstAtom.push_back(atm);
    while(!lstAtom.empty()){
        Literal* l=lstAtom.front();
        lstAtom.pop_front();
        vset.clear();
        l->CollectVariable(vset);
        if(vset.empty()){
            lstOut.push_back(l);
            continue;
        }
        else{
	       //Atom* a=new Atom(tm, NULL);
            //cout<<l->GetName()<<endl;
            list<Variable*> varlst;
            set<string>::iterator itr_v=vset.begin();
            while(itr_v!=vset.end()){
                Variable* var=variables[*itr_v];
                varlst.push_back(var);
                ++itr_v;
            }
            ResetVariable(varlst);
            if(debug_level==301) cout<<"reset variable"<<endl;
            while(NextAssignment(varlst)){
                Literal* a=new Literal(atm, assignment);
	            lstAtom.push_back(a);
            }
        }
    }
    return lstOut;
}

bool Grounder::NextAssignment(list<Variable*>& varlst)
{
        
    list<Variable*>::iterator itr_v=varlst.begin();
    bool flag=false;
    do{
		if((*itr_v)->NextValue()) flag=true;
		assignment[(*itr_v)->GetName()]=(*itr_v)->GetValue();
	    //cout<<(*itr_v)->GetName()<<" "<<(*itr_v)->GetValue()<<endl;
		++itr_v;
	}while(itr_v!=varlst.end() && flag==false);
	return flag;
}

bool Grounder::NextAssignment(vector< vector<string> >& sol, int i)
{
    if(i<0 || i>sol.size()-1) return false;
    else{
        vector<string>::iterator itr_vct, itr_vc0;
        itr_vct=sol[i].begin();
        itr_vc0=sol[0].begin();
        while(itr_vct!=sol[i].end()){
            assignment[*itr_vc0]=(*itr_vct);
            ++itr_vct;
            ++itr_vc0;
        }
    }
    return true;
}

//--------------------------------------------------------------------------------------


void Grounder::Ground(string s)
{
	GroundTerm *tmp, *lTerm;  //tempory variable for tmp
	list<Rule*>::iterator itr_rule;
	if(debug_level==303) cout<<"In Function Ground "<<s<<endl;
    lTerm=gndProgram->GetTerm(s);
	do
	{
		tmp=ResetTerms(lTerm);  //Compute the next set of terms
		if(tmp==NULL) break;
		if(debug_level==303) cout<<"Ground A:"<<tmp->GetName()<<endl;
		//int i;
		//cin>>i;
		//For every rule if its head is matched to the rule
		//Get all the ground instances of the rule
		itr_rule=prg->rule.begin();
		while(itr_rule!=prg->rule.end()){
			assignment.clear();
			//if(debug_level==303){
            //    cout<<"In Function Ground, Check Point A"<<endl;
            //    (*itr_rule)->Show();
            //}
			//TermTree* t=(*itr_rule)->GetHead()->GetTerm();
            //cout<<"check point 3"<<endl;
            //
			if(CheckTerm((*itr_rule)->GetHead()->GetTerm(), tmp->GetName())){
				//(*itr_rule)->Show();
				if(debug_level==303){
                    cout<<"In Function Ground, Check Point B:";
                    (*itr_rule)->Show();
                    cout<<endl;
                }
				GetGroundRule(*itr_rule);
                if(debug_level==303) cout<<"In Function Ground, Check Point D"<<endl;
			}
			++itr_rule;
		}
		//Compute the consequences of the program
		if(debug_level==303) cout<<"In Function Ground, Check Point C"<<endl;
		Evaluate(tmp);
		if(debug_level==303) cout<<"In Function Ground, Check Point E"<<endl;
		//finished.insert(tmp); //Add processed the term tmp into finished
		tmp->SetProcessed(true);
	}while(true);
}

void Grounder::DependantSet(GroundTerm *t, set<GroundTerm*>& dependantSet)
{
    GroundTerm* tmp;
	set<GroundTerm*> stk;
	set<GroundTerm*>::iterator itr;
	//set<GroundTerm*> checked;
	stk.insert(t);
	while(!stk.empty()){
		tmp=*stk.begin();
		//if(debug_level==307) cout<<"ResetTerms A:"<<tmp->GetName()<<endl;
		//if(tmp->GetProcessed()==true){
		tmp->CollectTerm(stk, dependantSet);  //Expand stk
       		//if(debug_level==307) cout<<"ResetTerms B:"<<stk.size()<<" "<<checked.size()<<endl;
		dependantSet.insert(tmp);
		stk.erase(tmp);
	}
}

GroundTerm* Grounder::ResetTerms(GroundTerm *t)
{
	GroundTerm* tmp;
	set<GroundTerm*> stk;
	set<GroundTerm*>::iterator itr;
	set<GroundTerm*> checked;
	stk.insert(t);
	while(!stk.empty()){
		tmp=*stk.begin();
		if(debug_level==307) cout<<"ResetTerms A:"<<tmp->GetName()<<endl;
		if(tmp->GetProcessed()==true){
			tmp->CollectTerm(stk, checked);  //Expand stk
       		if(debug_level==307) cout<<"ResetTerms B:"<<stk.size()<<" "<<checked.size()<<endl;
			checked.insert(tmp);
			stk.erase(tmp);
		}
		else{
			return tmp;
		}
	}
	return NULL;
}

bool Grounder::CheckTerm(const string a, const string b)
{
    if(a[0]=='#'){
        assignment[a]=b;    
        return true;
    }
    else if(isupper(a[0])){
        if(debug_level==304) cout<<"Checkterm Check Point A: "<<a<<" "<<b<<endl;
        if(variables[a]->InDomain(b)){
            assignment[a]=b;
            return true;
        }
        else return false;

    }    
    vector<string> s1=BreakTerm(a);
    vector<string> s2=BreakTerm(b);
    if(debug_level==304) cout<<"Checkterm "<<a<<" "<<b<<" "<<s1.size()<<" "<<s2.size()<<endl;
    if(s1.size()!=s2.size()) return false;
    vector<string>::iterator itr_1, itr_2;
    string id1, id2;
    id1=s1.front();
    id2=s2.front();

    if(id1!=id2) return false;
    itr_1=(++s1.begin());
    itr_2=(++s2.begin());
    while(itr_1!=s1.end()){
        if(CheckTerm(*itr_1,*itr_2)==false) return false;
        ++itr_1;
        ++itr_2;
    }
    return true;
}

//Matching to atoms and assign variables
bool Grounder::Match(string s1, string s2)
{
    if(s1[0]=='#'){
        assignment[s1]=s2;    
        return true;
    }
    else if(!isupper(s1[0])){
        if(s1!=s2) return false;
        else return true;
    }
    else{
        if(variables[s1]->InDomain(s2)) assignment[s1]=s2;
        else return false;

    }
    return true;
}


bool Grounder::GetGroundRule(Rule *r)
{
	bool fFact;
	bool fGround;
	list<Literal*> lstLiteral;
	list<Literal*> lstFactLiteral;
	list<GroundLiteral*> lstPosGroundLit;
	list<GroundLiteral*> lstNegGroundLit;
	GroundLiteral* gl;
	Literal *l;
	size_t idx, size;
	Literal *n;
	vector< vector<string> > solution, sol;
    if(debug_level==305) r->Show();
	size=r->GetBodySize();
	for(idx=0;idx<size;idx++)
	{
		l=r->GetLiteral(idx);
		//cout<<l->GetName()<<endl;
		//fFact=CheckFact(l);
        fGround=l->IsGround();
		if(debug_level==305) cout<<"name of atoms "<<l->GetName()<<endl;
		if(fGround==true){
            n=new Literal(l,assignment);
		   	//if(debug_level==305) cout<<"GetGroundRule"<<endl;
			if(l->GetType()==predefined){//The value of this literal can be determined
                if(debug_level==305) cout<<"predefined literal"<<endl;
				if(Evaluate(n)==false){
                    if(debug_level==305) cout<<"evaluated as false"<<endl;
					delete n;
					return false;
				}//else do nothing
                if(debug_level==305) cout<<"evaluated as true";
 			}
			else{//The truth value of it is not determined
				if(debug_level==305) cout<<"non predefined literal"<<endl;
				if(CheckValue(n)==false){
                    if(debug_level==305) cout<<"evaluated as false"<<endl;
					delete n;
					return false;
				}
				else{
                    if(debug_level==305) cout<<"evaluated as non false"<<endl;
					gl=gndProgram->GetLiteral(n);
					if(l->GetNaf())lstPosGroundLit.push_back(gl);
					else lstNegGroundLit.push_back(gl);
				}
			}
			delete n;
		}
		else{
           if(l->GetType()==predefined){
               vector< vector<string> > sol;
                if(GetSolution(l, sol)){
                    if(debug_level==305) cout<<"size: "<<sol.size()<<" : "<<solution.size()<<endl;
                    solution=Join(sol,solution); 
                    if(debug_level==305) cout<<"predefined non ground atom, evaluated as true"<<endl;
                }
                else{
                    if(debug_level==305) cout<<"predefined non ground atom, evaluated as false"<<endl;
                    return false;
                }
    		}
			else{
                  if(debug_level==305) cout<<"non predefined non ground atom"<<endl; 
                  lstLiteral.push_back(l);
            }
 		}
	}

    //
    if(debug_level==305) cout<<"GetGroundRule A:"<<endl;
	//nr->AddHead(r->GetHead());
	//nr->CollectVariable(variables); //Collect any free variables in nr
	//Reset the head of to a ground literal
	GroundLiteral* gHead=NULL;
	fGround=r->GetHead()->IsGround();
	if(fGround==true && r->GetType()==reg){
        Literal *nhead=new Literal(r->GetHead(),assignment);
        gHead=gndProgram->GetLiteral(nhead);
    }
	
	//Get Unbound free variables varlst
    if(debug_level==305) cout<<"GetGroundRule B:"<<endl;    

    set<string> varset=r->GetListVar();
    map<string, Variable*>::iterator itr_vars;
    list<Variable*> varlist;
    set<string>::iterator itr_lst;
    itr_lst=varset.begin();
    while(itr_lst!=varset.end())
    {
        itr_vars=variables.find(*itr_lst);
        if(itr_vars!=variables.end()) varlist.push_back(itr_vars->second);
        ++itr_lst;
    }

    //cout<<"size of varlist "<<varlist.size()<<" "<<solution.size()<<endl;    

    int i;
    size_t sz=solution.size();

    if(debug_level==305) cout<<"GetGroundRule C:"<<sz<<endl;

    if(sz==0){
        if(debug_level==305) cout<<"GetGroundRule E:"<<varlist.size()<<endl;
        if(varlist.size()==0) GetARule(r, lstPosGroundLit, lstNegGroundLit, gHead, lstLiteral); 
        else{
            ResetVariable(varlist);
            while(NextAssignment(varlist)){
                GetARule(r, lstPosGroundLit, lstNegGroundLit, gHead, lstLiteral); 
            }
        }
    }//Else
    for(i=1;i<sz;i++){
        //assignment.clear();
        if(NextAssignment(solution, i)==false) break;
        if(varlist.size()==0) GetARule(r, lstPosGroundLit, lstNegGroundLit, gHead, lstLiteral); 
        else{
            ResetVariable(varlist);
            while(NextAssignment(varlist)){
                GetARule(r, lstPosGroundLit, lstNegGroundLit, gHead, lstLiteral); 
            }
        }
    }
    if(debug_level==305) cout<<"GetGroundRule D:"<<endl;

}

void Grounder::ResetVariable(list<Variable*>& varlst)
{
    list<Variable*>::iterator itr_v;
    itr_v=varlst.begin();
    (*itr_v)->Reset(false);
    ++itr_v;
    while(itr_v!=varlst.end()){
        (*itr_v)->Reset(true);
        assignment[(*itr_v)->GetName()]=(*itr_v)->GetValue();
        ++itr_v;
    }
}

/*
bool Grounder::CheckFact(Literal *l)
{
	if(l->GetType()==predefined) return true;
	string idName=GetRoot(l->GetTerm());
	if(facts.find(idName)!=facts.end()) return true;
	else return false;
}*/

vector<vector<std::string> > Grounder::Join(vector<vector<std::string> >& sol_1,
		vector<vector<std::string> >& sol_2)
{
	//Need Implementation
	vector<vector<string> > solution;
	vector<vector<string> >::iterator itr1, itr2;
	vector<string>::iterator itr1_, itr2_;
	itr1=sol_1.begin();
	itr2=sol_2.begin();
	if(sol_2.empty()) return sol_1;
	size_t size_1=itr1->size();
	size_t size_2=itr2->size();
	size_t i,j;
	list<pair<int, int> > joinVariable;
	itr1_=itr1->begin();
	for(i=0;i<size_1;i++){
		for(j=0;j<size_2;j++){
			if((*itr1)[i]==(*itr2)[j]){
				pair<int, int> npair(i,j);
				joinVariable.push_back(npair);
				break;
			}
		}
	}
	vector<string> newSol;
	if(AppendSolution(newSol, sol_1[0], sol_2[0], joinVariable))solution.push_back(newSol);
	size_t size1=sol_1.size();
	size_t size2=sol_2.size();
	for(size_t i1=1;i1<size1;i1++){
		for(size_t j1=1;j1<size2;j1++){
			if(AppendSolution(newSol, sol_1[i1], sol_2[j1],joinVariable)) solution.push_back(newSol);
		}
	}
	return solution;
}

bool Grounder::AppendSolution(vector<string>& newSol, vector<string> sol_1,
							  vector<string> sol_2, list< pair<int, int> >& joinVariable)
{
	newSol.clear();
	list<pair<int,int> >::iterator itr;
	itr=joinVariable.begin();
	while(itr!=joinVariable.end()){
		if(sol_1[itr->first]!=sol_2[itr->second]) return false;
		else sol_2[itr->second]="";
		++itr;
	}
	newSol=sol_1;
	size_t size=sol_2.size();
	for(size_t i=0;i<size;i++){
		if(sol_2[i]!="") newSol.push_back(sol_2[i]);
	}
	return true;
}


void Grounder::GetARule(Rule* r, list<GroundLiteral*> lstPosGroundLit, list<GroundLiteral*> lstNegGroundLit,
						GroundLiteral* gHead, list<Literal*> lstLiteral)

{
	GroundLiteral* gl;
	Literal* l;
	list<GroundLiteral*>::iterator itr_gl;
	GroundRule *gndRule=new GroundRule(r);
	string rName;
	//The head of ground rule
	itr_gl=lstPosGroundLit.begin();
	while(itr_gl!=lstPosGroundLit.end()){
        if((*itr_gl)->GetTruthValue()==3){
		    gndRule->AddLiteral(*itr_gl,true);
        }
        else if((*itr_gl)->GetTruthValue()==1) return;
		++itr_gl;
	}
	itr_gl=lstNegGroundLit.begin();
	while(itr_gl!=lstNegGroundLit.end()){
        if((*itr_gl)->GetTruthValue()==3) gndRule->AddLiteral(*itr_gl,false);
        else if((*itr_gl)->GetTruthValue()==5) return;
		++itr_gl;
	}
	//cout<<lstLiteral.size()<<" literal size"<<endl;
	list<Literal*>::iterator itr_atm;
	itr_atm=lstLiteral.begin();
	while(itr_atm!=lstLiteral.end())
	{
		l=new Literal((*itr_atm), assignment);
		gl=gndProgram->GetLiteral(l);
		if((*itr_atm)->GetNaf()){
            if(gl->GetTruthValue()==3) gndRule->AddLiteral(gl,true);
            else if(gl->GetTruthValue()==1){
                delete l;
                return;
            }
        }
		else{
            if(gl->GetTruthValue()==3) gndRule->AddLiteral(gl,false);
            else if(gl->GetTruthValue()==5){
                delete l;
                return;
            }
        }
		++itr_atm;
	}
    //if(debug_level==306) cout<<"GetARule A:"<<endl;
	RandomRule* rndRule;
	//The name of the rule
	if(r->GetRuleName()!=""){
        l=new Literal(r->GetRuleName(), assignment);
		Literal* a=new Literal("rule("+l->GetTerm()+")", "true");
        
		gl=gndProgram->GetLiteral(a);
        gl->SetTruthValue(3); //?
		gndRule->AddHead(gl);
		gl->IncreaseSupport();
		rName=l->GetName();
		//if(debug_level==306) cout<<rName<<endl;
		rndRule=gndProgram->GetRandomRule(rName);
		//cout<<rName<<endl;
	}
	//The probability of a pr rule
	if(r->GetProbability()!=""){
        //Evaluate(Replace(r->GetProbability(), assignment));
        
        double v=ComputeProbability(r->GetProbability(), assignment);
		gndRule->AddProbability(v);
	}			
	//The Head of the rule

	
	if(r->GetType()==pr || r->GetType()==reg){
		if(gHead==NULL){
			l=new Literal(r->GetHead(), assignment);
            //cout<<l->GetName()<<endl;
			gl=gndProgram->GetLiteral(l);
			if(r->GetType()==reg) gl->IncreaseSupport();
			gndRule->AddHead(gl);
		}
		else{
      
			if(r->GetType()==reg) gHead->IncreaseSupport();
			gndRule->AddHead(gHead);
		}
	}
	else{//Random selection rules
        //if(debug_level==306) cout<<"GetARule B:"<<endl;
		string sortName=prg->GetAttributeRange(GetRoot(r->GetHead()->GetTerm()));
        //if(debug_level==306) cout<<"GetARule C:"<<sortName<<endl;
		Sort* s=prg->GetSort(sortName);
		size_t sz=s->GetDomainSize();
		string var=r->GetRndVar();
		string v;
		Literal* a;
		//s->Show();
		//cout<<" "<<sz<<endl;
		

		for(size_t idx=0;idx<sz;idx++)
		{
			v=s->GetDomainElement(idx);
			assignment[var]=v;
			a=new Literal(r->GetHead(),assignment);
			//gndProgram->GetLiteral(a)->GetTerm()->
			gl=gndProgram->GetLiteral(a);
			gl->IncreaseSupport();
			rndRule->AddHead(gl);
			if(idx==0) gl->GetTerm()->AddRandomRule(rndRule);
			if(r->GetRange()!=NULL){
				a=new Literal(r->GetRange(),assignment);
				gl=gndProgram->GetLiteral(a);
				rndRule->AddRange(gl);
			}
		}
        //if(debug_level==306) cout<<"GetARule D:"<<endl;
	}
	
	if(r->GetType()==rnd_){
		rndRule->AddRandomRule(gndRule);
		gndProgram->AddRule(gndRule);
	}
	else if(r->GetType()==pr) rndRule->AddPrRules(gndRule);
	else if(r->GetType()==reg) gndProgram->AddRule(gndRule);
	if(debug_level==306) gndRule->Show();
}

void Grounder::Evaluate(GroundTerm* gndTerm)
{
	//First it browse all the literals with attribute term named
	//strName, to see if any literal can be added to the sets
	//if a regular rule with empty body, add it to sets
	//cout<<"Evaluate"<<endl;
	stack<GroundLiteral*> stkPos, stkNeg;
	GroundLiteral *gl;
	GroundRule* gr;
	size_t idx, size;
	//Initialize stack by adding empty rule
	if(debug_level==311) cout<<"Check Point A"<<endl;
	size=gndTerm->GetSize();
	if(debug_level==311) cout<<gndTerm->GetName()<<" "<<size<<endl;
	for(idx=0;idx<size;idx++){
		gl=gndTerm->GetLiteral(idx);
		if(debug_level==311) cout<<"Check Point B "<<gl->GetName()<<endl;
		//cout<<"has"<<endl;
		gr=gl->GetEmptyRule();
		if(gr!=NULL){
			//gr->Show(); 
			//cout<<gr->GetSign()<<endl;
			stkPos.push(gl);
			
		}
		if(gl->GetSupport()==0){
            //cout<<gl->GetName()<<endl;
			stkNeg.push(gl);
		}
	}
	//if(!stkPos.empty() || !stkNeg.empty())
	//Check stacks
	
	if(debug_level==311) cout<<"check stacks "<<stkPos.size()<<" "<<stkNeg.size()<<endl;
	while(!stkPos.empty() || !stkNeg.empty())
	{
		if(!stkPos.empty()){
			gl=stkPos.top();
			positiveAtom.insert(gl->GetName());
			gl->SetTruthValue(5); //value 5
		    if(debug_level==311) cout<<"positive stack "<<gl->GetName()<<endl;
			stkPos.pop();
			/*
			gndTerm=gl->GetTerm();
			//Set others in the literal to s-
			size=gndTerm->GetSize();
			for(idx=0;idx<size;idx++){
				if(gndTerm->GetLiteral(idx)!=gl) stkNeg.push(gndTerm->GetLiteral(idx));
			}  */
			gl->Reduction(true, stkPos, stkNeg);
		}
		else{//stack Neg is not empty
			//Remove all the rules that gl is its head
			//Remove all the rules that is falised
			//Remove all the rule gl is in its pos, 
			//if gr is emtpy size and regular, add head to stack
			//remove it from literal list
			if(debug_level==311) cout<<"negative stack "<<gl->GetName()<<endl;
			gl=stkNeg.top();
			negtiveAtom.insert(gl->GetName());
			gl->SetTruthValue(1); //value 1
			stkNeg.pop();
			gl->Reduction(false,stkPos,stkNeg);
		}
	}
	
	//* gr;
    if(debug_level==311) cout<<"out of the first loop"<<endl;
	map<std::string, RandomRule*>::iterator itr_rnd;
    if(debug_level==311) gndProgram->Show();
	itr_rnd=gndProgram->rndRule.begin();
	while(itr_rnd!=gndProgram->rndRule.end()){
		itr_rnd->second->SetValid();
		++itr_rnd;
	}
    if(debug_level==311) cout<<"at the end of the function"<<endl;
}

//Evaluate a literal
bool Grounder::Evaluate(Literal* l)
{
    if(l->GetTerm()=="true") return true;
    if(l->GetTerm()=="false") return false; 
    //------------------------------------
   string s=l->GetName();
   if(debug_level==310) cout<<s<<" "<<l->GetNaf()<<endl;
   if(positiveAtom.find(s)!=positiveAtom.end()){//find
        if(debug_level==310) cout<<"found the atom"<<endl;
        if(l->GetNaf()) return true;
        else return false;
    }
    else {
        if(debug_level==310) cout<<"not found the atom"<<endl;
        if(l->GetNaf()) return false;
        else return true;
    }
}

bool Grounder::CheckValue(Literal* l)
{
    if(l->GetNaf()){
        if(negtiveAtom.find(l->GetName())!=negtiveAtom.end()) return false;
        else return true;
    }
    else{
        if(positiveAtom.find(l->GetName())!=positiveAtom.end()) return false;
        else return true;
    }
}

bool Grounder::GetSolution(Literal* l, std::vector<std::vector<std::string> >& sol)
{
    //Reset();//Reset the free variables
    set<string> varset=l->GetVariable();
    list<Variable*> varlist;
    //cout<<"GetSolution "<<varset.size()<<endl;
    vector<string> title;
	set<string>::iterator itr=varset.begin();
    while(itr!=varset.end()){
        title.push_back(*itr);
        varlist.push_back(variables[*itr]);
        ++itr;
    }
    sol.push_back(title); 

    ResetVariable(varlist);

    bool b1=l->GetNaf();
    if(debug_level==308) cout<<b1<<" "<<l->GetName()<<endl;;
    while(NextAssignment(varlist)){
        Literal *nl=new Literal(l, assignment);
        bool b2=Evaluate(nl);
        //Replace Line 110510_1428
        //if(b1 && b2 || !b1 && !b2){
        if(b2){
        //110510_1428
            if(debug_level==308) cout<<"T "<<nl->GetName();
            AddSolution(varlist,sol);
        }
        else{
            if(debug_level==308) cout<<"F "<<nl->GetName();
        }
    }
    if(debug_level==308) cout<<endl;
    if(sol.size()==1) return false;
    else return true;
}

void Grounder::AddSolution(list<Variable*>& varlist, vector<vector<string> >& sol)
{
    vector<string> s;
    list<Variable*>::iterator itr_v;
    itr_v=varlist.begin();
    while(itr_v!=varlist.end()){
        s.push_back((*itr_v)->GetValue());
        //cout<<(*itr_v)->GetValue()<<" ";
        ++itr_v;
    }
    sol.push_back(s);
}

/*
vector<vector<string> > Grounder::GetVarSolution(string varName)
{
	set<Variable*>::iterator itr;	
	itr=prg->variable.begin();
	vector<string> s;
	vector<vector<string> > sol;
	if(variables.find(varName)!=variables.end()){
	    Variable* var=variables[varName];
	//cout<<varName<<endl;
	//cout<<var->GetName()<<endl;
	    s.push_back(varName);
	    sol.push_back(s);
	
	    var->Reset();
	    do{
	        vector<string> ns;
		ns.push_back(var->GetValue());
		sol.push_back(ns);
	    }while(var->NextValue());
	}
	return sol;
}*/


