#include <iostream>
#include "addcandidate.h"
using namespace std;


int main() {
	
	displayAddCandidateMenu();

	string add_choice = promptChoice();
	if (add_choice == "1") {
		addCandidate();
	}
	else if (add_choice == "2") {
		viewCandidate();
	}
	else if (add_choice == "3") {
		return 1;

	}





	return 0;
}



