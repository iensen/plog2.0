#include "global.h"
#include <cctype>
#include <sstream>
#include <iostream>

using namespace std;

//enum  TermType {identifier, num, oprt, var, sym, invalid};

bool IsOperator(string s)
{
	if(s=="lt" || s=="gt" || s=="ge" || s=="le"
			|| s=="eq" || s=="neq") return true;
    if(s=="plus" || s=="minus" || s=="times" || s=="div" || s=="mod")
    return true;
	return false;
}

//Return a term type of an term in the atom
TermType GetTermType(string s)
{
    if(IsOperator(s)) return oprt;
    else if(s.size()>0){
		if(s[0]=='#') return var; //special variables
        if(isalpha(s[0])|| s[0]=='_'){
            if(isupper(s[0])) return var;
            else return identifier;
        }
        else if(isdigit(s[0])) return num;
        else if(s[0]=='(' || s[0]==')' || s[0]==',' || s[0]=='=') return sym;
        else return invalid;
    }
	else return invalid;
}

vector<string> BreakTerm(string s)
{
    vector<string> vct;
    size_t sz=s.size();
    int lev=0;
    size_t j=0;
    for(size_t idx=0; idx<sz;idx++){
        if(s[idx]=='('){
            if(lev==0){vct.push_back(s.substr(j,idx-j)); j=-1;}
            lev++;
        }
        else if(s[idx]==','){
            if(lev==1){vct.push_back(s.substr(j,idx-j)); j=-1;}
        }
        else if(s[idx]==')'){
           if(lev==1){vct.push_back(s.substr(j,idx-j)); j=-1;}
           lev--;
        }
        else{
            if(j==-1) j=idx;
        }
    }
    if(j==0) vct.push_back(s);
    return vct;
}

list<string> NextElement(string s)
{
    bool st=true;
    int i;
    int start=0;
    list<string> lstElement;
    for(i=0;i<s.size();i++){
        if(st==true){
           if(s[i]=='(' || s[i]==')' || s[i]==',' || s[i]=='='){
                lstElement.push_back(s.substr(start,i-start));
                lstElement.push_back(s.substr(i,1));
                st=false;
           }
        }
        else{
            if(!(s[i]=='(' || s[i]==')' || s[i]==',' || s[i]=='=')){
                start=i;
                st=true;
           }
           else{
                lstElement.push_back(s.substr(i,1));
           }
        }
    }
    if(st==true) lstElement.push_back(s.substr(start, i-start));
    //if(lstElement.empty()) lstElement.push_back(s);
    return lstElement;
}

string Calculate(string op1,string op2,string op)
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



string ReplaceExp(string s, list<string>& exp)
{
    static int i=1;    
    string x;
    list<string> lstStr;
    vector<string> vct=BreakTerm(s);
   if(vct.size()==1) return vct[0];
   if(GetTermType(vct[0])==oprt){
        vector<string>::iterator itr=vct.begin();
        x=(*itr)+"(";
        ++itr;
        while(itr!=vct.end()){
            x+=(*itr)+",";
            ++itr;
        }
        x[x.length()-1]=')';
        stringstream ss;
        ss<<exp.size();
        x="eq(#"+ss.str()+","+x+")";     
        exp.push_back(x);
        return "#"+ss.str();
    }
    else{
        vector<string>::iterator itr=vct.begin();
        x=(*itr)+"(";
        ++itr;
        while(itr!=vct.end()){
            x+=ReplaceExp(*itr, exp)+",";
            ++itr;
        }
        x[x.length()-1]=')';
        return x;
     }
}

string Evaluate(string in)
{
	string x;
    vector<string> vct=BreakTerm(in);
    //cout<<vct.size()<<endl;
    if(vct.size()==1) return vct[0];
    else if(vct.size()==3 && GetTermType(vct[0])==oprt){
        string s1=Evaluate(vct[1]);
        string s2=Evaluate(vct[2]);
        //cout<<vct[0]<<" "<<s1<<" "<<s2<<endl;
        return Calculate(s1, s2,vct[0]);
    }
    else{
        vector<string>::iterator itr=vct.begin();
        x=(*itr)+"(";
        ++itr;
        while(itr!=vct.end()){
            x+=Evaluate(*itr)+",";
            ++itr;
        }
        x[x.length()-1]=')';
        return x;
    }
}

string Replace(string in, map<string, string> vars)
{
    string result;
    list<string> lstStr=NextElement(in);
    list<string>::iterator itr;
    itr=lstStr.begin();
    while(itr!=lstStr.end()){
        //cout<<*itr<<endl;
        if(GetTermType(*itr)==var){
            result+=vars[*itr];
        }
        else result+=(*itr);
        //cout<<result<<endl;
        ++itr;
    }
    return result;
}

string GetRoot(string s)
{
    size_t sz=s.size();
    size_t idx;
    for(idx=0;idx<sz;idx++){
        if(s[idx]=='(') break;
    }
    return s.substr(0, idx);
}



//Return the index to the last of 
int SubTree(int i, std::string target)
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

double ComputeProbability(std::string s, map< string, string> assignment)
{
    string v=Evaluate(Replace(s, assignment));
    stringstream ss;
    ss<<v;
    double dv;
    ss>>dv;
    return dv;
}

void SubstractSet(set<string>& s1, set<string>& s2, set<string>& s3)
{
    set<string>::iterator itr_1;
    s3.clear();
    itr_1=s1.begin();
    while(itr_1!=s1.end()){
        if(s2.find(*itr_1)==s2.end()) s3.insert(*itr_1);
        ++itr_1;
    }
    
}

string GetPart(string in, int i)
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

std::string GetLastPart(std::string in)
{
    vector<string> v=BreakTerm(in);
    if(!v.empty()) return v.back();
    else return "";
}

std::string GetTerm(std::string l)
{
    size_t found=l.find("=");
    if(found==string::npos) return l;
    else return l.substr(0, found);
}

