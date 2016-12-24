#include "Variable.h"
#include <iostream>
#include <sstream>

using namespace std;

Variable::Variable(void)
{
}

Variable::Variable(string s, string st):name(s),sort(st)
{
}

Variable::~Variable(void)
{
}

//For debuging purpose
void Variable::Show()
{
	cout<<name<<":"<<sort<<endl;
}

//return the variable name
string Variable::GetName()
{
	return name;
}

//Return the name of the sort
string Variable::GetSort()
{
	return sort;
}

//Set the sort
void Variable::SetSort(Sort *s)
{
	pSort=s;
}

//Set the size of the sort
void Variable::SortSize(size_t t)
{
	size=t;
}

//Increase Index, return true, if not hit the last element of domain
//otherwise, return false
bool Variable::NextValue()
{
	if(pSort->GetSortType()==list_based){
		++idx;
		if(idx>=pSort->GetDomainSize()){
			idx=0; 
			return false;
		}
	}
	else{
		++idx;
		if(pSort->GetLow()+idx>pSort->GetHight()){
			idx=0;
			return false;
		}
	}
	return true;
}

//Get the current value indicated by the idx
std::string Variable::GetValue()
{
	return pSort->GetDomainElement(idx);
}

//Rest the index
void Variable::Reset(bool f)
{
	if(f==true) idx=0;
    else idx=-1;
}

//Return the domain size
size_t Variable::GetSize()
{
	return size;
}

//Check whether a symbol s is in the domain of the variable
bool Variable::InDomain(string s)
{
    if(pSort->GetSortType()==list_based){
        size_t sz=pSort->GetDomainSize();
        for(size_t idx=0; idx<sz; idx++){
            if(s==pSort->GetDomainElement(idx)) return true;
        }
        return false;
    }
    else{
        stringstream num(s);
        int x;
        num>>x;
        if(x>=pSort->GetLow() && x<=pSort->GetHight()) return true;
        else return false;
    }
}




