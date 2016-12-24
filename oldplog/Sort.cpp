#include "Sort.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

Sort::Sort(void)
{
}

Sort::~Sort(void)
{
}

Sort::Sort(string s, SortType stype):obj(s), sortType(stype),low(0),high(0)
{
}

string Sort::GetObject()
{
	return obj;
}

void Sort::Add(string s)
{
	domain.push_back(s);
}

size_t Sort::GetDomainSize()
{
	if(sortType==list_based){
		return domain.size();
	}
	else{
		return high-low+1;
	}
}

std::string Sort::GetDomainElement(size_t idx)
{
	stringstream out;
	if(sortType==list_based){
		if(idx>=0 && idx<=domain.size()) return domain[idx];
		else return "";
	}
	else{
		//int i(low+idx);
		//cout<<"low "<<low<<" "<<idx<<endl;
		int x=low+idx;
		//cout<<"x"<<x<<endl;
		out<<x;
		//itoa(x, s, 10);
		//string sout(s);
		//cout<<"hello"<<endl;
		string s=out.str();
        return s;
	}
}

SortType Sort::GetSortType()
{
	return sortType;
}

void Sort::Show()
{
	cout<<obj<<": ";
	vector<string>::iterator itr;
	if(sortType==list_based){
		itr=domain.begin();
		while(itr!=domain.end()){
			cout<<(*itr)<<" ";
			++itr;
		}
	}
	else{
		cout<<low<<"..."<<high;
	}
	cout<<endl;
}

void Sort::SetLowHigh(int l, int h)
{
	low=l;
	high=h;
}

int Sort::GetLow()
{
	return low;
}

int Sort::GetHight()
{
	return high;
}

void Sort::RemoveElement(size_t idx)
{
	vector<string>::iterator itr;
    itr=domain.begin();
	size_t i=0;
	while(i<idx){
	   i++;
       ++itr;
	}
	domain.erase(itr);
}

/*
//Return the element in the domain indicated by idx
 Sort::GetElement(size_t idx)
{
    if(sortType==list_based){
	if(idx>=0 && idx<=domain.size()) return domain[idx];
	else return NULL;
    }
    return NULL;
	
}*/

