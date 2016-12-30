#include <string>
#include <iostream>
#include "Parse.h"
#include "Program.h"
#include "Query.h"
#include "global.h"
#include "Grounder.h" //temporay
#include "TrEngine.h"  
#include "pgEngine.h"

#include <stdlib.h>

#include <list>




using namespace std;

int main(int argc, char **argv)
{
    int i=0;
    int debug_level=0;
    list<string> fileNames;
    int mode=0;
    for(i=1;i<argc;i++){
        string para=argv[i];
        if(para=="-p" && mode==0){
            mode=2;
            for(int j=i+1; j<argc; j++){
                para=argv[j];
                if(para[0]!='-'){
                    fileNames.push_back(argv[j]);
                 }
                else break;
            }
        }
        else if(para=="-t" && mode==0){
            mode=1;
            for(int j=i+1; j<argc; j++){
                para=argv[j];
                if(para[0]!='-'){
                    fileNames.push_back(argv[j]);
                 }
                else break;
            }
        }
        else if(para=="-d"){
            debug_level=atoi(argv[i+1]);
            i++;
        }
    }    
    if(debug_level==10){//Only Show command parsing
        list<string>::iterator itr;
        itr=fileNames.begin();  
        while(itr!=fileNames.end()){
            cout<<*itr<<endl;
            itr++;
        }
        return debug_level;
    }

    Program *p=new Program();
    Query *q=new Query();
    CParse *parse=new CParse(p, q);
    list<string>::iterator itr;
    itr=fileNames.begin();
    while(itr!=fileNames.end()){
        bool iresult=parse->SyntaxAnalysis(*itr);
        if(iresult==0) return -1;
        if(debug_level==20){
            cout<<*itr<<endl;
            p->Show();
            return debug_level;
        }
        ++itr;
    }
    if(mode==1){
	    TrEngine *tr;	
	    //s->Show();
	    //p->Show();
	    //gnd->Show();
	    tr=new TrEngine(p,q,"lp");
	    tr->Solve();
	    //cout<<tr->GetOutput();
    }
    else if(mode==2){
	    //cout<<"here"<<endl;
	    //p->Show();
	    pgEngine *pg=new pgEngine(p,q);
        pg->SetDebugLevel(debug_level);
	    pg->Run();
	    //GroundProgram* gnd=new GroundProgram();
	    //Grounder *gnder=new Grounder(gnd, p, q);
	    //gnder->Preprocessing();
	    //gnder->Ground("singlepair");
	    //p->Show();
	    //gnd->Show();
   }
   return 0;
}
