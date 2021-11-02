#include "Voter.h"


Voter::Voter(string id, string voterName, int voterAge, int div, char voteStatus) {
	voterID = id;
	name = voterName;
	age = voterAge;
	division = div;
	status = voteStatus;
}

string Voter::getVoterId() {
	return voterID;
}

string Voter::getName() {
	return name;
}

int Voter::getAge() {
	return age;
}

int Voter::getDivision() {
	return division;
}

int Voter::getStatus() {
	return status;
}


void Voter::setStatus(char voteStatus) {
	status = voteStatus;
}


