//#include "stdafx.h"
#include "State.h"
#include <iostream>
#include <vector>
#include <utility>
#include <list>
#include <time.h>

using namespace std;

State::State()
{
	asize=0;
	rsize=0;
}

State::State(State *s): prob(s->prob), asize(s->asize), rsize(s->rsize), prg(s->prg), upped(s->GetUpped())
{
	//clock_t start=clock();	
	aval=new int[asize];
	atom=new int[asize];
	rspt=new int[asize];
	rule=new int[rsize];
	int i;
	for(i=0;i<asize;i++){
		aval[i]=s->aval[i];
		atom[i]=s->atom[i];
		rspt[i]=s->rspt[i];
	}
	for(i=0;i<rsize;i++){
		rule[i]=s->rule[i];
	}
	//pos=s->pos;
	//neg=s->neg;
	firedRndRule=s->firedRndRule;
	//upper=s->upper;
	//clock_t end=clock();
	//clkAtMost+=(long)(end-start);
    debug_level=s->GetDebugLevel();

}

State::State(GroundProgram* p, Grounder* grnd):upped(false)
{
	int k;
	vector<GroundLiteral*>::iterator itr_lit;
	vector<GroundRule*>::iterator itr_rule;
	prg=p;
	rsize=prg->gRule.size(); // The total number of ground rules
	asize=prg->gLit.size(); //  The total number of ground literals
	atom=new int[asize];
	aval=new int[asize];
	rspt=new int[asize];
	rule=new int[rsize];

    for(size_t i=0;i<asize;i++){
        atom[i]=0;
    }

	//Initial rule array
	k=0;
	itr_rule=prg->gRule.begin();
	while(itr_rule!=prg->gRule.end()){
		if((*itr_rule)->GetValid()==true){
		    rule[k]=(*itr_rule)->GetBodySize(true)+(*itr_rule)->GetBodySize(false)+1; 
			atom[(*itr_rule)->GetHead()->GetId()]++;
		}
		else rule[k]=-2;
		k++;
		itr_rule++;
	}
	//
	//Inital atom array
	k=0;
	itr_lit=prg->gLit.begin();
	while(itr_lit!=prg->gLit.end()){
		aval[k]=(*itr_lit)->GetTruthValue();
        if(aval[k]==5 || aval[k]==1) atom[k]=-1; //known value, reset atom[k]
		//atom[k]=(*itr_lit)->GetHeadRuleSize();
		if((*itr_lit)->GetSign()==false) atom[k]+=(*itr_lit)->CountPositiveLiteral();
		//aspt[k]=(*itr_lit)->GetNegSprRuleSize();
		//if(aspt[k]>0) upper.insert(k);
		//If this literal is neg, then check its positive atom
		rspt[k]=atom[k];
		k++;
		++itr_lit;
	}
        //Consider random attribute atoms
	map<string, RandomRule*>::iterator itr_map;
	itr_map=prg->rndRule.begin();
	while(itr_map!=prg->rndRule.end()){
		if(itr_map->second->GetRandomRule()->GetValid()==true){
			size_t sz=(*itr_map).second->GetHeadSize();
			for(size_t i=0;i<sz;i++){
				int glit_id=(*itr_map).second->GetHeadLiteral(i)->GetId();
				atom[glit_id]++;
				rspt[glit_id]++;
				//rspt[(*itr_map).second->GetHeadLiteral(i)->GetId()]++;
			}
		}
		++itr_map;
	}
   	
	//pos=grnd->GetPostiveAtom();
	//neg=grnd->GetNegtiveAtom();
	prob=1;

	//cout<<"State Initilized"<<endl;
	//Show(true, false, true);
	
}



State::~State()
{
	delete [] atom;
	delete [] rspt;
	delete [] aval;
	delete [] rule;
}
void State::Show(bool bAtom, bool bRule, bool bKnown)
{
	int i;
	list<int>::iterator itr;
	/*
	cout<<"choice made"<<endl;
	itr=choice.begin();
	while(itr!=choice.end()){
		cout<<prg->groundLiteral[*itr]->name<<" ";
		itr++;
	}
	cout<<endl; */
	cout<<endl;
	if(bAtom==true){
		cout<<"Literals in the State:  aval  atom rspt aspt"<<endl<<endl;
		for(i=0;i<asize;i++)
		{
			cout<<i<<" "<<prg->gLit[i]->GetName()<<" "<<aval[i]<<" "<<atom[i]<<" "<<rspt[i]<<" "<<endl;
		}
	}
	if(bRule==true){
		cout<<"Rule in the State"<<endl;
		for(i=0;i<rsize;i++){
			cout<<i<<" "<<rule[i]<<"  ";
			//prg->ShowRule(prg->gRule[i]);
			prg->gRule[i]->Show();
		}  
	}
	if(bKnown==true){
		cout<<"True literals"<<endl;
		for(i=0;i<asize;i++){
           if(aval[i]==5) cout<<" "<<prg->gLit[i]->GetName();
        }
		cout<<endl<<endl;
		cout<<"False literals"<<endl;
		for(i=0;i<asize;i++){
           if(aval[i]==1) cout<<" "<<prg->gLit[i]->GetName();
        }
		cout<<endl;
		cout<<"Fired Random Selection Rules"<<endl;
        set<string>::iterator itr_set;
		itr_set=firedRndRule.begin();
		while(itr_set!=firedRndRule.end()){
			cout<<*itr_set<<" ";
			++itr_set;
		}
		cout<<endl;
		
	}
	cout<<endl<<"Probability: "<<prob<<endl;
	cout<<"End of State"<<endl<<endl;
	//cin>>i; 
}

