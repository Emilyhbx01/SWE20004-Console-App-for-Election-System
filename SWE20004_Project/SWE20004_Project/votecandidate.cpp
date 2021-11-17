/*
Name: Bhagya Priyadarshani Kumari Wijesuriya (101216659)
	  Emily Hong Boon Xuan (101220757)
	  Kelly Jee Li Zhen (102761529)
	  Vernon Chai Chyn Yeong (101223031)
Program Description: This program is a voting system that consists of 2 databases for candidates and voters in .txt files.
					 This part of the program shows the instructions of the menu options.
*/

#include "votecandidate.h"
#include <string>

//Displaying the menu options instructions.
void displayVoteMenu() {
	cout << "1) View Candidates" << endl;
	cout << "2) Register Voter" << endl;
	cout << "3) Vote" << endl;
	cout << "4) View Voting Results and Summary" << endl;
	cout << "5) Quit" << endl;
}

//User input validation where input of 1 to 5 are valid for the menu options.
string promptVoteChoice() {
	string choice;
	bool valid = false;

	while (!valid) {
		cout << endl << "Enter your choice:" << endl;
		getline(cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5") {
			valid = true;
		}
		else {
			cout << "Invalid selection, please try again\n";
		}

	}
	return choice;
}





