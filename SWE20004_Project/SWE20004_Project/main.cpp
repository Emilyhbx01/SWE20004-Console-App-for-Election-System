/*
Name: Bhagya Priyadarshani Kumari Wijesuriya (101216659)
	  Emily Hong Boon Xuan (101220757)
	  Kelly Jee Li Zhen (102761529)
	  Vernon Chai Chyn Yeong (101223031)
Date:
Program Description: This program is to create a database for candidates and storing it into .txt file.
					 This part of the program is the main function where multiples functions are called to perform the adding candidates
					 into the database. Users can add, view, search and exit the program by inputting their choices.
*/
#include <iostream>
#include "addcandidate.h"
using namespace std;

//Main function of the program
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