bool State::Close(int aid, int value)
{
    //clock_t start=clock();
    int id;
    int val;
    int pre_val;

    if(debug_level==401) cout<<"name and value "<<aid<<" "<<value<<endl;

    stack< pair<int, int> > stk_1, stk_2;

    GroundLiteral *gl;
    //pair<int, int> p(aid, value);


    if(CheckValueConsistency(aid, value)){
         pair<int, int> np(aid,value);
         if(value==MBT || value==MBF) stk_2.push(np);
      	 else stk_1.push(np);
    }
    else return false;
    
    
	
    if(value==TRUE && UpdateRule_8(prg->gLit[aid], stk_1, stk_2)==false) return false;
    if(debug_level==401) cout<<"Check A"<<endl;
    while(!stk_1.empty()){
	    //if(debug_level==401) cout<<gl->name<<" "<<stack.front().second<<endl;
	    id=stk_1.top().first;
	    val=stk_1.top().second;
        pre_val=aval[id];
	    gl=prg->gLit[id];
	    if(debug_level==401) cout<<gl->GetName()<<" "<<pre_val<<" "<<val<<endl;
        stk_1.pop();
        if((val>=UNKNOWN && pre_val<val)||(val<=UNKNOWN && pre_val>val)) aval[id]=val;
        else continue;


        if(gl->GetName().substr(0,5)=="rule("){
            if(val<UNKNOWN && !(UpdateRule_9(gl, stk_1, stk_2))) return false;
            continue;
        }
	    if(pre_val==UNKNOWN && val==TRUE){
            if(!(UpdateRule_1(gl, stk_1, stk_2) &&
                 UpdateRule_3(gl, stk_1, stk_2))) return false;
        }
        else if(pre_val==MBT && val==TRUE){
            //pos.insert(gl->GetName());
	        if(!UpdateRule_5(gl, stk_1, stk_2)) return false;
        }
        else if(pre_val==UNKNOWN && val==FALSE){
            //neg.insert(gl->GetName());
            if(!(UpdateRule_2(gl, stk_1, stk_2) &&
                 UpdateRule_4(gl, stk_1, stk_2))) return false;
	        // UpdateRule_10(gl, stk_1, stk_2);
        }
        else if(pre_val==MBF && val==FALSE){
            //neg.insert(gl->GetName());
            if(!(UpdateRule_6(gl, stk_1, stk_2) &&
                 UpdateRule_7(gl, stk_1, stk_2))) return false;
        }
    }
    if(debug_level==401) cout<<"Check B"<<endl;
    while(!stk_2.empty()){
	//cout<<gl->name<<" "<<stack.front().second<<endl;
	    id=stk_2.top().first;
    	val=stk_2.top().second;
        pre_val=aval[id];
    	gl=prg->gLit[id];
	    if(debug_level==401) cout<<gl->GetName()<<" "<<pre_val<<" "<<val<<endl;
    	stk_2.pop();
        if((val>=UNKNOWN && pre_val<val)||(val<=UNKNOWN && pre_val>val)) aval[id]=val;
        else continue;

        if(debug_level==401) cout<<"Check D"<<endl;
        
        //if(gl->GetName().substr(0,5)=="rule("){
            //cout<<"in"<<endl;
        //    if(val<UNKNOWN && !(UpdateRule_9(gl, stk_1, stk_2))) return false;
        //    continue;
        //}
	    if(pre_val==UNKNOWN && val==MBT){
            aval[id]=val;
            if(!(UpdateRule_1(gl, stk_1, stk_2) &&
                 UpdateRule_3(gl, stk_1, stk_2))) return false;

        }
        else if(pre_val==UNKNOWN && val==MBF){
            aval[id]=val;
            if(!(UpdateRule_2(gl, stk_1, stk_2) &&
                 UpdateRule_4(gl, stk_1, stk_2))) return false;
        }
    }
    
    if(debug_level==401) cout<<"Check C"<<endl;
    //clock_t end=clock();
    //clkAtMost+=(long)(end-start);		
    return true;
}
        
