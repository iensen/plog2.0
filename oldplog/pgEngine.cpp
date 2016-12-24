#include "pgEngine.h"
#include "GroundProgram.h"
#include "global.h"

#include "State.h"
#include <iostream>
#include <time.h>

#include <list>
#include <set>

using namespace std;

long State::clkAtMost=0;
long State::cntClose=0;

pgEngine::pgEngine(void)
{
   gnd=new GroundProgram();
   stage=false;
}

pgEngine::pgEngine(Program* p, Query* q):prg(p), qry(q)
{
   gnd=new GroundProgram();
   stage=true; //when stage is true, only fire random rules that belongs to the dependant set
}


pgEngine::~pgEngine(void)
{
}


void pgEngine::Run()
{	
	clock_t start=clock();	
    if(debug_level==110){
	    prg->Show();
	    qry->Show();
    }
	grounder=new Grounder(gnd, prg, qry);
    grounder->SetDebugLevel(debug_level);
	grounder->Preprocessing();
    if(debug_level==110) cout<<"After Preprocessing"<<endl;
	//grounder->GroundQuery(qry);
	//prg->Show();
	list<Literal*>::iterator itr_atm;
	itr_atm=qry->condition.begin();
	vector<GroundLiteral*> vecLit;
	int status;
	while(itr_atm!=qry->condition.end()){
        if(debug_level==110) cout<<(*itr_atm)->GetName()<<endl;
		grounder->Ground((*itr_atm)->GetTerm());
        if(debug_level==110) cout<<"After grounding "<<(*itr_atm)->GetName()<<endl;
		vecLit.push_back(gnd->GetLiteral(*itr_atm));
		++itr_atm;
	}
    gnd->DrawLine(); //Draw a line here
    if(debug_level==110) cout<<"size of condition rules "<<gnd->hline<<endl;
	set<string> atomSet;
	qry->CollectFormulaAtom(atomSet);
	set<string>::iterator itr_s;
	if(debug_level==110) cout<<"Set here "<<atomSet.size()<<endl;
	itr_s=atomSet.begin();
	while(itr_s!=atomSet.end()){
		grounder->Ground(GetTerm(*itr_s));
		++itr_s;
	}
	//cout<<"Set here"<<endl;
	gnd->BuildVectors();
	//gnd->BuildUpperBound();

	if(debug_level==110) gnd->Show();
	clock_t end=clock();
	
	//Output grounding information:
	cout<<"Grounding Finished and its duration:"<<((double)end-(double)start)/CLOCKS_PER_SEC<<endl;

    start=clock();
	map<int, double> possibleOutcome;
	map<int,double>::iterator itr_map;

	State* s=new State(gnd, grounder);
    s->SetDebugLevel(debug_level);

	if(debug_level==110) s->Show(true,true,true);

	//return;
    set<Literal*> litSet;
	itr_atm=qry->condition.begin();	
	while(itr_atm!=qry->condition.end()){
		//grounder->Ground(*itr_atm);
		//vecLit.push_back(
		if((*itr_atm)->GetType()==obs){
           if(debug_level==110) cout<<(*itr_atm)->GetName()<<endl;   
		   s->Close(gnd->GetLiteral(*itr_atm)->GetId(), MBT);
           litSet.insert(*itr_atm);
           if(debug_level==110) cout<<"A: Close function passed"<<endl;
        }
		else if((*itr_atm)->GetType()==dos) s->Close(gnd->GetLiteral(*itr_atm)->GetId(), TRUE);
		++itr_atm;
	}

	if(debug_level==11) s->Show(true, true, true);

	State::clkAtMost=0;	
	double TOTAL=0.0;
    BuildRandomDependant(litSet);
    states.push_front(s);
	while(!states.empty()){
		s=states.front();
		if(debug_level==112){
		    s->Show(false,false,true);
		    int i;
		    cin>>i;
        }
		states.pop_front();
		//s->Show(false, false, true);
		status=s->Satisify(vecLit, true);
		if(debug_level==112) cout<<"status "<<status<<endl;
		if(status==TRUE){
			ans.push_front(s);
			TOTAL+=s->prob;
			if(debug_level==111){
                s->Show(false, false, true);
                int i;
                cin>>i;
            }
            //RemoveState(s);
			continue;
		}
		else if(status==FALSE){
			RemoveState(s);
			continue;
		}
		//Status is unknown
		//Try to find a random selection rule to fire
		if(!FireRandomRule(s, possibleOutcome)) //No random rule to fire
		{
			if(debug_level==112) cout<<"No random selection rule is ready to fire, then call atmost and re-evaluate it"<<endl;		
			if(s->GetUpped() || !s->UpClosure()){
                s->Show(false,false,true);
				cout<<"Error: Literals can not be evaluated"<<endl;
				return;
			}
			else{
			    states.push_front(s);
			    continue;
			}
		}
		//cout<<"Fire a random selection rules and generate children of s "<<endl;
		itr_map=possibleOutcome.begin();
		while(itr_map!=possibleOutcome.end()){
            //cout<<"literal id "<<itr_map->first<<endl;
			if(s->aval[itr_map->first]<UNKNOWN){
				++itr_map;
				continue;
			}
			State* ns=GetNewState(s);
			//cout<<(itr_map->second)<<endl;
			ns->prob=ns->prob*(itr_map->second);
            //cout<<debug_level<<endl;
			if(ns->Close(itr_map->first, TRUE)) states.push_front(ns);
			else{ //Discard inconsistent ones
                if(debug_level==112){
                    cout<<"FALSE STATE"<<endl;                
                    ns->Show(true, true, true);
                }
			    RemoveState(ns);
			    
			}
			++itr_map;
		}
		RemoveState(s);
	}
	//if(qry->GetType()==3) CollectFormula_1();
	//else if(qry->GetType()==2) CollectFormula_2();
	cout<<"Partial Answer Set Size "<<ans.size()<<endl;
    
	states.clear();
	int i;
	if(TOTAL==0.0) return;
	list<State*>::iterator itr_st;
	itr_st=ans.begin();
	while(itr_st!=ans.end()){
        //(*itr_st)->Show(true,true,true);
        //cin>>i;
		(*itr_st)->prob=(*itr_st)->prob/TOTAL;
		++itr_st;
	}  
	//end=clock();
	//cout<<"Answer Sets computed and its duration:"<<((double)end-(double)start)/CLOCKS_PER_SEC<<endl;
	if(qry->GetType()==1) Query_1();
	else if(qry->GetType()==2) Query_2();
	else if(qry->GetType()==3) Query_3();
    end=clock();
    cout<<"Answer Sets computed and its duration:"<<((double)end-(double)start)/CLOCKS_PER_SEC<<endl;
}

