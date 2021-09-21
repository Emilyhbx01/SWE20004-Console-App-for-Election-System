#include <iostream>

using namespace std;


void displayAddCandidateMenu() {

	cout << "1) Add Candidate\n";
	cout << "2) View Candidate\n";
	cout << "3) Quit\n";

}

int promptChoice() {
	int choice;
	bool valid = false;
	while (!valid) {
		cout << "Enter your choice:\n";
		cin >> choice;
		if (choice > 0 && choice <= 3) {
			valid = true;
		}
		else {
			cout << "Invalid input\n";
		}
	
	}

	return choice;
}

void viewCandidate() {


}

void addCandidate() {


}

