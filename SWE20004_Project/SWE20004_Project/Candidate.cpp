#include "Candidate.h"

Candidate::Candidate(string id, string candidateName, string partyName, int div, int noVotes) {
	candidateId = id;
	name = candidateName;
	party = partyName;
	division = div;
	votes = noVotes;
}

string Candidate::getCandidateId() {
	return candidateId;
}

string Candidate::getName() {
	return name;
}

string Candidate::getParty() {
	return party;
}

int Candidate::getDivision() {
	return division;
}

int Candidate::getVotes() {
	return votes;
}

void Candidate::setVotes(int noVotes) {
	votes = noVotes;
}