void pgEngine::Query_1()
{
	// Ending here for computer answer sets
	//clock_t start=clock();
	map<int, double> possibleOutcome;
	map<int,double>::iterator itr_map;

	list<Formula*> lstFormula(qry->formula);
	list<Formula*>::iterator itr_fml;
	list<State*>::iterator itr_st;

	double MIN=0.0;
	State* s;
	int status;
    if(debug_level==140) cout<<"partial answer size: "<<ans.size()<<endl;
   
	itr_fml=lstFormula.begin();
	while(itr_fml!=lstFormula.end()){
		SetFormulaId(*itr_fml); //?
        set<Literal*> litSet;
        (*itr_fml)->CollectLiteral(litSet);
        BuildRandomDependant(litSet);
		itr_st=ans.begin();
		while(itr_st!=ans.end()){
			//int i;
			//(*itr_st)->Show(true, true, true);
			//cin>>i;
            State* ns;
            ns=GetNewState(*itr_st);
			states.push_back(ns);
			++itr_st;
		}  
		/*
	        //(*itr_st)->Show(true, true, true);
		int i;
		//cin>>i;
		itr_fml=lstFormula.begin();
		while(itr_fml!=lstFormula.end()){
			(*itr_fml)->SetValid(true);
			++itr_fml;
		}*/
		//Expand the answer set till it knows all the formula
		//states.push_front(*itr_st);
        if(debug_level==140){
            (*itr_fml)->Show();
        }
  	    while(!states.empty()){
			s=states.front();
			states.pop_front();
			//Check whether all the formula are known
			//itr_fml=lstFormula.begin();
			//expand=false;
			//while(itr_fml!=lstFormula.end()){
			//	if((*itr_fml)->GetValid()==true){//This formula is not known yet
			status=s->EvaluateFormula(*itr_fml); //TRUE , UNKNOWN, FALSE
            if(debug_level==140) cout<<"status "<<status<<endl;
                
			//else status=(*itr_fml)->Evaluate(s->pos);
			if(status==TRUE){ //This formula is true w.r.t. the state, update the minimal
				//(*itr_fml)->SetValid(false);
				//cout<<"True: "<<s->prob<<endl;
				//int i;
				//s->Show(true,true, true);
				//cin>>i;
				(*itr_fml)->UpdateProbability(s->prob, true);
				if(MIN<(*itr_fml)->GetMin()) MIN=(*itr_fml)->GetMin();
				//Calculate 
			}
			else if(status==FALSE){ //This formula is false w.r.t. the state, update the max
				//(*itr_fml)->SetValid(false);
				//cout<<"False: "<<s->prob<<endl;
				
				(*itr_fml)->UpdateProbability(s->prob, false);
			        //Calculate
			}
			else if(status==UNKNOWN){//this formula is not known, we need further expand the state
                if(debug_level==125){
                    s->Show(true,false,true);
                    int i;
                    cin>>i;
                }
				if(!FireRandomRule(s, possibleOutcome)){
                    if(debug_level==125){
                        s->Show(false,false,true);
                        int i; 
                        cin>>i;
                    }
					if(s->GetUpped() || !s->UpClosure()){
                        s->Show(false,false,true);
                        (*itr_fml)->Show();
						cout<<"Error: Literals can not be evaluated"<<endl;
						return;
					}
					else states.push_front(s);
                    //int i;
        		    //s->Show(true,true,true);
                    //cin>>i;
					continue;
				}				
                
				itr_map=possibleOutcome.begin();
				while(itr_map!=possibleOutcome.end()){
					State* ns=GetNewState(s);
					ns->prob=ns->prob*(itr_map->second);
					//cntClose++;
					if(ns->Close(itr_map->first, TRUE)) states.push_back(ns);
					else {
						cout<<"Error: Unexpeced Inconsistent Possible World"<<endl;
						return;
					}
					//ns->Show(true,true,true);
					//cin>>i;
					//cout<<"bond"<<endl;
					++itr_map;
				}
				
				//if(MIN>(*itr_fml)->GetMax()) lstFormula.erase(itr_fml); //Delete this formula, if max < min
				//else ++itr_fml;
				//++itr_fml;
			}
		}
		++itr_fml;
	}
	
	//cout<<"Count Closure: "<<State::cntClose<<endl;
	//cout<<"Count atomos"<<(double)State::clkAtMost/CLOCKS_PER_SEC<<endl;
    qry->GetMaximunFormula();
    qry->ShowAnswer(); 
	
	//cout<<lstFormula.size()<<endl;
    /*
	itr_fml=lstFormula.begin();
	while(itr_fml!=lstFormula.end()){
		(*itr_fml)->Show();
		//cout<<" "<<(*itr_fml)->GetMin()<<" "<<(*itr_fml)->GetMax()<<endl;
		++itr_fml;
	}*/
	//clock_t end=clock();
	//cout<<"Formulas are evaluated and running time is :"<<((double)end-(double)start)/CLOCKS_PER_SEC<<endl;
}

