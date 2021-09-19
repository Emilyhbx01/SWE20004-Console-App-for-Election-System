#pragma once
#include "People.h"

class Candidate :public People {
private:
	string candidateID;
	string party;
	int count;

public:
	Candidate(string name_arg, int division_arg, string candidateID_arg, string party_arg);

	string GetCandidateID();

	string GetParty();

	int GetCount();

	void SetCount(int count_arg);
};