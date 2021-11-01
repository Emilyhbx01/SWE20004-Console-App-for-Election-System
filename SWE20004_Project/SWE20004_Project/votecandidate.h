#pragma once

#include <iostream>
#include <vector>
using namespace std;

void displayVoteMenu();
string promptVoteChoice();
string promptSearchDivision();
void viewCandidates();
void registerVoter();
void vote();
vector<string> getCandidates();
void printCandidateSummary(string candidateID, string name, string party, int vote, double percentage);
void findCandidate(vector<string> candidateDetails, int totalVotes, int vote);
void summariseAllVoteResult(string divisionPhrase, vector<string> candidateDetails, int totalVotes, int maxVote, int minVote);
void viewDivisionVoteResult();
void viewAllVoteResult();
void viewVoteResult();
void quit();
void printCandidatesDetails(string& candidateID, string& name, string& party, string& division, string& count);
void viewCandidatesOptions();
void viewCandidates();
void viewCandidatesDivision();
void viewCandidatesParty();