void pgEngine::Query_2()
{
    double MIN=0;
    double MAX=1;    

    clock_t start=clock();
    map<int, double> possibleOutcome;
    map<int,double>::iterator itr_map;

    if(debug_level==120) cout<<"In Query 2"<<endl;
    stage=false;

    //list<Formula*> lstFormula;
    list<string>::iterator itr_term;
    itr_term=qry->terms.begin();
    list<GroundTerm*> grdTerm;
    while(itr_term!=qry->terms.end()){
        if(debug_level==120) cout<<gnd->gndTerm[(*itr_term)]->GetName();
        grdTerm.push_back(gnd->gndTerm[(*itr_term)]);
        ++itr_term;
    }
    list<State*>::iterator itr_st;
    State* s;
    int status;
	itr_st=ans.begin();

	while(itr_st!=ans.end()){
		//int i;
		//(*itr_st)->Show(true, true, true);
		//cin>>i;
		states.push_back(*itr_st);
		++itr_st;
	}  
		
	//Expand the answer set till it knows all the formula
    //states.push_front(*itr_st);
    Formula* fml;
    list<Formula*>::iterator itr_fml;
    while(!states.empty()){
	    s=states.front();
	    states.pop_front();
	    Formula* f=new Formula();
        status=s->KnowTerm(grdTerm, f);   //TRUE , UNKNOWN, FALSE
		//if(fml!=NULL) fml->Show();
		
	    if(status==TRUE){ //This formula is true w.r.t. the state, update the minimal
		//(*itr_fml)->SetValid(false);
		//cout<<"True: "<<s->prob<<endl;
		 //int i;
		    //s->Show(true,true, true);
		    //cin>>i;
                //fml->UpdateProbability(s->prob, true);
                //if(MIN<fml->GetMin()){
                //MIN=fml->GetMin();
	        bool flag=false;
            itr_fml=qry->formula.begin();
            while(itr_fml!=qry->formula.end()){
		        if(debug_level==120) (*itr_fml)->Show();
                if(!(f->IsSubset(*itr_fml)==1)){
                    (*itr_fml)->UpdateProbability(s->prob,false);
                    if((*itr_fml)->GetMax()<MIN) itr_fml=qry->formula.erase(itr_fml);
                    else ++itr_fml;
                }
                else{
                    flag=true;
                    (*itr_fml)->UpdateProbability(s->prob, true);
                    if(MIN<(*itr_fml)->GetMin()) MIN=(*itr_fml)->GetMin();
                    ++itr_fml;
                }
		  
            }
            if(flag==false){
               f->UpdateProbability(1-MAX, false);
               f->UpdateProbability(s->prob, true);
               qry->formula.push_back(f);
            }
	        MAX=MAX-s->prob;
	       //Calculate 
	    }
	    else if(status==FALSE){ //This formula is false w.r.t. the state, update the max
		    //Update the upper bound of exsiting formula, update the gloable upper bound
		   delete f;
                //(*itr_fml)->UpdateProbability(s->prob, false);
           itr_fml=qry->formula.begin();
           while(itr_fml!=qry->formula.end()){
               (*itr_fml)->UpdateProbability(s->prob,false);
               if((*itr_fml)->GetMax()<MIN) itr_fml=qry->formula.erase(itr_fml);
               else ++itr_fml;
           }
	       MAX=MAX-s->prob;
	       //cout<<"shoul not in here"<<endl;
           //Calculate
	    }
	    else if(status==UNKNOWN){//this formula is not known, we need further expand the state
		    delete f;
		    if(!FireRandomRule(s, possibleOutcome)){
		        if(s->GetUpped() || !s->UpClosure()){
                    cout<<"Error: Literals can not be evaluated"<<endl;
			        return;
		        }
		        else states.push_front(s);
		        continue;
		    }				
		
	        itr_map=possibleOutcome.begin();
	        while(itr_map!=possibleOutcome.end()){
		        State* ns=GetNewState(s);
		        ns->prob=ns->prob*(itr_map->second);
		    //cntClose++;
		        if(ns->Close(itr_map->first, TRUE)) states.push_back(ns);
		        else {
			        cout<<"Error: Unexpeced Inconsistent Possible World"<<endl;
			        return;
		        }
		        if(debug_level==120){
                    ns->Show(true,false,true);
                    int i;
		            cin>>i;
                }
		        //cout<<"bond"<<endl;
		        ++itr_map;
	        }
        }
   } 
   qry->GetMaximunFormula();
   qry->ShowAnswer(); 
   /*  
   itr_fml=lstFormula.begin();
   while(itr_fml!=lstFormula.end()){
	    (*itr_fml)->Show();
	    //cout<<" "<<(*itr_fml)->GetMin()<<" "<<(*itr_fml)->GetMax()<<endl;
	    ++itr_fml;
   }*/
   //cout<<"MAX "<<MAX<<endl;
}

