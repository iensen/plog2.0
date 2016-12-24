#include "TermTree.h"
#include <stack>
#include <cctype>
#include <sstream>
#include <iostream>

using namespace std;

//Constructed by a single symbol
TermTree::TermTree(string s)
{
    term.push_back(s);
    parent.push_back(-1); //This the root
    size=1; //Single node Termtree
}

//Add a root symbol s and its children, represented by child
TermTree::TermTree(std::string s, std::list<TermTree*> child)
{
    TermTree* t;
	//Construct the root node
    term.push_back(s);
    parent.push_back(-1); //This the root
	
    list<TermTree*>::iterator itr;
    itr=child.begin();
    int relativePosition=1;
    while(itr!=child.end()){
        t=(*itr);
        size=t->term.size(); 
        if(size!=0){
            term.push_back(t->term[0]);
            parent.push_back(relativePosition); //its parent is the root
            relativePosition+=size; //Get relative position of this new added node
            //for the children of this new added node,adjust their parent position relationship
            for(size_t i=1;i<size;i++){
                term.push_back(t->term[i]);
                parent.push_back(t->parent[i]);
            }
        }
        ++itr;
    }
    size=term.size(); 
}

TermTree::TermTree(TermTree *t, size_t idx)
{
	int parentPosition=t->GetParentPos(idx);
	size_t sz=t->GetSize();
	size_t j=idx;
	do{
		term.push_back(t->GetName(j));
		parent.push_back(t->GetPosition(j));
		j++;
	}while(t->GetParentPos(j)< parentPosition && j<sz);
	size=term.size();
	parent[0]=-1;
	
}

TermTree::TermTree(TermTree *t)
{
	size=t->GetSize();
	size_t idx;
	for(idx=0;idx<size;idx++){
		term.push_back(t->GetName(idx));
		parent.push_back(t->GetPosition(idx));
	}
	
}
/*
TermTree::TermTree(TermTree *t, std::map<std::string, std::string> value)
{
	size=t->GetSize();
	size_t idx;
	string sName;
	TermType tt;
	for(idx=0;idx<size;idx++){
		term.push_back(t->GetName(idx));
		parent.push_back(t->GetPosition(idx));
	}
	for(idx=0; idx<size;idx++)
	{
		tt=GetType(idx);
		if(tt==oprt){
			TermTree *t1=new TermTree(this,idx);
			//cout<<"operator "<<t1->GetName()<<endl; 
			sName=t1->Evaluate(value);
			//cout<<"Result "<<sName<<" "<<idx<<endl; 
			size=Replace(idx,sName);
			//cout<<GetName()<<endl;
			delete t1;
		}
		else if(tt==var){
			term[idx]=value[term[idx]];
		}
	}
	//cout<<GetName()<<
}
*/


//destructor
TermTree::~TermTree(void)
{
}

/*
   std::string GetRoot();
	std::string GetName(int idx);
	int GetParentPos(int idx);
	TermType GetType(int idx);

    //Append a list of subtree as the child of the node indicated by idx
    void Append(int idx, std::list<TermTree&> chld); 

*/
string TermTree::GetRoot()
{
    return term[0];

}

string TermTree::GetName(size_t idx)
{
    if(idx>=0 && idx<size) return term[idx];
    else return "";
}

int TermTree::GetParentPos(size_t idx)
{
    if(idx>0 && idx<size){
        return idx-parent[idx];
    }
    else return -1; //Error 
}

int TermTree::GetPosition(size_t idx)
{
	if(idx>=0 && idx<size){
		return parent[idx];
	}
	else return -1;
}

int TermTree::GetHeight(size_t idx)
{
    int i=0;
    while(parent[idx]!=-1){
        idx=idx-parent[idx];
        i++;
    }
    return i;
}

size_t TermTree::GetSize()
{
	return size;
}


string TermTree::GetName()
{
    size_t i=1;
    string result=term[0];
    for(i=1;i<=size;i++){
        if(i==size){//Last element

            string s1(GetHeight(i-1),')');
            result=result+s1;
        }
        else if(i-parent[i] == i-1-parent[i-1] && i-1!=0){//Lookforwad, next node is the sibling
            result=result+","+term[i];
        }
        else if(parent[i]==1){//Lookforward, next node is this node's child
            result=result+"("+term[i];
        }
        else{//Next node is on the branch, get the common parent
            string s1(GetHeight(i-1)-GetHeight(i),')'); 
            result=result+s1+","+term[i];
        }
    }
	return result;
}

void TermTree::Append(TermTree* t)
{
	size_t sz,i;
	sz=t->GetSize();
	int j;
	string s;
	for(i=0;i<sz;i++){
		j=t->GetPosition(i);
		s=t->GetName(i);
		term.push_back(s);
		if(i==0) parent.push_back(size);
		else parent.push_back(j);
	}
	size+=t->GetSize();
}

/*
TermType TermTree::GetType(size_t idx)
{
    if(idx>=0 && idx<size){
        string s=term[idx];
	if(IsOperator(s)) return oprt;
        else if(s.size()>0){
			if(s[0]=='#') return var; //special variables
            if(isalpha(s[0])|| s[0]=='_'){
                if(isupper(s[0])) return var;
                else return id;
            }
            else if(isdigit(s[0])) return num;
            else return invalid;
        }
		else return invalid;
    }
    else return invalid;
}
*/






