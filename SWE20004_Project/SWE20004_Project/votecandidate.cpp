#include "votecandidate.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>

void displayVoteMenu() {
	cout << endl << "1) View Candidates" << endl;
	cout << "2) Register Voter" << endl;
	cout << "3) Vote" << endl;
	cout << "4) View Voting Results and Summary" << endl;
	cout << "5) Quit" << endl;
}

string promptVoteChoice() {
	string choice;
	bool valid = false;

	while (!valid) {
		cout << endl << "Enter your choice:\n";
		getline(cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4") {
			valid = true;
		}
		else {
			cout << "Invalid selection, please try again\n";
		}

	}
	return choice;
}

vector<string> getCandidates() {
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

string promptSearchDivision() {
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


void viewVoteResult() {
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

//display candidate detail
void printCandidateSummary(string candidateID,string name, string party, int vote, double percentage) {
	cout << "Candidate ID:" << candidateID << endl;
	cout << "Candidate Name:" << name << endl;
	cout << "Party:" << party<< endl;
	cout << "Votes:" << vote << endl;
	cout << std::fixed << std::setprecision(2);
	cout << "Percentage:" << percentage << "%" << endl << endl;
}

//find all candidate with highest or lowest votes (may have more than 1 candidate)
void findCandidate(vector<string> candidateDetails,int totalVotes,int vote) {
	for (int i = 0; i < candidateDetails.size(); i += 5) {
		int voteIndex = i + 4;
		int candidateVote = stoi(candidateDetails[voteIndex]);
		if (candidateVote == vote) {
			int nameIndex = i + 1;
			int partyIndex = i + 2;
			double percentageVote = 0.0;
			if (totalVotes > 0) {
				percentageVote = (double(candidateVote) /(double) totalVotes) * 100;;
			}
			printCandidateSummary(candidateDetails[i], candidateDetails[nameIndex], candidateDetails[partyIndex], candidateVote, percentageVote);
		}
	}
}

//summarise voting result for all divisions
void summariseAllVoteResult(string divisionPhrase,vector<string> candidateDetails, int totalVotes, int maxVote,int minVote) {
	cout << endl << "Total vote for " << divisionPhrase << ":" << endl << totalVotes << endl;
	cout << endl << "Candidates with highest vote" << ":" << endl;
	findCandidate(candidateDetails, totalVotes, maxVote);
	cout << endl << "Candidates with lowest vote" << ":" << endl;
	findCandidate(candidateDetails, totalVotes, minVote);
}


//display voting result for all divisions
void viewAllVoteResult() {
	vector<string> candidateDetails = getCandidates();
	int totalVotes = 0;
	int minVote = stoi(candidateDetails[4]);
	int maxVote = 0;
	cout << endl << "ID\t" << "Candidate Name\t" << "Votes" << endl;
	for (int i = 0; i < candidateDetails.size(); i += 5) {
		
		int voteIndex = i + 4;
		int nameIndex = i + 1;
		int candidateVote = stoi(candidateDetails[voteIndex]);
		string candidateName = candidateDetails[nameIndex];
		string candidateID = candidateDetails[i];
		cout << candidateID <<  "\t" << candidateName << "\t" << candidateVote << "\t" << endl;
		totalVotes += candidateVote;

		if (candidateVote < minVote) {
			minVote = candidateVote;
		}
		
		if (candidateVote > maxVote) {
			maxVote = candidateVote;
		}
		
	}
	summariseAllVoteResult("all divisions",candidateDetails, totalVotes, maxVote, minVote);


}

//display voting result for certain division
void viewDivisionVoteResult() {

	int totalVotes = 0;
	vector<string> candidateDetails = getCandidates();
	vector<string> divisionCandidates;
	int minVote = stoi(candidateDetails[4]);
	int maxVote = 0;
	string division = promptSearchDivision();

	cout << endl << "Candidate Name\t" << "Votes" << endl;
	for (int i = 0; i < candidateDetails.size(); i += 5) {
		int divIndex = i + 3;
		if (candidateDetails[divIndex] == division) {
			int voteIndex = i + 4;
			int nameIndex = i + 1;
			int partyIndex = i + 2;
			int candidateVote = stoi(candidateDetails[voteIndex]);
			string candidateName = candidateDetails[nameIndex];
			divisionCandidates.insert(divisionCandidates.end(), { candidateDetails[i],candidateName,candidateDetails[partyIndex],candidateDetails[divIndex],candidateDetails[voteIndex]});
			string candidateID = candidateDetails[i];
			cout << candidateID << "\t" << candidateName << "\t" << candidateVote << "\t" << endl;
			totalVotes += candidateVote;

			if (candidateVote < minVote) {
				minVote = candidateVote;
			}
		    if (candidateVote > maxVote) {
				maxVote = candidateVote;
			}
		}
	}

	summariseAllVoteResult("division " + division,divisionCandidates, totalVotes, maxVote, minVote);

}

//Print candidate details
void printCandidatesDetails(string& candidateID, string& name, string& party, string& division, string& count) {
	cout << endl << "CandidateID:" << candidateID << endl;
	cout << "Name:" << name << endl;
	cout << "Party:" << party << endl;
	cout << "Division:" << division << endl;
	cout << "Count:" << count << endl << endl;
}

void viewCandidatesOptions() {
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

//View all candidates
void viewCandidates() {
	cout << endl << "Welcome!" << endl;
	cout << "This section is to view all candidates" << endl << endl;
	vector<string> candidateDetails = getCandidates();

	for (int i = 0; i < candidateDetails.size(); i += 5) {
		int nameIndex = i + 1;
		int partyIndex = i + 2;
		int divisionIndex = i + 3;
		int countIndex = i + 4;

		printCandidatesDetails(candidateDetails[i], candidateDetails[nameIndex], candidateDetails[partyIndex], candidateDetails[divisionIndex], candidateDetails[countIndex]);
	}
	cout << endl;
}


//View candidate by division
void viewCandidatesDivision() {

	bool found = false;
	vector<string> candidateDetails = getCandidates();
	string searchDivision = promptSearchDivision();

	for (int i = 0; i < candidateDetails.size(); i += 5) {
		int divisionIndex = i + 3;
		string division = candidateDetails[divisionIndex];
		if (division == searchDivision) {
				int nameIndex = i + 1;
				int partyIndex = i + 2;
				int countIndex = i + 4;
				printCandidatesDetails(candidateDetails[i], candidateDetails[nameIndex], candidateDetails[partyIndex], candidateDetails[divisionIndex], candidateDetails[countIndex]);
				found = true;
		}
	}

	if (!found) {
		cout << "No candidates available..." << endl << endl;
	}
}

//View candidate by party
void viewCandidatesParty() {
	string searchParty;
	bool found = false;
	vector<string> candidateDetails = getCandidates();

	cout << "Party name: " << endl;
	getline(cin, searchParty);
	transform(searchParty.begin(), searchParty.end(), searchParty.begin(), ::tolower);

	for (int i = 0; i < candidateDetails.size(); i += 5) {
		int partyIndex = i + 2;
		string party = candidateDetails[partyIndex];
		transform(party.begin(), party.end(), party.begin(), ::tolower);
		if (party == searchParty) {
			int nameIndex = i + 1;
			int divisionIndex = i + 3;
			int countIndex = i + 4;
			printCandidatesDetails(candidateDetails[i], candidateDetails[nameIndex], candidateDetails[partyIndex], candidateDetails[divisionIndex], candidateDetails[countIndex]);
			found = true;
		}
	}

	if (!found) {
		cout << "No candidates available..." << endl << endl;
	}
}

void registerVoter() {
	string name, age, voterID;
	int division, status;
	int count = 0;
	bool validVoterName;


	//Register Voter Option [2] Description
	cout << endl << "Welcome!" << endl;
	cout << "This section is for voter registration." << endl;
	cout << "Please fill each field correctly." << endl;
	cout << endl;

}

void vote() {

}


void quit() {
	cout << "Thank you for using this program. Goodbye!" << endl;
}

