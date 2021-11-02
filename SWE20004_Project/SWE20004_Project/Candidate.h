#pragma once
#include <iostream>
using namespace std;

class Candidate {

	private:
		string candidateId;
		string name;
		string party;
		int division;
		int votes;

	public:
		Candidate(string id, string candidateName, string partyName, int div, int noVotes);
		string getCandidateId();
		string getName();
		string getParty();
		int getDivision();
		int getVotes();
		void setVotes(int noVotes);
};