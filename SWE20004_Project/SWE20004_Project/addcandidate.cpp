#include <iostream>
#include <string>
#include <fstream>
#include <set>
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
	string party;
	bool valid = false;
	while (!valid) {
		cout << endl << "Party Name:" << endl;
		getline(cin, party);
		for (unsigned int i = 0; i < party.length(); i++) {
			char letter = party[i];
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

void inputToFile(string& candidateID, string& name, string& party, int& division, int& count) {

	string outputFilename = "candidate.txt";
	string candidateDetails = "CandidateID:" + candidateID + ",Name:" + name + ",Party:" + party + ",Division:" + to_string(division) + ",Count:" + to_string(count) + "\n";
	ofstream outputStream;
	outputStream.open(outputFilename, ofstream::app);


	if (outputStream.is_open()) {
		outputStream << candidateDetails << endl;
	}
	else {
		cerr << "File cannot be opened" << endl;
	}

	outputStream.close();
}


//function to generate the random 2 digit behind candidate ID
//read the candidate file to determine the next ID
int generateCandidateIdNo() {
	
	string inputFilename = "candidate.txt";
	ifstream inputStream;
	int no = 1;
	inputStream.open(inputFilename, ifstream::in);

	if (inputStream.is_open()) {
		string str;
		while (getline(inputStream,str)) {
			int startPosition = str.find("CandidateID");
			if (startPosition != -1) {
				no += 1;
			}

		
		}
	}

	if (to_string(no).length() == 1) {
		no = stoi("0") + no;
	}
	return no;
}


//to generate the full candidate ID
string generateCandidateID(int& candidateIdNo, string& party ) {
	string candidateID;
	if (to_string(candidateIdNo).length() == 1) {
		candidateID = party.substr(0, 3) + "0" + to_string(candidateIdNo);
	}
	else {
		candidateID = party.substr(0, 3) + to_string(candidateIdNo);
	}
	return candidateID;
}




bool validateCandidateName(string& name) {

	return true;
}



void addCandidate() {

	
	string name, party, candidateID;
	int division, candidateIdNo;
	int count = 0;
	bool validCandidateName;

	//Menu Option [1] Description
	cout << endl << "Welcome!" << endl;
	cout << "This section is for candidate registration." << endl;
	cout << "Please fill each field correctly." << endl;
	cout << "Candidate ID will be assigned at the end." << endl;
	cout << endl;	
		
	name = promptCandidateName();
	party = promptCandidateParty();
	division = stoi(promptDivision());
	candidateIdNo = generateCandidateIdNo();
	candidateID = generateCandidateID(candidateIdNo,party);
	validCandidateName = validateCandidateName(name);

	if (validateCandidateName(name)) {
		inputToFile(candidateID, name, party, division, count);
	}
	else {
		cout << "Candidate name already exists." << endl;
	}

	
}



void viewCandidate() {


}


