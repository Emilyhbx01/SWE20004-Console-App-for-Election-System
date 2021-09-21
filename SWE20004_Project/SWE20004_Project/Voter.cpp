#include "Voter.h"


Voter::Voter(string name_arg, int division_arg, string voterID_arg, int age_arg) :People(name_arg, division_arg) {
	voterID = voterID_arg;
	age = age_arg;
	status = 'N';
}

string Voter::getVoterID() {
	return voterID;
}

int Voter::getAge() {
	return age;
}

char Voter::getStatus(){
	return status;
}

void Voter::setStatus(char status_arg) {
	status = status_arg;
}



	

	


