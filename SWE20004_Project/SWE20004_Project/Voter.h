#pragma once
#include <iostream>
using namespace std;


class Voter {

	private:
		string voterID;
		string name;
		int age;
		int division;
		char status;

	public:
		Voter(string id, string voterName, int voterAge, int div, char voteStatus);
		string getVoterId();
		string getName();
		int getAge();
		int getDivision();
		int getStatus();
		void setStatus(char voteStatus);
};