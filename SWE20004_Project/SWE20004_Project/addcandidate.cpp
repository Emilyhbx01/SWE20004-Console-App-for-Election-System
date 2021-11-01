/*
Name: Bhagya Priyadarshani Kumari Wijesuriya (101216659)
      Emily Hong Boon Xuan (101220757)
	  Kelly Jee Li Zhen (102761529)
	  Vernon Chai Chyn Yeong (101223031)
Program Description: This program is to add candidate into a database. This part shows all the functions used to produced the menu options
                     to add, view and search candidates as well as to exit the program.
*/

#include "addcandidate.h"
#include <string>
#include <fstream>
#include<algorithm>

//This function is to print the name of each menu options
void displayAddCandidateMenu() {
	cout << "1) Add Candidate\n";
	cout << "2) View Candidate\n";
	cout << "3) Search Candidate\n";
	cout << "4) Quit\n";
}

//This function prompt choices for the user to input their choice for the menu option
string promptChoice() {
	string choice;
	bool valid = false;

	while (!valid) {
		cout << endl << "Enter your choice:\n";
		getline(cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4") {
			valid = true;
		}
		else {
			cout << "Invalid input\n";
		}

	}
	return choice;
}

//This function is to retrieve candidate details from text file
vector<string> readCandidateFile() {
	ifstream inputStream;
	string fileLine = "";
	vector<string> candidateDetails;
	inputStream.open("candidate.txt", ifstream::in);

	while (getline(inputStream, fileLine)) {
		char fileLineArray[200];
		strcpy_s(fileLineArray, fileLine.c_str());

		//Split line by comma
		char* remain = fileLineArray;
		char* token;
		while (token = strtok_s(remain, ",", &remain)) {
			candidateDetails.push_back(token);
		}
	}
	inputStream.close();
	return candidateDetails;
}

//This function is to print candidate details.
void printCandidateDetails(string& candidateID, string& name, string& party, string& division, string& count) {
	cout << endl << "CandidateID:" << candidateID << endl;
	cout << "Name:" << name << endl;
	cout << "Party:" << party << endl;
	cout << "Division:" << division << endl;
	cout << "Count:" << count << endl << endl;
}

//This function is to check if the candidate already exists in the database
bool validateCandidateName(string name) {
	vector<string> candidateDetails = readCandidateFile();
	bool nameExists = false;
	transform(name.begin(), name.end(), name.begin(), ::tolower);
	
	for (int i = 1; i < candidateDetails.size(); i += 5) {
		string detail = candidateDetails[i];
		transform(detail.begin(), detail.end(), detail.begin(), ::tolower);
		if (detail == name) {
			nameExists = true;
			break;
		}
	}

	// Returns a value based on whether the name exists
	if (nameExists == true) {
		cout << "Candidate name already exists." << endl;
		return false;
	}
	else {
		return true;
	}
}

//This function is for the user to add their name as a candidate in the form of string
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

				valid = validateCandidateName(name);
				break;
			}
		}
	}
	return name;
}

//This function is for the user to input their candidate party name in the form of string
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

//This function is for the user to input their division in the form of string
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

//This function is to convert the candidates information into .txt file storing into database
void inputToFile(string& candidateID, string& name, string& party, int& division, int& count) {
	string outputFilename = "candidate.txt";
	string candidateDetails = candidateID + "," + name + "," + party + "," + to_string(division) + "," + to_string(count);
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


//This function generate the random 2 digit behind candidate ID
//and read the candidate file to determine the next ID
int generateCandidateIdNo() {
	string inputFilename = "candidate.txt";
	ifstream inputStream;
	int noOfLines = 0;
	int newCandidateNo;
	inputStream.open(inputFilename, ifstream::in);

	if (inputStream.is_open()) {
		string str;
		while (getline(inputStream,str)) {
				noOfLines += 1;
		}
	}
	inputStream.close();
	newCandidateNo = noOfLines + 1;
	return newCandidateNo;
}


//This function generate the full candidate ID
string generateCandidateID(int& candidateIdNo, string& party ) {
	string candidateID;

	//to ensure the number behind the ID is 2 digit by adding a 0 if there is only 1 digit
	if (to_string(candidateIdNo).length() == 1) {
		candidateID = party.substr(0, 3) + "0" + to_string(candidateIdNo);
	}
	else {
		candidateID = party.substr(0, 3) + to_string(candidateIdNo);
	}
	return candidateID;
}

//This function prompt the menu option [1]
void addCandidate() {
	string name, party, candidateID;
	int division, candidateIdNo;
	int count = 0;
	bool validCandidateName;

	//Menu Option [1] Description
	cout << endl << "Welcome!" << endl;
	cout << "This section is for candidate registration." << endl;
	cout << "Please fill each field correctly." << endl;
	cout << endl;	
		
	name = promptCandidateName();
	party = promptCandidateParty();
	division = stoi(promptDivision());
	candidateIdNo = generateCandidateIdNo();
	candidateID = generateCandidateID(candidateIdNo,party);
	inputToFile(candidateID, name, party, division, count);
}


//This function search for a candidate by inputing the full name of the candidate
void searchCandidate() {
	string searchName;
	bool found = false;
	vector<string> candidateDetails = readCandidateFile();

	cout << "Name of candidate:" << endl;
	getline(cin, searchName);
	transform(searchName.begin(), searchName.end(), searchName.begin(),::tolower);

	for (int i = 0; i < candidateDetails.size(); i += 5) {
		int nameIndex = i + 1;
		string name = candidateDetails[nameIndex];
		transform(name.begin(), name.end(), name.begin(), ::tolower);
		if (name == searchName) {
			int partyIndex = i + 2;
			int divisionIndex = i + 3;
			int countIndex = i + 4;
			printCandidateDetails(candidateDetails[i], candidateDetails[nameIndex], candidateDetails[partyIndex], candidateDetails[divisionIndex], candidateDetails[countIndex]);
			found = true;
			break;
		}

	}
	if (!found) {
		cout << "Candidate does not exist" << endl << endl;
	}
}

//This function is to display all the candidates information
void viewCandidate() {

	//View Option [2] Description
	cout << endl << "Welcome!" << endl;
	cout << "This section is to view all candidates" << endl;
	cout << endl;
	vector<string> candidateDetails = readCandidateFile();

	for (int i = 0; i < candidateDetails.size(); i += 5) {
		int nameIndex = i + 1;
		int partyIndex = i + 2;
		int divisionIndex = i + 3;
		int countIndex = i + 4;

		printCandidateDetails(candidateDetails[i], candidateDetails[nameIndex], candidateDetails[partyIndex], candidateDetails[divisionIndex], candidateDetails[countIndex]);
	}
}

//This function prints out the description when program quit
void exitProgram() {
	cout << "Thank you for using this program. Goodbye!" << endl;
}