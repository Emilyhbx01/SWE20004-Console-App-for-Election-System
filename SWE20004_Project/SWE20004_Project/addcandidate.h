#pragma once
#include <iostream>
using namespace std;


void displayAddCandidateMenu();
void inputToFile(string candidateID, string name, string party, int division);
int generateCandidateIdNo();
void viewCandidate();
void addCandidate();

string promptChoice();
string promptCandidateParty();
string promptCandidateName();
string promptDivision();


