#pragma once
#include <string>

class Attribute
{
public:
	Attribute(void);
	~Attribute(void);
	//Construct
	Attribute(std::string s1, std::string s2);

	void Show();
	
	std::string GetSortName();
	std::string GetName();

private:
	std::string name;
	std::string sortName;
};
