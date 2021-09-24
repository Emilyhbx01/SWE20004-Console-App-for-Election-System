#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;


void displayAddCandidateMenu() {

	cout << "1) Add Candidate\n";
	cout << "2) View Candidate\n";
	cout << "3) Quit\n";

}

string promptChoice() {
	string choice;
	bool valid = false;
	while (!valid) {
		cout << endl << "Enter your choice:\n";
		getline(cin, choice);
		if (choice == "1" || choice == "2" || choice == "3") {
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

string promptCandidateName() {
	string name;
	bool valid = false;

	while (!valid) {

		cout << endl << "Name of candidate:" << endl;
		getline(cin, name);
		for (unsigned int i = 0; i < name.length(); i++) {
			char letter = name[i];
			if (!isalpha(letter) && (!isspace(letter))) {
				cout << "Invalid input" << endl;
				valid = false;
				break;
			}
			else if (isalpha(letter)) {
				valid = true;
			}
		}

	}

	return name;
}

string promptCandidateParty() {
	string party_no;
	string party;
	bool valid = false;

	cout << endl << "Choose a party:" << endl;
	cout << "1) National" << endl;
	cout << "2) Pakatan" << endl;
	cout << "3) Bersatu" << endl;


	while (!valid) {

		cout << endl << "Choose a party:" << endl;
		getline(cin, party_no);
		if (party_no == "1" || party_no == "2" || party_no == "3") {
			valid = true;
		}
		else {
			cout << "Invalid input" << endl;
		}
	}

	switch (stoi(party_no)) {
	case 1:
		party = "National";
		break;
	case 2:
		party = "Pakatan";
		break;
	case 3:
		party = "Bersatu";
		break;


	}

	return party;
}

string promptDivision() {
	string division;
	bool valid = false;
	
	while (!valid) {
		cout << endl << "Division:" << endl;
		getline(cin, division);
		if (division == "1" || division == "2" || division == "3" || division == "4") {
			valid = true;
		}

		else {
			cout << "Please enter the correct division (1~4)." << endl;
		}
	}

	return division;
	
}
void addCandidate() {

	
	string name, party;
	int division;
	int count = 0;


	//Menu Option [1] Description
	cout << "Welcome!" << endl;
	cout << "This section is for candidate registration." << endl;
	cout << "Please fill each field correctly." << endl;
	cout << "Candidate ID will be assigned at the end." << endl;
	cout << endl;

	name = promptCandidateName();
	party = promptCandidateParty();
	division = stoi(promptDivision());

	

	
	//Assigned Candidate ID
	string str(party); 
	string partyname = str.substr(0, 3);
	transform(partyname.begin(), partyname.end(), partyname.begin(), ::toupper);
	const char* nameID = partyname.c_str();

}

