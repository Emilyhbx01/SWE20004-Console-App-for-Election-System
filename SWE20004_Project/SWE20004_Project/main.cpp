#include <iostream>
#include "addcandidate.h"
using namespace std;

int MainMenu();

int main() {
	int main_choice = MainMenu();
	if (main_choice == 1) {
		DisplayAddCandidateMenu();
		int add_choice = PromptChoice();
		switch (add_choice) {
			case 1:
				AddCandidate();
				break;
			case 2:
				ViewCandidate();
				break;
			case 3:
				return 0;

		}

	}


	
	return 0;
}



int MainMenu() {
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


