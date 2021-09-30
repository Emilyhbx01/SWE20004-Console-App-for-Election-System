#include <iostream>
#include "addcandidate.h"
using namespace std;


int main() {
	bool run = true;
	while (run) {
		displayAddCandidateMenu();

		string add_choice = promptChoice();
		if (add_choice == "1") {
			addCandidate();
		}
		else if (add_choice == "2") {
			viewCandidate();
		}
		else if (add_choice == "3") {
			searchCandidate();

		}
		else if(add_choice == "4"){
			run = false;
			return 1;
		}
	
	}
	

	

	return 0;
}



