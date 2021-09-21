#include <iostream>
#include "addcandidate.h"
using namespace std;

int mainMenu();

int main() {
	int main_choice = mainMenu();
	if (main_choice == 1) {
		displayAddCandidateMenu();
		int add_choice = promptChoice();
		switch (add_choice) {
			case 1:
				addCandidate();
				break;
			case 2:
				viewCandidate();
				break;
			case 3:
				return 0;

		}

	}


	
	return 0;
}



int mainMenu() {
	int choice;
	bool valid = false;
	cout << "1) Add Candidate\n";
	cout << "2) Vote Candidate\n";
	while (!valid) {
		cout << "Enter your choice:\n";
		cin >> choice;
		if (choice > 0 && choice <= 2) {
			valid = true;
		}
		else {
			cout << "Invalid input\n";
		}
	}
	return choice;
}


