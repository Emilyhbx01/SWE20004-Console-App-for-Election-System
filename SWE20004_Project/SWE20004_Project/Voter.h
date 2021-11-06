#pragma once
#include <iostream>
#include <vector>
#include "Candidate.h"
using namespace std;


class Voter {

	private:
		string voterID;
		string name;
		int age;
		int division;
		char status;
		vector<Candidate> getCandidates();
		string promptSearchDivision();
		void printCandidateSummary(string candidateID, string name, string party, int vote, double percentage);
		void findCandidate(vector<Candidate> candidates, int totalVotes, int vote);
		void summariseAllVoteResult(string divisionPhrase, vector<Candidate> candidates, int totalVotes, int maxVote, int minVote);
		void viewAllVoteResult();
		void viewDivisionVoteResult();
		void printCandidatesDetails(Candidate candidate);
		void viewCandidates();
		void viewCandidatesDivision();
		void viewCandidatesParty();

	public:
		Voter(string id, string voterName, int voterAge, int div, char voteStatus);
		Voter();
		string getVoterId();
		string getName();
		int getAge();
		int getDivision();
		int getStatus();
		void setStatus(char voteStatus);
		void viewVoteResult();
		void viewCandidatesOptions();
		void vote();
		bool login();
		bool findVoter(string);
};