bool State::UpClosure()
{
    //clock_t start=clock();
    int id;
    int val;
    int pre_val;
    SetUpped(true);
    stack< pair<int, int> > stk_1, stk_2;

    //list<GroundRule*>::iterator itr;
    //ist<GroundLiteral*>::iterator itrg;
    GroundLiteral *gl;
    //pair<int, int> p(aid, value);
    //cout<<"up close"<<endl;
    while(AtMost(stk_1)){
    if(stk_1.empty()) return true;
    while(!stk_1.empty()){
	    //cout<<gl->name<<" "<<stack.front().second<<endl;
	    id=stk_1.top().first;
	    val=stk_1.top().second;
        pre_val=aval[id];
	    gl=prg->gLit[id];
	    //cout<<gl->GetName()<<" "<<pre_val<<" "<<val<<endl;
	    stk_1.pop();
       
	    if(pre_val==UNKNOWN && val==TRUE){
            aval[id]=val;
	        //pos.insert(gl->GetName());
	    
            if(!(UpdateRule_1(gl, stk_1, stk_2) &&
                 UpdateRule_3(gl, stk_1, stk_2))) return false;
        }
        else if(pre_val==MBT && val==TRUE){
            aval[id]=val;
	        if(!UpdateRule_5(gl, stk_1, stk_2)) return false;
        }
        else if(pre_val==UNKNOWN && val==FALSE){
            aval[id]=val;
	        if(!(UpdateRule_2(gl, stk_1, stk_2) &&
                 UpdateRule_4(gl, stk_1, stk_2))) return false;
	        // UpdateRule_10(gl, stk_1, stk_2);
        }
        else if(pre_val==MBF && val==FALSE){
            aval[id]=val;
	        //neg.insert(gl->GetName());
            if(!(UpdateRule_6(gl, stk_1, stk_2) &&
                 UpdateRule_7(gl, stk_1, stk_2))) return false;
        }
	}
    while(!stk_2.empty()){
	//cout<<gl->name<<" "<<stack.front().second<<endl;
	    id=stk_2.top().first;
	    val=stk_2.top().second;
        pre_val=aval[id];
	    gl=prg->gLit[id];
        //cout<<gl->GetName()<<" "<<pre_val<<" "<<val<<endl;
	    stk_2.pop();
	    if(pre_val==UNKNOWN && val==MBT){
            aval[id]=val;
            if(!(UpdateRule_1(gl, stk_1, stk_2) &&
                 UpdateRule_3(gl, stk_1, stk_2))) return false;
        }
        else if(pre_val==UNKNOWN && val==MBF){
            aval[id]=val;
            if(!(UpdateRule_2(gl, stk_1, stk_2) &&
                 UpdateRule_4(gl, stk_1, stk_2))) return false;
        }
    }
    }
    //clock_t end=clock();
    //clkAtMost+=(long)(end-start);		
    return false;	
}

//The precondition of the this function
//is the literals in the body are at least MBT
bool State::CountMValue(GroundRule *r)
{
    size_t idx;
    GroundLiteral* gl;
    size_t size=r->GetBodySize(true);
    for(idx=0;idx<size;idx++){
	    gl=r->GetBodyLit(idx,true);
	    if(aval[gl->GetId()]!=TRUE) return false;
    }
    size=r->GetBodySize(false);
    for(idx=0;idx<size;idx++){
	    gl=r->GetBodyLit(idx,false);
	    if(negVal(aval[gl->GetId()])!=TRUE) return false;
    }
    return true;
}

void State::SetGroundRuleFalse(GroundRule* r, stack< pair<int,int> >& stk_2)
{
    size_t idx;
    GroundLiteral* gl;
    size_t size=r->GetBodySize(true);
    for(idx=0;idx<size;idx++){
	    gl=r->GetBodyLit(idx,true);
	    if(aval[gl->GetId()]==UNKNOWN){
	        pair<int, int> np(gl->GetId(),MBF);
	        stk_2.push(np); 
	        return;
	    }
    }
    size=r->GetBodySize(false);
    for(idx=0;idx<size;idx++){
	    gl=r->GetBodyLit(idx,false);
	    if(aval[gl->GetId()]==UNKNOWN){
	        pair<int, int> np(gl->GetId(),MBT);
	        stk_2.push(np); 
	        return;
	        }
    }
}

void State::SetGroundRuleTrue(GroundRule* r, stack< pair<int,int> >& stk_2)
{
    size_t idx;
    GroundLiteral* gl;
    size_t size=r->GetBodySize(true);
    for(idx=0;idx<size;idx++){
	    gl=r->GetBodyLit(idx,true);
	    if(aval[gl->GetId()]==UNKNOWN){
	        pair<int, int> np(gl->GetId(),MBT);
	        stk_2.push(np); 
	    }
    }
    size=r->GetBodySize(false);
    for(idx=0;idx<size;idx++){
	    gl=r->GetBodyLit(idx,false);
	    if(aval[gl->GetId()]==UNKNOWN){
	        pair<int, int> np(gl->GetId(),MBF);
	        stk_2.push(np); 
	    }
    }
}




