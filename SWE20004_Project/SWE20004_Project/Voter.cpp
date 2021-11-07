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
	status = 'N';
}

Voter::Voter(string id, string voterName, int voterAge, int div, char voteStatus) {
	voterID = id;
	name = voterName;
	age = voterAge;
	division = div;
	status = voteStatus;
}

string Voter::getVoterId() {
	return voterID;
}

string Voter::getName() {
	return name;
}

int Voter::getAge() {
	return age;
}

int Voter::getDivision() {
	return division;
}

int Voter::getStatus() {
	return status;
}


void Voter::setStatus(char voteStatus) {
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
	bool loginSuccess;
	loginSuccess = login();

	if (loginSuccess == true) {
		//Display all the candidates in the voter's division
		vector<Candidate> candidates = getCandidates();

		for (int i = 0; i < candidates.size(); i++) {
			printCandidatesDetails(candidates[i]);
		}

		cout << endl;

		string candidateID, confirm;

		cout << endl;
		cout << "--------------------" << endl;
		cout << "Vote for a candidate" << endl;
		cout << "--------------------" << endl;
		cout << "\nEnter the candidate's ID: ";
		getline(cin, candidateID);

		cout << "Are you sure (Y/N): ";
		getline(cin, confirm);
	}
	else {
		cout << "Login failed." << endl;
	}
}

//User input validation to ensure that the voter ID is valid, else a message will prompt informing that the input is invalid
bool Voter::login() {
	string id;
	bool idExists;

	while (true) {
		cout << "Voter ID: ";
		getline(cin, id);

		idExists = findVoter(id);

		if (idExists == true) {
			return true;
		}
		else {
			cout << "The voter ID you entered is not registered." << endl;
			return false;
		}
	}
}

//This function is to find the voter in the voter text file
bool Voter::findVoter(string id) {
	ifstream inputStream;
	string fileLine = "";
	vector<string> voterDetails;
	inputStream.open("voter.txt", ifstream::in);

	while (getline(inputStream, fileLine)) {
		char fileLineArray[200];
		strcpy_s(fileLineArray, fileLine.c_str());

		char* remain = fileLineArray;
		char* token;

		while (token = strtok_s(remain, ",", &remain)) {
			voterDetails.push_back(token);
		}
	}

	inputStream.close();

	bool idExists = false;

	for (int i = 0; i < voterDetails.size(); i+=5) {
		string detail = voterDetails[i];
		if (detail == id) {
			idExists = true;
			break;
		}
	}

	//Returns a value based on whether the name exists
	if (idExists == true) {
		return true;
	}
	else {
		return false;
	}
}