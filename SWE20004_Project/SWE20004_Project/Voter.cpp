/*
Name: Bhagya Priyadarshani Kumari Wijesuriya (101216659)
	  Emily Hong Boon Xuan (101220757)
	  Kelly Jee Li Zhen (102761529)
	  Vernon Chai Chyn Yeong (101223031)
Program Description: This program is a voting system that consists of 2 databases for candidates and voters in .txt files.
					 This part of the program shows the writing of the voter part in the program which includes:
					 1) view candidates details in all division or by specific division or party.
					 2) registering voters.
					 3) voting for candidates by voters.
					 4) view vote results summary in all division or specific division.
					 5) quiiting the program.	 
*/

#include "Voter.h"
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

Voter::Voter() {
	voterID = "";
	name = "";
	age = NULL;
	division = NULL;
	status = "";
}

Voter::Voter(string id, string voterName, int voterAge, int div, string voteStatus) {
	voterID = id;
	name = voterName;
	age = voterAge;
	division = div;
	status = voteStatus;
}

string Voter::getVoterId() {
	return voterID;
}

//This function is for the user to add their name as a voter in the form of string
string Voter::getName() {
	string name;
	bool valid = false;

		while (!valid) {
			cout << endl << "Name of voter:" << endl;
			getline(cin, name);
			for (unsigned int i = 0; i < name.length(); i++) {
				char letter = name[i];
				if (!isalpha(letter) && (!isspace(letter))) {
					cout << "Invalid input" << endl;
					valid = false;
					break;
				}
				else if (isalpha(letter)) {

					valid = validatevoterName(name);
					break;
				}
			}
		}
		
	return name;
}

int Voter::getAge() {
	return age;
}

int Voter::getDivision() {
	return division;
}

string Voter::getStatus() {
	return status;
}

void Voter::setStatus(string voteStatus) {
	status = voteStatus;
}

//Reading candidate text file
vector<Candidate> Voter::getCandidates() {
	ifstream inputStream;
	string fileLine = "";
	vector<string> candidateDetails;
	vector<Candidate> candidates;
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

	if (!candidateDetails.empty()) {

		for (int i = 0; i < candidateDetails.size(); i += 5) {
			int nameIndex = i + 1;
			int partyIndex = i + 2;
			int divisionIndex = i + 3;
			int voteIndex = i + 4;
			Candidate candidate(candidateDetails[i], candidateDetails[nameIndex], candidateDetails[partyIndex], stoi(candidateDetails[divisionIndex]), stoi(candidateDetails[voteIndex]));
			candidates.push_back(candidate);
		}
	}
	return candidates;
}

//User input validation for the view vote results by division
//This part ensure that the user input for division is valid which is input of 1 to 4
//Other input will be considered invalid by printing a message to inform of the invalid input
string Voter::promptSearchDivision() {
	bool valid = false;
	string searchDivision;

	while (!valid) {
		cout << "Division:" << endl;
		getline(cin, searchDivision);
		if (searchDivision == "1" || searchDivision == "2" || searchDivision == "3" || searchDivision == "4") {
			valid = true;
		}
		else {
			cout << "Invalid division...Please try again" << endl;
		}
	}
	return searchDivision;
}

//This function is the menu options for the view vote results where user can choose to view the result by specific division or all division
void Voter::viewVoteResult() {
	string choice;
	bool valid = false;
	cout << endl << "1) View voting result of a division" << endl;
	cout << "2) View voting result of all divisions" << endl;
	while (!valid) {
		cout << "Enter your choice:" << endl;
		getline(cin, choice);

		if (choice == "1") {
			viewDivisionVoteResult();
			valid = true;
		}
		else if (choice == "2") {
			viewAllVoteResult();
			valid = true;
		}
		else {
			cout << "Invalid selection, please try again" << endl;
		}
	}
}

//Displaying candidate detail for the view vote result
void Voter::printCandidateSummary(string candidateID, string name, string party, int vote, double percentage) {
	cout << "Candidate ID:" << candidateID << endl;
	cout << "Candidate Name:" << name << endl;
	cout << "Party:" << party << endl;
	cout << "Votes:" << vote << endl;
	cout << std::fixed << std::setprecision(2);
	cout << "Percentage:" << percentage << "%" << endl << endl;
}