//The Literal is true, check every rule where the literal is positive
//then the counter for the body decreases
//where the literal is negtive, the rule is falsified
bool State::UpdateRule_1(GroundLiteral* gl, stack< pair<int,int> >& stk_1, stack< pair<int,int> >& stk_2)
{
    size_t size=gl->GetBodySize(true);
    size_t idx, idx_1;
    size_t sz;
    int rid;
    int gid;
    if(debug_level==403) cout<<"update 1"<<endl;
    if(debug_level==402) cout<<"Check A"<<endl;
    GroundRule* gr;
    for(idx=0;idx<size;idx++){
        gr=gl->GetBodyRule(idx, true);
	    rid=gr->GetId();
	    if(rule[rid]>0) rule[rid]--;
	    if(rule[rid]==1){
	        if(aval[gr->GetHead()->GetId()]==UNKNOWN){
	    	    if(aval[gl->GetId()]==TRUE && CountMValue(gr)){	
		            if(CheckValueConsistency(gr->GetHead()->GetId(), TRUE)){
		                pair<int, int> np(gr->GetHead()->GetId(),TRUE);
		                stk_1.push(np); 
		            }
                    else { return false; }
		        }
		        else{
		            if(CheckValueConsistency(gr->GetHead()->GetId(), MBT)){
			            pair<int, int> np(gr->GetHead()->GetId(),MBT);
			            stk_2.push(np);
		            }
		            else { return false; }
		        }
	        }
	        else if(aval[gr->GetHead()->GetId()]<UNKNOWN){
		        SetGroundRuleFalse(gr, stk_2);
	        }
	    }
	    if(rule[rid]==0){
		    if(aval[gl->GetId()]==TRUE && CountMValue(gr)){
		        if(CheckValueConsistency(gr->GetHead()->GetId(), TRUE)){
		            pair<int, int> np(gr->GetHead()->GetId(),TRUE);
		            stk_1.push(np); 
		        }
                else return false;
	    	}
	    }
    }
    //Literal appear in the negtive part
    if(debug_level==402) cout<<"Check B"<<endl;
    size=gl->GetBodySize(false);
    for(idx=0;idx<size;idx++){
        gr=gl->GetBodyRule(idx, false);
        rid=gr->GetId();
        gid=gr->GetHead()->GetId();
        if(rule[rid]>=0){ //Falsified
           if(aval[gl->GetId()]==TRUE){
		        rspt[gid]--;
		        rule[rid]=-2;
	        }
	        else rule[rid]=-1;
	        atom[gid]--;
	    }
	    else if(rule[rid]==-1){
	        if(aval[gl->GetId()]==TRUE){
		        rspt[gid]--;
		        rule[rid]=-2;
	        }
	        else continue;	
        }
        if(rspt[gid]==0){
	        if(CheckValueConsistency(gid, FALSE)){
                    pair<int, int> np(gid,FALSE);
                    stk_1.push(np);
	        }
	        else return false;
        }
        else if(atom[gid]==0){
	        if(CheckValueConsistency(gid, MBF)){
                   pair<int, int> np(gid,MBF);
                   stk_2.push(np);
	        }
	        else return false;
       }
       else if(atom[gid]==1 && aval[gid]==MBT){
	       sz=gr->GetHead()->GetHeadRuleSize();
           for(idx_1=0;idx_1<sz;idx_1++){
               GroundRule* gr_1=gr->GetHead()->GetHeadRule(idx_1);
               if(rule[gr_1->GetId()]>0) SetGroundRuleTrue(gr_1, stk_2);
           }
       }
    }
    if(debug_level==402) cout<<"Check C"<<endl;
    //Literal in the head of the rule
    size=gl->GetHeadRuleSize();
    for(idx=0;idx<size;idx++){
        gr=gl->GetHeadRule(idx);
        if(rule[gr->GetId()]>0){
        	if(size==1) SetGroundRuleTrue(gr, stk_2);
            rule[gr->GetId()]--;
        }
    }
    return true;
}

//The Literal is false, check every rule where the literal is false
//then the counter for the body decreases
//where the literal is negtive, the rule is falsified
bool State::UpdateRule_2(GroundLiteral* gl, stack< pair<int,int> >& stk_1, stack< pair<int,int> >& stk_2)
{
    size_t size=gl->GetBodySize(false);
    size_t idx, idx_1;
    size_t sz;
    int rid;
    int gid;
    GroundRule* gr;
    if(debug_level==403) cout<<"update 2"<<endl;
    for(idx=0;idx<size;idx++){
        gr=gl->GetBodyRule(idx, false);
	    rid=gr->GetId();
	    if(rule[rid]>0) rule[rid]--;
	    if(rule[rid]==1){
	        if(aval[gr->GetHead()->GetId()]==UNKNOWN){
	   	        if(aval[gl->GetId()]==FALSE && CountMValue(gr)){	
		            if(CheckValueConsistency(gr->GetHead()->GetId(), TRUE)){
		                pair<int, int> np(gr->GetHead()->GetId(),TRUE);
		                stk_1.push(np); 
		            }
                    else return false;
		        }
		        else{
		            if(CheckValueConsistency(gr->GetHead()->GetId(), MBT)){
			            pair<int, int> np(gr->GetHead()->GetId(),MBT);
			            stk_2.push(np);
		            }
		            else return false;
		        }
	        }
	        else if(aval[gr->GetHead()->GetId()]<UNKNOWN){
	            SetGroundRuleFalse(gr, stk_2);
	        }
	    }
	    if(rule[rid]==0){
		    if(aval[gl->GetId()]==FALSE && CountMValue(gr)){
		        if(CheckValueConsistency(gr->GetHead()->GetId(), TRUE)){
		            pair<int, int> np(gr->GetHead()->GetId(),TRUE);
		            stk_1.push(np); 
		        }
                else return false;
		    }
	    }
   }
   //Literal appear in the positive part
   size=gl->GetBodySize(true);
   for(idx=0;idx<size;idx++){
        gr=gl->GetBodyRule(idx, true);
    	rid=gr->GetId();
    	GroundLiteral* glit=gr->GetHead();
        gid=glit->GetId();
  
        if(rule[rid]>=0){ //Falsified
            if(aval[gl->GetId()]==FALSE){
	            rspt[gid]--;
	            rule[rid]=-2;
	        }
	        else rule[rid]=-1;
	        atom[gid]--;
	    }
	    else if(rule[rid]==-1){
	        if(aval[gl->GetId()]==FALSE){
		        rspt[gid]--;
		        rule[rid]=-2;
	        }
	        else continue;	
	    }
	    else continue;

	    if(rspt[gid]==0){
		    if(CheckValueConsistency(gid, FALSE)){
		        pair<int, int> np(gid,FALSE);
		        stk_1.push(np);
		    }
		    else return false;
	    }
	    else if(atom[gid]==0){
		    if(CheckValueConsistency(gid, MBF)){
		        pair<int, int> np(gid,MBF);
		        stk_2.push(np);
		    }
		    else return false;
	    }
	    else if(atom[gid]==1 && aval[gid]==MBT){
		    sz=glit->GetHeadRuleSize();
		    for(idx_1=0;idx_1<sz;idx_1++){
		        GroundRule* gr_1=glit->GetHeadRule(idx_1);
		        if(rule[gr_1->GetId()]>0) SetGroundRuleTrue(gr_1, stk_2);
		    }
	    }
        
    }
    size=gl->GetHeadRuleSize();
    for(idx=0;idx<size;idx++){
        gr=gl->GetHeadRule(idx);
        if(rule[gr->GetId()]>0){
	        rule[gr->GetId()]--;
	        if(rule[gr->GetId()]==1) SetGroundRuleFalse(gr, stk_2);
        }
    }
    return true;
}