void pgEngine::Query_3()
{

    map<int, double> possibleOutcome;
    map<int,double>::iterator itr_map;
    list<State*>::iterator itr_st;
    list<State*> stkState1;
    list<int> gndLiteralId;
    list<Literal*>::iterator itr_qry;
    map<string, GroundLiteral*>::iterator itr_gl;
    stage=false; //all rules in programs can be considered
    itr_qry=qry->atoms.begin();
    while(itr_qry!=qry->atoms.end()){
        itr_gl=gnd->gndLiteral.find((*itr_qry)->GetName());
        if(itr_gl!=gnd->gndLiteral.end()) gndLiteralId.push_back(itr_gl->second->GetId());
        ++itr_qry;
    }
    if(debug_level==150) cout<<"Answer set size "<<ans.size()<<endl;    
    itr_st=ans.begin();
    while(itr_st!=ans.end()){
        Formula *f=new Formula();
        if((*itr_st)->KnownLiteral(gndLiteralId,f)){
            if(debug_level==150) cout<<"Check A"<<endl;
            qry->AddFormula(f);
        }
        else{
           if(!qry->IsSuper(f)){
                if(debug_level==150) cout<<"Check B"<<endl;
                State* ns;
                ns=GetNewState(*itr_st);
                AddState(ns, stkState1);
           }
           delete f;
        }
        ++itr_st;
    }
    //itr_st=stkState1.begin();
    while(!stkState1.empty()){
        State *s=stkState1.front();
        stkState1.pop_front();
        //If s has more literals than a known formula, then discard it.
        Formula *f=new Formula();
        if(s->KnownLiteral(gndLiteralId,f)){
            if(debug_level==150) s->Show(false,false,true);
            qry->AddFormula(f);
            if(debug_level==150){
                f->Show();
                int i;
                cin>>i;
            }
            continue;
        }
        else{
            if(debug_level==150){
                //ns->Show(false, false, true);
                int i;
                //cin>>i;
            }
            if(qry->IsSuper(f)) continue;
            delete f;
        }

        while(!FireRandomRule(s, possibleOutcome)){
	        if(s->GetUpped() || !s->UpClosure()){
                //s->Show(true,true,true);
   	            cout<<"Error: Literals can not be evaluated"<<endl;
                if(debug_level==150) s->Show(false, false, true);
		        return;
	        }
	    }	
        if(debug_level==150) cout<<"Check C"<<endl;			
		
        itr_map=possibleOutcome.begin();
        while(itr_map!=possibleOutcome.end()){
	        State* ns=GetNewState(s);
	        //ns->prob=ns->prob*(itr_map->second);
	        //cntClose++;
	        if(ns->Close(itr_map->first, TRUE)){
                Formula *f=new Formula();
                ns->KnownLiteral(gndLiteralId,f);
                AddState(ns, stkState1);
                delete f;
            }
	        else {
		        cout<<"Error: Unexpeced Inconsistent Possible World"<<endl;
		        return;

	        }
	        ++itr_map;
        }
                                                                                                                                                                                      
    }
    if(debug_level==150){
        cout<<"Check D"<<endl;
        qry->Show();
        int j;
        cin>>j;
    }
    stage=true; //dependant set rules only
    
    Query_1();
}

