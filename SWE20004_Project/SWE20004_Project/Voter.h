#pragma once
#include "People.h"



class Voter :public People {
	private:
		string voterID;
		int age;
		char status;

	public:
		Voter(string name_arg, int division_arg, string voterID_arg, int age_arg);
		string getVoterID();
		int getAge();
		char getStatus();
		void setStatus(char status_arg);

};