//Find all candidate with highest or lowest votes (may have more than 1 candidate)
void Voter::findCandidate(vector<Candidate> candidates, int totalVotes, int vote) {

	for (Candidate candidate : candidates) {
		int candidateVote = candidate.getVotes();
		if (candidateVote == vote) {
			double percentageVote = 0.0;
			if (totalVotes > 0) {
				percentageVote = (double(candidateVote) / (double)totalVotes) * 100;;
			}
			printCandidateSummary(candidate.getCandidateId(), candidate.getName(), candidate.getParty(), candidate.getVotes(), percentageVote);
		}
	}
}

//Summarise voting result for all divisions
void Voter::summariseAllVoteResult(string divisionPhrase, vector<Candidate> candidates, int totalVotes, int maxVote, int minVote) {
	cout << endl << "Total vote for " << divisionPhrase << ":" << endl << totalVotes << endl;
	cout << endl << "Candidates with highest vote" << ":" << endl;
	findCandidate(candidates, totalVotes, maxVote);
	cout << endl << "Candidates with lowest vote" << ":" << endl;
	findCandidate(candidates, totalVotes, minVote);
}


//Display voting result for all divisions
void Voter::viewAllVoteResult() {
	vector<Candidate> candidates = getCandidates();
	int totalVotes = 0;
	int minVote = candidates[0].getVotes();
	int maxVote = 0;
	cout << endl << "ID\t" << "Candidate Name\t" << "Votes" << endl;


	for (Candidate candidate : candidates) {
		int candidateVote = candidate.getVotes();
		cout << candidate.getCandidateId() << "\t" << candidate.getName() << "\t" << candidateVote << "\t" << endl;
		totalVotes += candidateVote;

		if (candidateVote < minVote) {
			minVote = candidateVote;
		}
		if (candidateVote > maxVote) {
			maxVote = candidateVote;
		}
	}
	summariseAllVoteResult("all divisions", candidates, totalVotes, maxVote, minVote);
}

//Display voting result for certain division
void Voter::viewDivisionVoteResult() {
	int totalVotes = 0;
	vector<Candidate> candidates = getCandidates();
	vector<Candidate> divisionCandidates;
	int minVote = candidates[0].getVotes();
	int maxVote = 0;
	int division = stoi(promptSearchDivision());

	cout << endl << "ID\t" << "Candidate Name\t" << "Votes" << endl;
	for (Candidate candidate : candidates) {
		if (candidate.getDivision() == division) {
			int candidateVote = candidate.getVotes();
			divisionCandidates.insert(divisionCandidates.end(), { candidate.getCandidateId(),candidate.getName() ,candidate.getParty(),candidate.getDivision(),candidateVote });
			cout << candidate.getCandidateId() << "\t" << candidate.getName() << "\t" << candidateVote << "\t" << endl;
			totalVotes += candidateVote;

			if (candidateVote < minVote) {
				minVote = candidateVote;
			}
			if (candidateVote > maxVote) {
				maxVote = candidateVote;
			}
		}
	}
	summariseAllVoteResult("division " + to_string(division), divisionCandidates, totalVotes, maxVote, minVote);
}

//Print candidate details for view candidates
void Voter::printCandidatesDetails(Candidate candidate) {
	cout << endl << "CandidateID:" << candidate.getCandidateId() << endl;
	cout << "Name:" << candidate.getName() << endl;
	cout << "Party:" << candidate.getParty() << endl;
	cout << "Division:" << candidate.getDivision() << endl;
	cout << "Votes:" << candidate.getVotes() << endl << endl;
}

//Menu options for view candidates details in all division or by specific division or party
void Voter::viewCandidatesOptions() {
	string choice;
	bool valid = false;
	cout << endl << "1) View candidates in all division." << endl;
	cout << "2) View candidates in specific divisions" << endl;
	cout << "3) View candidates in specific party" << endl;
	while (!valid) {
		cout << "Enter your choice:" << endl;
		getline(cin, choice);

		if (choice == "1") {
			viewCandidates();
			valid = true;
		}
		else if (choice == "2") {
			viewCandidatesDivision();
			valid = true;
		}
		else if (choice == "3") {
			viewCandidatesParty();
			valid = true;
		}
		else {
			cout << "Invalid selection, please try again" << endl;
		}
	}
}

//View all candidates in all division
void Voter::viewCandidates() {
	cout << "This section is to view all candidates in all division." << endl << endl;
	vector<Candidate> candidates = getCandidates();

	for (Candidate candidate : candidates) {
		printCandidatesDetails(candidate);
	}
	cout << endl;
}