bool pgEngine::FireRandomRule(State* s, map<int,double>& po)
{
    map<string,RandomRule*>::iterator itr_rnd;
	po.clear();
	//if(debug_level==120) cout<<"randrule "<<gnd->rndRule.size()<<endl;
    itr_rnd=gnd->rndRule.begin();
    while(itr_rnd!=gnd->rndRule.end()){
        //Ready to fire
	    if(s->firedRndRule.find(itr_rnd->first)!=s->firedRndRule.end()){
		    ++itr_rnd;
		    continue;
	    }
	    //cout<<"check "<<endl;
	    GroundRule *gr=itr_rnd->second->GetRandomRule();
	    //if(gr==NULL) cout<<"checked here"<<endl;
	    //else gr->Show();
        if(stage==true && rndDependant.find(itr_rnd->first)==rndDependant.end()){
            if(debug_level==120) cout<<"stage is true"<<endl;
            ++itr_rnd;
            continue;
        }
	    if(s->Satisify(itr_rnd->second->GetRandomRule()->ReturnBody(true) , true)==TRUE
                && s->Satisify(itr_rnd->second->GetRandomRule()->ReturnBody(false) , false)==TRUE
			    && s->Known(itr_rnd->second->GetRange())){
               if(debug_level==120) cout<<"Ready to Fire "<<itr_rnd->first<<" "<<endl;
            vector<GroundRule*>::iterator itr_pr;
            itr_pr=itr_rnd->second->GetPrRule().begin();
            while(itr_pr!=itr_rnd->second->GetPrRule().end()){
                if(s->Known((*itr_pr)->ReturnBody(true))==true
                      && s->Known((*itr_pr)->ReturnBody(false))==true)
                      ++itr_pr;
                else break;
            }
            if(itr_pr!=itr_rnd->second->GetPrRule().end()){
		        //cout<<itr_rnd->first<<" ";
		        itr_rnd++;
		        continue;
            }
            
            //Find the rules that is ready to fire
            s->firedRndRule.insert(itr_rnd->first);
            //Possible outcome
            vector<GroundLiteral*>::iterator itr_glit;
            size_t size=itr_rnd->second->GetHeadSize();
            for(size_t idx=0;idx<size;idx++){
                GroundLiteral* glit=itr_rnd->second->GetHeadLiteral(idx);
		        GroundLiteral* gl=itr_rnd->second->GetRangeLiteral(idx);
		        if(gl==NULL || s->aval[gl->GetId()]==TRUE)
                    po[glit->GetId()]=-1; //Inital value less than 0
            }
             //PA probability
            int pa_num=0;
            double pa_val=0;
            //cout<<"size :"<<itr_rnd->second->GetPrRule().size()<<endl;
            itr_pr=itr_rnd->second->GetPrRule().begin();
            while(itr_pr!=itr_rnd->second->GetPrRule().end()){
                if(s->Satisify((*itr_pr)->ReturnBody(true),true)==TRUE
                  && s->Satisify((*itr_pr)->ReturnBody(false),false)==TRUE){
                    if(po.find((*itr_pr)->GetHead()->GetId())!=po.end()){
                        pa_val+=(*itr_pr)->GetProbability();
	                    po[(*itr_pr)->GetHead()->GetId()]=(*itr_pr)->GetProbability();
	                    //cout<<(*itr_pr)->GetHead()->GetName()<<" "<<(*itr_pr)->GetProbability()<<endl;
                        pa_num++;
	                    //cout<<" "<<pa_val<<" "<<pa_num<<endl;
                    }
                }
                ++itr_pr;
            }
           //Pd probability
            //cout<<" "<<pa_val<<" "<<pa_num<<endl;
           double pd_val=(1-pa_val)/(po.size()-pa_num);
           //cout<<pd_val<<" "<<pa_val<<" "<<pa_num<<po.size()<<endl;
           map<int,double>::iterator itr_map;
           itr_map=po.begin();
           while(itr_map!=po.end()){
	           //cout<<gnd->gLit[itr_map->first]->GetName()<<" "<<itr_map->second<<" | ";
               if((*itr_map).second<0) itr_map->second=pd_val;
	           //cout<<gnd->gLit[itr_map->first]->GetName()<<" "<<itr_map->second<<" | ";
               ++itr_map;
           }
	       //cout<<endl;
           return true;
        }
        ++itr_rnd;
    }
    return false;
}
            