/*
void TermTree::CollectVariable(std::set<std::string>& addin)
{
	size_t i;
	for(i=0;i<size;i++){
		if(GetType(i)==var){
			addin.insert(term[i]);
		}
	}
}

void TermTree::CollectVariable(std::set<std::string>& addin, std::set<std::string>& notin)
{
	size_t i;
	for(i=0;i<size;i++){
		if(GetType(i)==var){
			if(notin.find(term[i])==notin.end()) addin.insert(term[i]);
		}
	}
}


size_t TermTree::Replace(size_t idx, std::string s)
{
	//cout<<idx<<" "<<size<<endl;	
	if(idx>=size || idx<0 ) return size; //Out of range
	vector<int>::iterator itr1=parent.begin();
	vector<string>::iterator itr2=term.begin();
	size_t i=0;
	size_t j=0;
	bool flag=false;
	int parentPosition=GetParentPos(idx);
	term[idx]=s;
	for(i=idx+1; i<size;i++){
		if(GetParentPos(i)==parentPosition){
			j=i;
			break;
		}
	}
	//cout<<term[idx]<<" "<<idx<<" "<<size<<" "<<j<<endl;	
	if(j!=0){
		for(i=0;i<size-j;i++){
			term[idx+1+i]=term[j+i];
			if(GetParentPos(i+j)==parentPosition)
				parent[idx+1+i]=idx+1+i-parentPosition;
			else parent[idx+1+i]=parent[i+j];
		}
		size=idx+i+1;
	}
	else size=idx+1;
	return size;
}
*/
//Append a list of subtree as the child of the node indicated by idx
/*
bool TermTree::Append(int idx, std::list<TermTree&> chld)
{
    if(idx<0 || idx>=size) return false;
    

    return true;
}
*/

/*
string TermTree::Evaluate(map<string, string>& value)
{
	stack<string> stk;
	string x;
	int counter=0;
	//cout<<size<<endl;
	for(size_t idx=0; idx<size; idx++){
		x=GetName(idx);
		//cout<<idx<<" "<<x<<endl;
		if(GetType(idx)==oprt){
			//cout<<"oprt"<<" "<<x<<endl;
			stk.push(x);
		}
		else{
			if(GetType(idx)==var) x=value[x]; //use its assignment
			//cout<<"op"<<" "<<x<<endl;
			while(!stk.empty() && !IsOperator(stk.top())){
				string op2=x;
				string op1=stk.top();
				stk.pop();
				string op=stk.top();
				stk.pop();
				x=Calculate(op1,op2,op);
			}
			stk.push(x);
		};
	}
	return stk.top();
}

bool TermTree::IsOperator(string s)
{
	if(s=="lt" || s=="gt" || s=="ge" || s=="le"
			|| s=="eq" || s=="neq") return true;
    if(s=="plus" || s=="minus" || s=="times" || s=="div" || s=="mod")
    return true;
	return false;
}

string TermTree::Calculate(string op1,string op2,string op)
{
	int i1, i2;
	stringstream s1(op1);
	stringstream s2(op2);
	s1>>i1;
	s2>>i2;
	stringstream s;
	//cout<<op<<" "<<op1<<" "<<op2<<endl;
	if(op=="plus"){
		s<<i1+i2;
	}
	else if(op=="minus"){
		s<<i1-i2;
	}
	else if(op=="times"){
		s<<i1*i2;
	}
	else if(op=="div"){
		if(i2!=0) s<<(double)i1/(double)i2;
	}
	else if(op=="eq"){
		if(isdigit(op1[0]) && isdigit(op2[0])){
			if(i1==i2) s<<"true";
			else s<<"false";
		}
		else{
			if(s1.str()==s2.str()) s<<"true";
			else s<<"false";
		}
	}
	else if(op=="le"){
		if(isdigit(op1[0]) && isdigit(op2[0])){
			if(i1<=i2) s<<"true";
			else s<<"false";
		}
		else{
			if(s1.str()<=s2.str()) s<<"true";
			else s<<"false";
		}
	}
	else if(op=="ge"){
		if(isdigit(op1[0]) && isdigit(op2[0])){
			if(i1>=i2) s<<"true";
			else s<<"false";
		}
		else{
			if(s1.str()>=s2.str()) s<<"true";
			else s<<"false";
		}
	}
	else if(op=="lt"){
		if(isdigit(op1[0]) && isdigit(op2[0])){
			if(i1<i2) s<<"true";
			else s<<"false";
		}
		else{
			if(s1.str()<s2.str()) s<<"true";
			else s<<"false";
		}
	}
	else if(op=="gt"){
		if(isdigit(op1[0]) && isdigit(op2[0])){
			if(i1>i2) s<<"true";
			else s<<"false";
		}
		else{
			if(s1.str()>s2.str()) s<<"true";
			else s<<"false";
		}
	}
	else if(op=="neq"){
		if(isdigit(op1[0]) && isdigit(op2[0])){
			if(i1!=i2) s<<"true";
			else s<<"false";
		}
		else{
			if(s1.str()!=s2.str()) s<<"true";
			else s<<"false";
		}
	}
	return s.str();
}
*/
