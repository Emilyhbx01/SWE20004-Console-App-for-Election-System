#pragma once

#include <iostream>
#include <vector>
#include "Candidate.h"
#include "Voter.h"
using namespace std;

void displayVoteMenu();
string promptVoteChoice();
void registerVoter();
void vote();
void quit();