// :- a=y, -a=y;  // a\neq y^\prime :- a=y, only works for a=y
bool State::UpdateRule_3(GroundLiteral* gl, stack< pair<int,int> >& stk_1, stack< pair<int,int> >& stk_2)
{
    if(gl->GetSign()==false) return true;
    size_t idx_1, idx;
    int lit_id;	
    if(debug_level==403) cout<<"update 3"<<endl;
    if(debug_level==404) cout<<"Check A"<<endl;
    GroundTerm* gterm=gl->GetTerm();
    GroundLiteral* glit;
    size_t sz=gterm->GetSize();
    if(debug_level==404) cout<<"Check A "<<sz<<endl;
    for(idx_1=0;idx_1<sz;idx_1++){
        glit=gterm->GetLiteral(idx_1);
        lit_id=glit->GetId();
        if(debug_level==404) cout<<"Check B"<<endl;
        if(glit->GetSign()==false && glit->GetName()==gl->GetName()){
            if(debug_level==404) cout<<"Check C"<<endl;
	        if(CheckValueConsistency(lit_id, MBF)){
                pair<int, int> np(lit_id,MBF);
                stk_2.push(np);
	        }
	        else return false;
        }
        else if(glit->GetSign()==false){
            if(debug_level==404) cout<<"Check D"<<endl;
	        if(CheckValueConsistency(lit_id, aval[gl->GetId()])){
                pair<int, int> np(lit_id,aval[gl->GetId()]);
		        if(aval[gl->GetId()]==TRUE) stk_1.push(np);
		        else stk_2.push(np);
	        }
	        else return false;
        }
	    else if(glit!=gl){
            if(debug_level==404) cout<<"Check E"<<endl;
             if(CheckValueConsistency(lit_id, MBF)){
		        pair<int, int> np(lit_id,MBF);
		        stk_2.push(np);
	         }
	         else return false;
	    }
    }   
    if(debug_level==404) cout<<"Check F"<<endl;
    return true;   
}

//Reduce the supporting rule of a\neq y
// a\neq y^\prime :- a=y, only works for a=y
bool State::UpdateRule_4(GroundLiteral* gl, stack< pair<int,int> >& stk_1, stack< pair<int,int> >& stk_2)
{
    if(gl->GetSign()==false) return true;
    size_t idx_1, idx;
    int gid;
    int rid;
    if(debug_level==403) cout<<"update 4"<<endl;
    GroundTerm* gterm=gl->GetTerm();
    GroundLiteral* glit;
    GroundRule* gr;
    size_t sz=gterm->GetSize();
    for(idx_1=0;idx_1<sz;idx_1++){
        glit=gterm->GetLiteral(idx_1);
	    gid=glit->GetId();
        if(glit->GetSign()==false  && "-"+glit->GetName()!=gl->GetName()){
	        if(aval[gl->GetId()]==FALSE) rspt[gid]--;
	        atom[gid]--;
	               
            if(rspt[gid]==0){
		        if(CheckValueConsistency(gid, FALSE)){
                    pair<int, int> np(gid,FALSE);
                    stk_1.push(np);
		        }
		        else return false;
            }
	        else if(atom[gid]==0){
		        if(CheckValueConsistency(gid, MBF)){
                    pair<int, int> np(gid,MBF);
                    stk_2.push(np);
		        }
		        else return false;
	        }
	        else if(atom[gid]==1 && aval[gid]==MBT){
		        sz=glit->GetHeadRuleSize();
                for(idx_1=0;idx_1<sz;idx_1++){
                    gr=glit->GetHeadRule(idx_1);
                    if(rule[gr->GetId()]>=0) SetGroundRuleTrue(gr, stk_2);
	            }
	        }
        }
    }
    return true;
}