//View candidate by specific division
void Voter::viewCandidatesDivision() {
	bool found = false;
	vector<Candidate> candidates = getCandidates();
	int searchDivision = stoi(promptSearchDivision());
	cout << "This section is to view candidates in the specified division." << endl;

	for (Candidate candidate : candidates) {
		if (candidate.getDivision() == searchDivision) {
			printCandidatesDetails(candidate);
			found = true;
		}
	}

	if (!found) {
		cout << "No candidates available..." << endl << endl;
	}
}

//View candidate by specific party
void Voter::viewCandidatesParty() {
	string searchParty;
	bool found = false;
	vector<Candidate> candidates = getCandidates();
	cout << "This section is to view candidates in the specified party." << endl;

	cout << "Party name: " << endl;
	getline(cin, searchParty);
	transform(searchParty.begin(), searchParty.end(), searchParty.begin(), ::tolower);

	for (Candidate candidate : candidates) {
		string candidateParty = candidate.getParty();
		transform(candidateParty.begin(), candidateParty.end(), candidateParty.begin(), ::tolower);
		if (candidateParty == searchParty) {
			printCandidatesDetails(candidate);
			found = true;

		}
	}

	if (!found) {
		cout << "No candidates available..." << endl << endl;
	}
}

//Vote for candidates
void Voter::vote() {
	string voterID, candidateID, confirm;
	Voter myVoter;
	bool candidateExists = false;
	
	voterID = verifyVoter();

	//Proceed when voter has been verified
	if (voterID != "q") {
		if (!voterID.empty()) {
			//Get the voter
			vector<Voter> voters = getVoters();

			for (Voter v : voters) {
				string vID = v.getVoterId();
				transform(vID.begin(), vID.end(), vID.begin(), [](unsigned char c) {return tolower(c); });

				if (vID == voterID)
					myVoter = v;
			}

			//Display all the candidates in the voter's division
			vector<Candidate> candidates = getCandidates();

			for (Candidate c : candidates) {
				if (c.getDivision() == myVoter.getDivision())
					printCandidatesDetails(c);
			}

			//Checks if the voter has already voted or not
			if (myVoter.getStatus() == "Not Voted") {
				cout << "\n--------------------" << endl;
				cout << "Vote for a candidate" << endl;
				cout << "--------------------" << endl;

				while (true) {
					bool loop = true;

					cout << "\nEnter the candidate's ID (Q: Exit): ";
					getline(cin, candidateID);

					transform(candidateID.begin(), candidateID.end(), candidateID.begin(), [](unsigned char c) {return tolower(c); });

					//Exits the voting section
					if (candidateID == "Q" || candidateID == "q") {
						break;
					}

					//Checks if the candidate ID is valid and in the same division as the voter
					for (Candidate c : candidates) {
						string id = c.getCandidateId();
						transform(id.begin(), id.end(), id.begin(), [](unsigned char c) {return tolower(c); });

						if (candidateID == id && c.getDivision() == myVoter.getDivision()) {
							//Gets the voters confirmation on their vote
							while (true) {
								cout << "Are you sure (Y/N): ";
								getline(cin, confirm);

								if (confirm == "Y" || confirm == "y") {
									changeValues(c, myVoter);

									//Provide voting feedback to the voter
									cout << "\nThank you for voting " + myVoter.getName() + "." << endl;
									cout << "You have successfully voted for " + c.getCandidateId() + " " + c.getName() + ".\n" << endl;

									loop = false;

									break;
								}
								else if (confirm == "N" || confirm == "n") {
									break;
								}
								else {
									cout << "Invalid input. Please try again." << endl;
								}
							}

							candidateExists = true;
							break;
						}
					}

					//Breaks the loop once the vote succeeds
					if (loop == false)
						break;

					//Displays an error message if the candidate could not be found
					if (candidateExists == false) {
						cout << "The candidate could not be found. Please try again." << endl;
					}
				}
			}
			else {
				cout << "You have already voted\n" << endl;
			}
		}
		else {
			cout << "Login failed." << endl;
		}
	}
}

