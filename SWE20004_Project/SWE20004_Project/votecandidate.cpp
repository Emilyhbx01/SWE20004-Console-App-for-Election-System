#include "votecandidate.h"
#include <string>

void displayVoteMenu() {
	cout << "1) View Candidates" << endl;
	cout << "2) Register Voter" << endl;
	cout << "3) Vote" << endl;
	cout << "4) View Voting Results and Summary" << endl;
	cout << "5) Quit" << endl;
}

string promptVoteChoice() {
	string choice;
	bool valid = false;

	while (!valid) {
		cout << endl << "Enter your choice:\n";
		getline(cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4") {
			valid = true;
		}
		else {
			cout << "Invalid selection, please try again\n";
		}

	}
	return choice;
}

void viewCandidates() {

}

void registerVoter() {

}
void vote() {

}

void viewVoteResult() {

}


void quit() {

}