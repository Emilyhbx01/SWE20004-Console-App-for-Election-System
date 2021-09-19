#include "Voter.h"


Voter::Voter(string name_arg, int division_arg, string voterID_arg, int age_arg) :People(name_arg, division_arg) {
	voterID = voterID_arg;
	age = age_arg;
	status = 'N';
}

string Voter::GetVoterID() {
	return voterID;
}

int Voter::GetAge() {
	return age;
}

char Voter::GetStatus(){
	return status;
}

void Voter::SetStatus(char status_arg) {
	status = status_arg;
}



	

	


