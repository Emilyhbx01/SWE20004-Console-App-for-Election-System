#include <iostream>

using namespace std;



void DisplayAddCandidateMenu() {

	cout << "1) Add Candidate\n";
	cout << "2) View Candidate\n";
	cout << "3) Quit\n";

}

int PromptChoice() {
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

void ViewCandidate() {


}

void AddCandidate() {


}

