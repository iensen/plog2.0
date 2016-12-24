#pragma once
#include <string>
#include <vector>
//#include "TermTree.h"

enum SortType {list_based, range_based};

class Sort
{
public:
	Sort(void);
	~Sort(void);
	//construct
	Sort(std::string s, SortType stype);
	
	//Get the string name
	std::string GetObject();

	//Add objcet to domain
	void Add(std::string tm);

	//Get the size of the domain
	size_t GetDomainSize();

	//Return the element indicated by idx in string form
	std::string GetDomainElement(size_t idx);

	//Return the sort type	
	SortType GetSortType();

	//Remove the an element of domain indicated by idx. Only works for list_based sort
	void RemoveElement(size_t idx);

	//Return the element in the domain indicated by idx
	//TermTree* GetElement(size_t idx);

	//Showing the sort
	void Show();

	//Set the low bound and high bound of the sort, only works for range_based sort
	void SetLowHigh(int l, int h);

	//Get the low bound of the sort
	int GetLow();

	//Get the high bound of the sort
	int GetHight();

	void ClearDomain(){domain.clear();};
private:
	int low;
	int high;
	//bool ground;
	SortType sortType;
	std::string obj;
	std::vector<std::string> domain;
};
