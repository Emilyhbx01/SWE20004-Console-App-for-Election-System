/*
Name: Bhagya Priyadarshani Kumari Wijesuriya (101216659)
	  Emily Hong Boon Xuan (101220757)
	  Kelly Jee Li Zhen (102761529)
	  Vernon Chai Chyn Yeong (101223031)
Program Description: This program is a voting system that consists of 2 databases for candidates and voters in .txt files.
					 This part of the program shows the class for voter where the functions used in the voter.cpp.
*/

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
		string status;
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
		Voter(string id, string voterName, int voterAge, int div, string voteStatus);
		Voter();
		string getVoterId();
		string getName();
		int getAge();
		int getDivision();
		string getStatus();
		void setStatus(string voteStatus);
		void viewVoteResult();
		void viewCandidatesOptions();
		vector<Voter> getVoters();
		void vote();
		void changeValues(Candidate, Voter);
		string verifyVoter();
		void registerVoter();
		void quit();
};