//When mbt to T 
bool State::UpdateRule_5(GroundLiteral* gl, stack< pair<int,int> >& stk_1, stack< pair<int,int> >& stk_2)
{
    size_t size=gl->GetBodySize(true);
    size_t idx;
    int lit_id;
    if(debug_level==403) cout<<"update 5"<<endl;
    GroundRule* gr;
    for(idx=0;idx<size;idx++){
	    gr=gl->GetBodyRule(idx, true);
	    if(rule[gr->GetId()]>=0 && CountMValue(gr)){
	        rule[gr->GetId()]=-2;	
	        if(CheckValueConsistency(gr->GetHead()->GetId(), TRUE)){
	            pair<int, int> np(gr->GetHead()->GetId(),TRUE);
	            stk_1.push(np); 
	        }
            else return false;
	    }
    }
    size=gl->GetBodySize(false);
    for(idx=0;idx<size;idx++){
	    gr=gl->GetBodyRule(idx, false);
	    if(rule[gr->GetId()]== -1){
	        int gid=gr->GetHead()->GetId();
	        rspt[gid]--;
	        if(rspt[gid]==0){
	            if(CheckValueConsistency(gid, FALSE)){
	                pair<int, int> np(gid,FALSE);
	                stk_1.push(np);
	            }
	            else return false;
	        }
	        rule[gr->GetId()]=-2;
	    }
    }
    return true;
}

//When mbf to F 
bool State::UpdateRule_6(GroundLiteral* gl, stack< pair<int,int> >& stk_1, stack< pair<int,int> >& stk_2)
{
    size_t size=gl->GetBodySize(false);
    size_t idx;
    int lit_id;
    if(debug_level==403) cout<<"update 6"<<endl;
    GroundRule* gr;
    for(idx=0;idx<size;idx++){
	    gr=gl->GetBodyRule(idx, false);
	    if(rule[gr->GetId()]>=0 && CountMValue(gr)){
	        rule[gr->GetId()]=-2;	
	        if(CheckValueConsistency(gr->GetHead()->GetId(), TRUE)){
	            pair<int, int> np(gr->GetHead()->GetId(),TRUE);
	            stk_1.push(np); 
	        }
            else return false;
    	}
    }
    size=gl->GetBodySize(true);
    for(idx=0;idx<size;idx++){
	    gr=gl->GetBodyRule(idx, true);
	    if(rule[gr->GetId()]== -1){
	        int gid=gr->GetHead()->GetId();
	        rspt[gid]--;
	        if(rspt[gid]==0){
	            if(CheckValueConsistency(gid, FALSE)){
	                pair<int, int> np(gid,FALSE);
	                stk_1.push(np);
	            }
	            else return false;
	        }
	        rule[gr->GetId()]=-2;
	    }
    }
    return true;
}


//For MBF to F update the support for a\neq y^\prime
bool State::UpdateRule_7(GroundLiteral* gl, stack< pair<int,int> >& stk_1, stack< pair<int,int> >& stk_2)
{
    if(gl->GetSign()==false) return true;
    size_t idx_1, idx;
    int gid;
    if(debug_level==403) cout<<"update 7"<<endl;
    GroundTerm* gterm=gl->GetTerm();
    GroundLiteral* glit;
    size_t sz=gterm->GetSize();
    for(idx_1=0;idx_1<sz;idx_1++){
        glit=gterm->GetLiteral(idx_1);
	    gid=glit->GetId();
        if(glit->GetSign()==false  && "-"+glit->GetName()!=gl->GetName()){
	        rspt[gid]--;
            if(rspt[gid]==0){
		        if(CheckValueConsistency(gid, FALSE)){
                    pair<int, int> np(gid,FALSE);
                    stk_1.push(np);
		        }
		        else return false;
            }
        }
    }
    return true;
}

bool State::UpdateRule_8(GroundLiteral* gl, stack< pair<int,int> >& stk_1, stack< pair<int,int> >& stk_2)
{
    size_t idx_1, idx;
    int gid;
    if(debug_level==403) cout<<"update 8"<<endl;
    GroundTerm* gterm=gl->GetTerm();
    GroundLiteral* glit;
    size_t sz=gterm->GetSize();
    for(idx_1=0;idx_1<sz;idx_1++){
        glit=gterm->GetLiteral(idx_1);
	    gid=glit->GetId();
        if(glit->GetSign()==true  && glit!=gl){
	        rspt[gid]--;
	        atom[gid]--;
            if(rspt[gid]==0){
		        if(CheckValueConsistency(gid, FALSE)){
                    pair<int, int> np(gid,FALSE);
                    stk_1.push(np);
		        }
		        else return false;
            }
        }
    }
    return true;
}

bool State::UpdateRule_9(GroundLiteral* gl, stack< pair<int,int> >& stk_1, stack< pair<int,int> >& stk_2)
{
    //cout<<"update 9"<<endl;    
    if(debug_level==403) cout<<"update 9"<<endl;
    string s=gl->GetName().substr(5,gl->GetName().length()-11);   
    //cout<<"extract string "<<s<<endl;
    //int i;
    //cin>>i;
    map<string, RandomRule*>::iterator itr_rnd;
    itr_rnd=prg->rndRule.find(s+"=true");
    if(itr_rnd!=prg->rndRule.end()){
       //Ready to fire
       //cout<<itr_rnd->first<<" "<<s<<endl;
	   vector<GroundLiteral*>::iterator itr_glit;
       size_t size=itr_rnd->second->GetHeadSize();
       for(size_t idx=0;idx<size;idx++){
            GroundLiteral* glit=itr_rnd->second->GetHeadLiteral(idx);
            int gid=glit->GetId();
            if(aval[gl->GetId()]==FALSE){
	           rspt[gid]--;
            }
            atom[gid]--;
            if(rspt[gid]==0){
	            if(CheckValueConsistency(gid, FALSE)){
	                pair<int, int> np(gid,FALSE);
	                stk_1.push(np);
            	}
	           else return false;
            }
            else if(atom[gid]==0){
	            if(CheckValueConsistency(gid, MBF)){
	                pair<int, int> np(gid,MBF);
	                stk_2.push(np);
	            }
	            else return false;
            }
        }
        return true;
    }
    return false;
}


