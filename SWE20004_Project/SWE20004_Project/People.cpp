#include "People.h"

	
People::People(string name_arg, int division_arg) {
	name = name_arg;
	division = division_arg;
}

string People::GetName() {
	return name;
}

int People::GetDivision() {
	return division;
}

