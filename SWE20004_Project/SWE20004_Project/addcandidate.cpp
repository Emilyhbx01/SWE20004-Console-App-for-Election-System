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

int promptChoice() {
	int choice;
	bool valid = false;
	while (!valid) {
		cout << "Enter your choice:\n";
		cin >> choice;
		if (choice > 0 && choice <= 3) {
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

void addCandidate() {

	// Name and Party are stored as variable character
	char name[50], party[50]; //[50] is the array dimension
	//Division and count stored as variable integer
	int division, count;


	//Menu Option [1] Description
	cout << "Welcome!" << endl;
	cout << "This section is for candidate registration." << endl;
	cout << "Please fill each field correctly." << endl;
	cout << "Candidate ID will be assigned at the end." << endl;
	cout << endl;

	//User Input Section
	cout << "Name: ";
	cin.getline(name, 50);
	cout << "Party: ";
	cin.getline(party, 50);
	cout << "Division: ";
	cin >> division;

	if (division > 4) {
		cout << "Please enter the correct division (1~4)." << endl;
		cout << "Division: ";
		cin >> division;
	}

	//Count: Total number of votes
	count = 0; //initial value

	//Assigned Candidate ID
	//Extract and uppercase first 3 letters of party
	string str(party); //Convert char to string for party field
	string partyname = str.substr(0, 3); //Getting the first 3 letter of the party
	transform(partyname.begin(), partyname.end(), partyname.begin(), ::toupper); //Uppercase the first 3 letters of the party name
	const char* nameID = partyname.c_str();


	//Program End Description
	cout << endl;
	cout << "Your -Assigned Candidate ID-: " << nameID << endl; //Assigned Candidate ID
	cout << "You have finish registering yourself as a candidate for the election." << endl;
	cout << "Good Luck in the Election!" << endl;
	//Program ends
}