//return the negation of the truth value
int State::negVal(int val)
{
    return TRUE-val+1;
}

int State::Satisify(std::vector<GroundLiteral*>& gvec, bool flag) const
{
    vector<GroundLiteral*>::iterator itr;
    //cout<<"ho"<<" ";	
    itr=gvec.begin();
    int value=TRUE;
    while(itr!=gvec.end())
    {
	
	 if(flag==true){
		if(aval[(*itr)->GetId()]==FALSE)return FALSE;
		else if(aval[(*itr)->GetId()]!=TRUE) value=UNKNOWN;
	 }
	 if (flag==false){
		if(aval[(*itr)->GetId()]==TRUE) return FALSE;
		else if(aval[(*itr)->GetId()]!=FALSE) value=UNKNOWN;
	 }
        ++itr;
    }
    return value;
}

bool State::Known(std::vector<GroundLiteral*>& gvec)
{
    size_t sz=gvec.size();
    for(size_t idx=0;idx<sz;idx++){
        int id=gvec[idx]->GetId();
        if(aval[id]>FALSE && aval[id]<TRUE) return false;
    }
    return true;
}

bool State::KnownLiteral(list<int>& glst, Formula *f)
{
    list<int>::iterator itr;
    bool flag=true;
    itr=glst.begin();
    rank=0;
    while(itr!=glst.end())
    {
        if(aval[*itr]==TRUE){
            GroundLiteral *gl=prg->gLit[*itr];
            f->AddLiteral(new Literal(gl->GetTermName(), gl->GetValue()));
            rank++;
        }
        else if(aval[*itr]!=FALSE) flag=false;
        ++itr;
    }
    return flag;
}

void State::Copy(State *s)
{
	int i;
	//clock_t start=clock();
	for(i=0;i<asize;i++){
		aval[i]=s->aval[i];
		atom[i]=s->atom[i];
    	rspt[i]=s->rspt[i];
	}
	for(i=0;i<rsize;i++){
		rule[i]=s->rule[i];
	}
	prob=s->prob;
	//pos=s->pos;
	//neg=s->neg;
	firedRndRule=s->firedRndRule;
	//clock_t end=clock();
	//clkAtMost+=(long)(end-start);

}

bool State::AtMost(stack< pair<int,int> >& stk)
{
	
	size_t sz=prg->gRule.size();
	size_t idx;
	int* lid=new int[asize];
	stack<int> stk_id;
    bool flag=false;
    for(int i=0;i<asize;i++){
        if(aval[i]!=TRUE && aval[i]!=FALSE) flag=true;
        lid[i]=0;   
    }
    if(!flag){
        //cout<<"non call activated"<<endl;
        return true;
    } 
	//Show(true,true,true);
	//cout<<endl;
	//clock_t start=clock();
	for(idx=0;idx<sz;idx++){
		int id=prg->gRule[idx]->GetHead()->GetId();
		if(rule[idx]>=0 && aval[id]>=UNKNOWN && aval[id]<=MBT){
            size_t posSize=prg->gRule[idx]->GetBodySize(true);
			size_t posId;
			for(posId=0;posId<posSize;posId++){
				GroundLiteral* glit=prg->gRule[idx]->GetBodyLit(posId,true);
				if(aval[glit->GetId()]!=TRUE) break;
			}
            if(posId==posSize) lid[id]=1;
        } 
	}
	//cout<<endl;
	map<string, RandomRule*>::iterator itr_map;
	vector<GroundLiteral*>::iterator itr_lits;
	itr_map=prg->rndRule.begin();
	while(itr_map!=prg->rndRule.end()){
		RandomRule* rnds=itr_map->second;
		sz=rnds->GetHeadSize();
		for(idx=0;idx<sz;idx++){
			GroundLiteral* l=rnds->GetHeadLiteral(idx);
			if(aval[l->GetId()]>=UNKNOWN &&  aval[l->GetId()]<=MBT) lid[l->GetId()]=1;
		}
		++itr_map;
	}
	for(int i=0;i<asize;i++){
        if(lid[i]==1) stk_id.push(i);
    }
	//set<int> lid;
	//stack<int> stk_id;
    /*
	set<int>::iterator itr_set;
	itr_set=lid.begin();
	while(itr_set!=lid.end()){
		stk_id.push(*itr_set);
		//lid.insert(*itr_set);
        //cout<<(*itr_set)<<" ";
		++itr_set;
	}
    //cout<<endl;
	//clock_t end=clock();
	//clkAtMost+=(long)(end-start); */
	//int id;
        //stack<int> stk_id(prg->upperBound);

	//For debugging
	/*
	cout<<endl<<"Final lid:"<<endl;
	itr_set=lid.begin();
	while(itr_set!=lid.end()){
		cout<<(*itr_set)<<" ";
		++itr_set;
	} 
	cout<<"NO LID"<<endl;
	if(lid.size()==0) Show(true,false, true);
	*/

	//cout<<"NO LID"<<endl;
    //if(stk_id.empty()) return true;
	while(!stk_id.empty())
	{
		int id=stk_id.top();
		stk_id.pop();
		GroundLiteral* gl=prg->gLit[id];
		sz=gl->GetBodySize(true);
		for(idx=0;idx<sz;idx++){
			GroundRule* gr=gl->GetBodyRule(idx,true);
			if(rule[gr->GetId()]>=-1 && lid[gr->GetHead()->GetId()]==0){
				size_t posSize=gr->GetBodySize(true);
				size_t posId;
				for(posId=0;posId<posSize;posId++){
					GroundLiteral* glit=gr->GetBodyLit(posId,true);
					if(aval[glit->GetId()]!=TRUE && lid[glit->GetId()]==0) break;
				}
				if(posId==posSize){
					stk_id.push(gr->GetHead()->GetId());
					lid[gr->GetHead()->GetId()]=1;
				}
			}
		}
	}
	
    
	/*cout<<endl<<"Final lid:"<<endl;
	itr_set=lid.begin();

	while(itr_set!=lid.end()){
		cout<<(*itr_set)<<" ";

		++itr_set;
	} 	
    */
	//sz=prg->gLit.size();
	for(idx=0;idx<asize;idx++){
		if(aval[idx]>FALSE && aval[idx]<TRUE && lid[idx]==0){
			if (aval[idx]==MBT){
			        //cout<<prg->gLit[idx]->GetName()<<" "<<aval[idx]<<" consis"<<endl;
				return false;
			}
            else{
				pair<int, int> np(idx,FALSE);
				//cout<<prg->gLit[idx]->GetName()<<" "<<aval[idx]<<" consis"<<endl;
				//cout<<prg->gLit[idx]->GetName()<<endl;
				stk.push(np);
			}
		}
	}

	//cout<<"NO LID 1"<<endl;
	return true;
}

