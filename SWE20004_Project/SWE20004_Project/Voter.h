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
		char status;
		vector<Candidate> getCandidates();
		vector<Candidate> getCandidatesByDivision(int division);
		vector<Voter> getVoters();
		void printCandidateSummary(string candidateID, string name, string party, int vote, double percentage);
		void findCandidate(vector<Candidate> candidates, int totalVotes, int vote);
		void summariseDivisionVoteResult(string divisionPhrase, vector<Candidate> candidates, int totalVotes, int maxVote, int minVote);
		void summariseAllVoteResult(int totalVotes);
		void viewAllVoteResult();
		void viewDivisionVoteResult();
		void printCandidatesDetails(Candidate candidate);
		void viewCandidates();
		void viewCandidatesDivision();
		void viewCandidatesParty();
		string verifyVoter();
		string promptVoterName();
		bool validateVoterName(string name);
		void updateDatabase(Candidate, Voter);
		int promptVoterAge();
		int promptDivision();
		string generateVoterID(string name);
		void inputToFile(string& voterID, string& name, char& status, int& division, int& age);

	public:
		Voter(string id, string voterName, int voterAge, int div, char voteStatus);
		Voter();
		string getVoterId();
		string getName();
		int getAge();
		int getDivision();
		char getStatus();
		void setStatus(char voteStatus);
		void viewVoteResult();
		void viewCandidatesOptions();
		void vote();
		void registerVoter();
		void quit();
};
