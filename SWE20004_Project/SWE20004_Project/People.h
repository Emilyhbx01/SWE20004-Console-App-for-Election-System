#pragma once
#include <iostream>
using namespace std;

class People {

protected:
	string name;
	int division;

public:
	People(string name_arg, int division_arg);

	string GetName();

	int GetDivision();


};
