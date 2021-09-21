#include "People.h"

	
People::People(string name_arg, int division_arg) {
	name = name_arg;
	division = division_arg;
}

string People::getName() {
	return name;
}

int People::getDivision() {
	return division;
}

