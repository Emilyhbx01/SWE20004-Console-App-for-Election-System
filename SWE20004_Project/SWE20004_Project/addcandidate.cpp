/*
Name: Bhagya Priyadarshani Kumari Wijesuriya (101216659)
      Emily Hong Boon Xuan (101220757)
	  Kelly Jee Li Zhen (102761529)
	  Vernon Chai Chyn Yeong (101223031)
Date:
Program Description: This program is to add candidate into a database. This part shows all the functions used to produced the menu options
                     to add, view and search candidates as well as to exit the program.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include<algorithm>
using namespace std;

//This function is to display the menu options for the user to choose
void displayAddCandidateMenu() {

	cout << "1) Add Candidate\n";
	cout << "2) View Candidate\n";
	cout << "3) Search Candidate\n";
	cout << "4) Quit\n";

}

//This function prompt choices for the user to input their desired choice for the menu option
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

//To check if the candidate already exists
bool validateCandidateName(string name) {

	ifstream myFile;
	string line;
	vector<string> candidateDetails;
	bool nameExists = false;
	transform(name.begin(), name.end(), name.begin(), ::tolower);
	myFile.open("candidate.txt");

	if (myFile.fail()) {
		cout << "Error: Unable to open candidate.txt.";
		exit(1);
	}

	while (getline(myFile, line)) {
		char fileLine[200];
		strcpy_s(fileLine, line.c_str());
		char* remain = fileLine;
		char* token;

		while ((token = strtok_s(remain, ",", &remain)) && !nameExists) {
			candidateDetails.push_back(token);

			for (string detail : candidateDetails) {
				transform(detail.begin(), detail.end(), detail.begin(), ::tolower);
				if (detail == name) {
					nameExists = true;
					break;
				}
			}
		}

		candidateDetails.clear();
	}

	myFile.close();

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


//Function to generate the random 2 digit behind candidate ID
//Read the candidate file to determine the next ID
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


//To generate the full candidate ID
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
	
	string searchName,fileLine;
	bool found = false;
	vector<string> candidateDetails;
	ifstream inputStream;

	cout << "Name of candidate:" << endl;
	getline(cin, searchName);
	transform(searchName.begin(), searchName.end(), searchName.begin(),::tolower);

	inputStream.open("candidate.txt",ifstream::in);
	if (inputStream.is_open()) {
		
		while (getline(inputStream,fileLine) && !found) {
			candidateDetails.clear();
			char fileLineArray[200];
			strcpy_s(fileLineArray, fileLine.c_str());
			

			//Split line by comma and add each candidate details to vector
			char* remain = fileLineArray;
			char* token;
			while ((token = strtok_s(remain, ",", &remain)) && !found) {
				candidateDetails.push_back(token);
				for (string detail : candidateDetails) {
					transform(detail.begin(), detail.end(), detail.begin(), ::tolower);
					if (detail == searchName && candidateDetails.size() == 5) {
						found = true;
						break;
					}
				}
			}	
		}
	}
	else {
		cerr << "File cannot be opened" << endl;
	}

	inputStream.close();


	//Print candidate details if found 
	if (found) {
		cout << endl << "CandidateID:" << candidateDetails[0] << endl;
		cout << "Name:" << candidateDetails[1] << endl;
		cout << "Party:" << candidateDetails[2] << endl;
		cout << "Division:" << candidateDetails[3] << endl;
		cout << "Count:" << candidateDetails[4] << endl << endl;
	}
	else {
		cout << "Candidate does not exist" << endl << endl;
	}


}

void viewCandidate() {

	//View Option [2] Description
	cout << endl << "Welcome!" << endl;
	cout << "This section is to view all candidates" << endl;
	cout << endl;

	ifstream inputStream;
	string fileLine = "";
	vector<string> candidateDetails;
	inputStream.open("candidate.txt", ifstream::in);
	while (getline(inputStream, fileLine, ',')) {
		char fileLineArray[200];
		strcpy_s(fileLineArray, fileLine.c_str());

		//Split line by comma
		char* remain = fileLineArray;
		char* token;
		while (token = strtok_s(remain, ",", &remain)) {
			candidateDetails.push_back(token);
			for (string detail : candidateDetails) {
				transform(detail.begin(), detail.end(), detail.begin(), ::tolower);
				break;
			}
		}

	}

	inputStream.close();

	//Print candidates detail
	for (int i = 0; i < 5; i = i + 10) {
		cout << endl << "CandidateID:" << candidateDetails[i] << endl;
		cout << "Name:" << candidateDetails[i+1] << endl;
		cout << "Party:" << candidateDetails[i+2] << endl;
		cout << "Division:" << candidateDetails[i+3] << endl;
		cout << "Count:" << candidateDetails[i+4] << endl;
		cout << endl;
	break;
	}

	for (int i = 5; i < 10; i = i + 10) {
		cout << endl << "CandidateID:" << candidateDetails[i] << endl;
		cout << "Name:" << candidateDetails[i + 1] << endl;
		cout << "Party:" << candidateDetails[i + 2] << endl;
		cout << "Division:" << candidateDetails[i + 3] << endl;
		cout << "Count:" << candidateDetails[i + 4] << endl;
		cout << endl;
		break;
	}
}