//Increases the vote count for the candidate and the voters voting status in their respective text files
void Voter::changeValues(Candidate candidate, Voter voter) {
	vector<Candidate> candidates = getCandidates(), newCandidates = {};
	vector<Voter> voters = getVoters(), newVoters = {};

	ofstream outputStream;

	outputStream.open("candidate.txt", ios::out);

	//Increases the vote count of the candidate in the candidate text file
	if (outputStream.is_open()) {
		for (Candidate c : candidates) {
			if (candidate.getCandidateId() == c.getCandidateId())
				c.setVotes(c.getVotes() + 1);

			newCandidates.push_back(c);
		}

		for (Candidate c : newCandidates)
			outputStream << c.getCandidateId() + "," + c.getName() + "," << c.getParty() + "," + to_string(c.getDivision()) + "," + to_string(c.getVotes()) << endl;
	}
	else {
		cout << "Error: The candidate text file could not be opened." << endl;
	}

	outputStream.close();

	outputStream.open("voter.txt", ios::out);

	//Sets the voters voting status to voted in the voter text file
	if (outputStream.is_open()) {
		for (Voter v : voters) {
			if (voter.getVoterId() == v.getVoterId()) {
				v.setStatus("Voted");

			newVoters.push_back(v);
			}
		}

		for (Voter v : newVoters)
			outputStream << v.getVoterId() << "," << v.getName() << "," << v.getAge() << "," << v.getDivision() << "," << v.getStatus() << endl;
	}
	else {
		cout << "Error: The voter text file could not be opened." << endl;
	}

	outputStream.close();
}

//Verifies that the voter ID given is valid and returns the voter ID
string Voter::verifyVoter() {
	string id;
	Voter myVoter;
	bool idExists = false;

	while (true) {
		cout << "\nVoter ID (Q: Exit): ";
		getline(cin, id);

		transform(id.begin(), id.end(), id.begin(), [](unsigned char c) {return tolower(c); });

		//Exits the function
		if (id == "q")
			return "q";

		vector<Voter> voters = getVoters();

		for (Voter v : voters) {
			string voterID = v.getVoterId();
			transform(voterID.begin(), voterID.end(), voterID.begin(), [](unsigned char c) {return tolower(c); });
			
			if (voterID == id) {
				myVoter = v;
				idExists = true;
			}
		}

		//Only returns a value when the Voter ID is found
		if (idExists)
			return id;
		else
			cout << "The voter ID you entered is not registered. Please try again." << endl;
	}
}

//Get the voters details from the voter text file
vector<Voter> Voter::getVoters() {
	ifstream inputStream;
	string fileLine = "";
	vector<string> voterDetails;
	vector<Voter> voters;

	inputStream.open("voter.txt", ifstream::in);

	while (getline(inputStream, fileLine)) {
		char fileLineArray[200];
		strcpy_s(fileLineArray, fileLine.c_str());

		//Split line by comma
		char* remain = fileLineArray;
		char* token;
		while (token = strtok_s(remain, ",", &remain)) {
			voterDetails.push_back(token);
		}
	}

	inputStream.close();

	if (!voterDetails.empty()) {
		for (int i = 0; i < voterDetails.size(); i += 5) {
			int name = i + 1, age = i + 2, div = i + 3, vote = i + 4;

			Voter voter(voterDetails[i], voterDetails[name], stoi(voterDetails[age]), stoi(voterDetails[div]), voterDetails[vote]);
			voters.push_back(voter);
		}
	}

	return voters;
}

//This function is the menu options for the register voters 
void Voter::registerVoter() {

	string name, age, voterID;
	int division, status;
	int count = 0;
	bool validVoterName;

	cout << endl << "Welcome!" << endl;
	cout << "This section is for voter registration." << endl;
	cout << "Please fill each field correctly." << endl;
	cout << endl;
}



vector<string> readVoteFile() {
	ifstream inputStream;
	string fileLine = "";
	vector<string> voterDetails;
	inputStream.open("vote.txt", ifstream::in);

	while (getline(inputStream, fileLine)) {
		char fileLineArray[200];
		strcpy_s(fileLineArray, fileLine.c_str());

		//Split line by comma
		char* remain = fileLineArray;
		char* token;
		while (token = strtok_s(remain, ",", &remain)) {
			voterDetails.push_back(token);
		}
	}
	inputStream.close();
	return voterDetails;
	
//This function is to check if the voter's name is already exists in the database
bool validateVoterName(string name) {
	vector<string> voterDetails = readVoteFile();
	bool nameExists = false;
	transform(name.begin(), name.end(), name.begin(), ::tolower);

	for (int i = 1; i < voterDetails.size(); i += 5) {
		string detail = voterDetails[i];
		transform(detail.begin(), detail.end(), detail.begin(), ::tolower);
		if (detail == name) {
			nameExists = true;
			break;
		}
	}

	// Returns a value based on whether the name exists
	if (nameExists == true) {
		cout << "Voter's name is already registered." << endl;
		return false;
	}
	else {
		return true;
	}
}


//This function prints out the description when program quit	
void Voter::quit() {
	cout << "Thank you for using this program. Goodbye!" << endl;

	
}