State* pgEngine::GetNewState(State *s)
{
	State* ns;
	if(statePool.empty()) return new State(s);
	else{
		ns=statePool.back();
		statePool.pop_back();
		ns->Copy(s);
		return ns;
	}
}

void pgEngine::RemoveState(State *s)
{
	statePool.push_back(s);
}

void pgEngine::SetFormulaId(Formula *f)
{
    //(*itr_fml)->CollectAtom(fmlLiteral);
    Literal *l;
    l=f->GetLiteral();
    if(l!=NULL){
        GroundLiteral *gl=gnd->GetLiteral(l);
        l->SetId(gl->GetId());
    }
    else if(f->GetOperation()==""){
        set<Literal*>::iterator itr;
        itr=f->GetASet().begin();
		while(itr!=f->GetASet().end()){
            GroundLiteral *gl=gnd->GetLiteral(*itr);
            (*itr)->SetId(gl->GetId());
			++itr;
		}
    }
    else{
        if(f->GetFirstFormula()!=NULL) SetFormulaId(f->GetFirstFormula());
        if(f->GetSecondFormula()!=NULL) SetFormulaId(f->GetSecondFormula());
    }
}

void pgEngine::AddState(State* s, list<State*>& lstState)
{
    list<State*>::iterator itr_st;
    itr_st=lstState.begin();
    while(itr_st!=lstState.end()){
        if(s->rank>(*itr_st)->rank) ++itr_st;
        else{
            lstState.insert(itr_st, s);
            return;
        }
    }
    lstState.push_back(s);
}

void pgEngine::BuildRandomDependant(set<Literal*>& litSet)
{
 
    set<Literal*>::iterator itr_lit;
    set<GroundTerm*> dependantSet;
    itr_lit=litSet.begin();
    while(itr_lit!=litSet.end()){
        grounder->DependantSet(gnd->GetLiteral(*itr_lit)->GetTerm(), dependantSet);
        ++itr_lit;
    }
    rndDependant.clear();
    set<GroundTerm*>::iterator itr_dep;
    itr_dep=dependantSet.begin();
    while(itr_dep!=dependantSet.end()){
        (*itr_dep)->CollectRandomRule(rndDependant);
        ++itr_dep;    
    }
    if(debug_level==160){
        cout<<"debuging"<<endl;
        set<string>::iterator itr_str;
        itr_str=rndDependant.begin();
        while(itr_str!=rndDependant.end()){
            cout<<(*itr_str)<<" ";
            ++itr_str;
        }
        cout<<endl;
    }
}
        
