#include "Attribute.h"
#include <iostream>
using namespace std;
Attribute::Attribute(void)
{
}

Attribute::~Attribute(void)
{
}

Attribute::Attribute(string s1, string s2):name(s1), sortName(s2)
{
}

string Attribute::GetSortName()
{
	return sortName;
}

string Attribute::GetName()
{
	return name;
}

void Attribute::Show()
{
	cout<<name<<"-> "<<sortName<<endl;
}