bool State::CheckValueConsistency(int id, int new_value)
{
	if(debug_level==403) cout<<"Attempt "<<prg->gLit[id]->GetName()<<" "<<aval[id]<<" "<<new_value<<" "<<endl;	
	if((aval[id]>UNKNOWN && new_value<UNKNOWN) 
        || (aval[id]<UNKNOWN && new_value>UNKNOWN)){
	   //cout<<"INCON "<<prg->gLit[id]->GetName()<<" "<<aval[id]<<" "<<new_value<<endl;
	   //Show(true,true,true);
	   return false;
	}
	else return true;
}

int State::KnowTerm(std::list<GroundTerm*>& gndTerm, Formula* f) const
{
	//f=new Formula();	
	list<GroundTerm*>::iterator itr_lst;
	itr_lst=gndTerm.begin();
	while(itr_lst!=gndTerm.end()){
		size_t sz=(*itr_lst)->GetSize();
		size_t idx;
		bool flag=true;
		for(idx=0;idx<sz;idx++){
			GroundLiteral* gl=(*itr_lst)->GetLiteral(idx);
			if(gl->GetSign()){
				if(aval[gl->GetId()]==TRUE) {
					//cout<<gl->GetName()<<endl;
					f->AddLiteral(new Literal(gl->GetTermName(), gl->GetValue()));
					break;
				}
				else if(aval[gl->GetId()]==UNKNOWN){ flag=false;}
			}
		}
		if(idx==sz){
			//delete f;
			if(flag==false) return UNKNOWN;
			else return FALSE;
		}
		++itr_lst;
	}
	return TRUE;
}

int State::EvaluateFormula(Formula *f)
{
    set<Literal*>::iterator itr;
    string operation=f->GetOperation();
	if(f->GetLiteral()!=NULL){
		if(aval[f->GetLiteral()->GetId()]==TRUE) return TRUE;
		else if(aval[f->GetLiteral()->GetId()]==FALSE) return FALSE;
		else return UNKNOWN;
	}
	else if(operation==""){
		int val=TRUE;
		itr=f->GetASet().begin();
		while(itr!=f->GetASet().end()){
			if(aval[(*itr)->GetId()]==FALSE) return FALSE;
			else if (aval[(*itr)->GetId()]!=TRUE) val=UNKNOWN;


			++itr;
		}
		return val;
	}
	else{
		int val_1=EvaluateFormula(f->GetFirstFormula());
		int val_2=EvaluateFormula(f->GetSecondFormula());
        if(operation=="and"){
			if(val_1>FALSE && val_2>FALSE){
				if(val_1!=TRUE || val_2!=TRUE) return UNKNOWN;
				else return TRUE;
			}
			else return FALSE;
		}
		else if(operation=="or"){
			if(val_1==TRUE || val_2==TRUE){
				return TRUE;
			}
			else if(val_1==FALSE && val_2==FALSE) return FALSE;
			else return UNKNOWN;
		}

		else if(operation=="!"){
			return 6-val_2;
		}
		else return UNKNOWN;
	}
}




