/*
Name: Bhagya Priyadarshani Kumari Wijesuriya (101216659)
	  Emily Hong Boon Xuan (101220757)
	  Kelly Jee Li Zhen (102761529)
	  Vernon Chai Chyn Yeong (101223031)
Program Description: This program is to create a database for candidates and storing it into .txt file.
					 This part of the program is the main function where multiples functions are called to perform the adding candidates
					 into the database. Users can add, view, search and exit the program by inputting their choices.
*/

#include <iostream>
#include <string>
#include "votecandidate.h"
#include "addcandidate.h"
using namespace std;

string displayMainMenu();

//Main function of the program
int main() {
	bool run = true;

	while (run) {
		string choice = displayMainMenu();
		if (choice == "1") {
			displayAddCandidateMenu();
			string addChoice = promptChoice();
			if (addChoice == "1") {
				addCandidate(); //adding candidate function
			}
			else if (addChoice == "2") {
				viewCandidate(); //viewing candidate function
			}
			else if (addChoice == "3") {
				searchCandidate(); //search candidate function
			}
			else if (addChoice == "4") {
				exitProgram();//quit the program
				run = false;
				return 1;
			}
		}
		else if (choice == "2") {
			displayVoteMenu();
			string voteChoice = promptVoteChoice();
			if (voteChoice == "1") {
				viewCandidatesOptions();
			}
			else if (voteChoice == "2") {
				registerVoter();
			}
			else if (voteChoice == "3") {
				vote();
			}
			else if (voteChoice == "4") {
				viewVoteResult();
			}
			else if (voteChoice == "5") {
				quit();
			}
		}
		else if (choice == "3") {
			return 1;
		}
		
	}
	return 0;
}

string displayMainMenu() {
	string choice = "0";
	bool valid = false;
	cout << "1) Add Candidate" << endl;
	cout << "2) Vote Candidate" << endl;
	cout << "3) Quit" << endl;
	

	while (!valid) {
		getline(cin, choice);
		if (choice == "1" || choice == "2" || choice == "3") {
			valid = true;
		}
		else {
			cout << "Invalid selection, please try again" << endl;
		}
	}
	
	return choice;
	

}