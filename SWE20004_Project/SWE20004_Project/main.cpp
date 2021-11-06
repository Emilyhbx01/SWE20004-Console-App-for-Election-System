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


int main() {
	bool run = true;

	while (run) {
		displayVoteMenu();
		string voteChoice = promptVoteChoice();
		Voter voter;

		if (voteChoice == "1") {
			voter.viewCandidatesOptions();
		}
		else if (voteChoice == "2") {
			registerVoter();
		}
		else if (voteChoice == "3") {
			voter.vote();
		}
		else if (voteChoice == "4") {
			voter.viewVoteResult();
		}
		else if (voteChoice == "5") {
			quit();
			run = false;
			return 1;
		}
		
	}
	return 0;
}

