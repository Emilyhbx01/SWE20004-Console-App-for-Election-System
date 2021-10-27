#include "votecandidate.h"
#include <string>
#include <fstream>
#include <iomanip>

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
	bool valid = false;
	int totalVotes = 0;
	string division;
	vector<string> candidateDetails = getCandidates();
	vector<string> divisionCandidates;
	int minVote = stoi(candidateDetails[4]);
	int maxVote = 0;

	while (!valid) {
		cout << "Division:" << endl;
		getline(cin, division);
		if (division == "1" || division == "2" || division == "3" || division == "4") {
			valid = true;
		}
	}

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


void viewCandidates() {

}

void registerVoter() {

}
void vote() {

}

void quit() {

}


