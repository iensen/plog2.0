#pragma once

#include <string>
#include <vector>
#include "Sort.h"

class Variable
{
public:
	Variable(void);
	Variable(std::string s,std::string st);
	~Variable(void);
	
	std::string GetName();
	std::string GetSort();

	void SetSort(Sort *s);
	void SortSize(size_t t);
	void Show();

	bool NextValue();
	std::string GetValue();
	size_t GetSize();
	void Reset(bool f);
    bool InDomain(std::string s);

private:
	std::string name;
	std::string sort;
	
	size_t idx;  //Index for the current value
	size_t size; //domain size
	Sort *pSort; 
};
