#include "Candidate.h"

Candidate::Candidate(string name_arg, int division_arg, string candidateID_arg, string party_arg):People(name_arg,division_arg){
	candidateID = candidateID_arg;
	party = party_arg;
}

string Candidate::GetCandidateID() {
	return candidateID;
}

string Candidate::GetParty() {
	return party;
}

int Candidate::GetCount() {
	return count;
}

void Candidate::SetCount(int count_arg) {
	count = count_arg;
}
