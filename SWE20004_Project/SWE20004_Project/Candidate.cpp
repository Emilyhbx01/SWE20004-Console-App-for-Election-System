#include "Candidate.h"

Candidate::Candidate(string name_arg, int division_arg, string candidateID_arg, string party_arg):People(name_arg,division_arg){
	candidateID = candidateID_arg;
	party = party_arg;
}

string Candidate::getCandidateID() {
	return candidateID;
}

string Candidate::getParty() {
	return party;
}

int Candidate::getCount() {
	return count;
}

void Candidate::setCount(int count_arg) {
	count = count_arg;
}
