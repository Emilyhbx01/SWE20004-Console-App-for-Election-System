/*
Name: Bhagya Priyadarshani Kumari Wijesuriya (101216659)
	  Emily Hong Boon Xuan (101220757)
	  Kelly Jee Li Zhen (102761529)
	  Vernon Chai Chyn Yeong (101223031)
Date:
Program Description: This program is to add candidate into a database. This part is the header file where the functions are 
					 contained to be used in the main function.
*/
#pragma once
#include <iostream>
using namespace std;


void displayAddCandidateMenu();
void inputToFile(string& candidateID, string& name, string& party, int& division, int& count);
int generateCandidateIdNo();
void viewCandidate();
void addCandidate();
void searchCandidate();

string promptChoice();
string promptCandidateParty();
string promptCandidateName();
string promptDivision();
string generateCandidateID(int& candidateIdNo, string& party);
bool validateCandidateName(string& name);


