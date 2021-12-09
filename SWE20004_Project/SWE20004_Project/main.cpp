/*
Name: Bhagya Priyadarshani Kumari Wijesuriya (101216659)
	  Emily Hong Boon Xuan (101220757)
	  Kelly Jee Li Zhen (102761529)
	  Vernon Chai Chyn Yeong (101223031)
Program Description: This program is a voting system that consists of 2 databases for candidates and voters in .txt files. 
					 This part of the program shows the menu options to view candidates, register voters, voting, view voting results and quitting
					 program.
*/

#include <iostream>
#include <string>
#include "votecandidate.h"
#include "addcandidate.h"
using namespace std;


//int main() {
//	bool run = true;
//
//	while (run) {
//		displayVoteMenu();
//		string voteChoice = promptVoteChoice();
//		Voter voter;
//
//		if (voteChoice == "1") {
//			voter.viewCandidatesOptions();	//Menu option 1 that is to view candidates
//		}								   	
//		else if (voteChoice == "2") {	   
//			voter.registerVoter();			//Menu option 2 that is to register voters
//		}								   								  
//		else if (voteChoice == "3") {	   
//			voter.vote();					//Menu option 3 that is to vote
//		}								   
//		else if (voteChoice == "4") {	   
//			voter.viewVoteResult();			//Menu option 4 is to view the result of the voting
//		}								   
//		else if (voteChoice == "5") {	   
//			voter.quit();					//Menu option 5 is to quit the program
//			run = false;
//			return 1;
//		}
//	}
//
//	return 0;
//}


//Main function of the program
int main() {
	bool run = true;

	while (run) {
		displayAddCandidateMenu();
		string add_choice = promptChoice();
		if (add_choice == "1") {
			addCandidate(); //adding candidate function
		}
		else if (add_choice == "2") {
			viewCandidate(); //viewing candidate function
		}
		else if (add_choice == "3") {
			searchCandidate(); //search candidate function
		}
		else if (add_choice == "4") {
			exitProgram();//quit the program
			run = false;
			return 1;
		}
	}
	return 0;
}
