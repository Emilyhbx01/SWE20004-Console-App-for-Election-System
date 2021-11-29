/*
Name: Bhagya Priyadarshani Kumari Wijesuriya (101216659)
	  Emily Hong Boon Xuan (101220757)
	  Kelly Jee Li Zhen (102761529)
	  Vernon Chai Chyn Yeong (101223031)
Program Description: This program is a voting system that consists of 2 databases for candidates and voters in .txt files.
					 This part of the program shows the writing of the voter part in the program which includes:
					 1) view candidates details in all division or by specific division or party.
					 2) registering voters.
					 3) voting for candidates by voters.
					 4) view vote results summary in all division or specific division.
					 5) quiiting the program.	 
					
					In this program, there are 2 tables on top of every function to show the summary of the input, output and local variables used 
					and test data.
*/


#include "Voter.h"
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

Voter::Voter() {
	voterID = "";
	name = "";
	age = NULL;
	division = NULL;
	status = 'N';
}

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

char Voter::getStatus() {
	return status;
}

void Voter::setStatus(char voteStatus) {
	status = voteStatus;
}

/*
>> Reading candidate text file
Summary of input, output and local variables                          
---------------------------------------------------------------------------  
| Variables					      | Description                           |  
---------------------------------------------------------------------------  
| local: fileline				  | a text string to output the text file |   
--------------------------------------------------------------------------- 
| local: candidateDetails         | vector to get candidate details from  |   
|								  | the file.			                  |	  
---------------------------------------------------------------------------
| local: candidates               | vector to get candidate details from  |
|								  | class.						   	      |
---------------------------------------------------------------------------
*/
vector<Candidate> Voter::getCandidates() {
	ifstream inputStream;
	string fileLine = "";
	vector<string> candidateDetails;
	vector<Candidate> candidates;
	inputStream.open("candidate.txt", ifstream::in);

	while (getline(inputStream, fileLine)) {
		char fileLineArray[200];
		strcpy_s(fileLineArray, fileLine.c_str());

		//Split line by comma
		char* remain = fileLineArray;
		char* token;
		while (token = strtok_s(remain, ",", &remain)) {
			candidateDetails.push_back(token);
		}
	}
	inputStream.close();

	if (!candidateDetails.empty()) {

		for (int i = 0; i < candidateDetails.size(); i += 5) {
			int nameIndex = i + 1;
			int partyIndex = i + 2;
			int divisionIndex = i + 3;
			int voteIndex = i + 4;
			Candidate candidate(candidateDetails[i], candidateDetails[nameIndex], candidateDetails[partyIndex], stoi(candidateDetails[divisionIndex]), stoi(candidateDetails[voteIndex]));
			candidates.push_back(candidate);
		}
	}
	return candidates;
}

/*
>>This function is the menu options for the view vote results where user can choose to view the result by specific division or all division
Summary of input, output and local variables                          Test Data
-------------------------------------------------------------------   --------------------------------------------------------------------------------------------------
| Variables					      | Description                   |   | Menu Choice | Name         | ID         | Age  | Division  | Status | Description              |
-------------------------------------------------------------------   --------------------------------------------------------------------------------------------------
| input: choice					  | input either 1 or 2 to view   |   | 4, 1        | Walter Lee   | WalterLee  | 34   | 2         | Y      | View voting results by   |
|								  | vote results a division or    |   |             |              |            |      |           |        | a division inputted.     |
|					              | division.                     |   --------------------------------------------------------------------------------------------------
-------------------------------------------------------------------   | 4, 2        | Adam Wong    | AdamWong   |30    | 2         | Y		| View voting results in   |
| output: viewDivisionVoteResult  | go to the function of	   	  |   |   			|			   |			|	   |		   |        | all division.			   |
|								  | viewDivisionVoteResult        |	  --------------------------------------------------------------------------------------------------
-------------------------------------------------------------------
| output: viewAllVoteResult	      | go to the function of         |
|								  | viewAllVoteResult		      |
-------------------------------------------------------------------
| local: valid                    | boolean that is only true when|
|                                 | the choice is 1 or 2          |
-------------------------------------------------------------------
*/
void Voter::viewVoteResult() {
	cout << endl << "------------------" << endl;
	cout << "View Vote Results" << endl;
	cout << "------------------" << endl;

	if (getCandidates().empty()) {
		cout << "No candidates yet. Please try again later" << endl << endl;
	}
	else {
		string choice;
		bool valid = false;
		cout << "1) View voting result of a division" << endl;
		cout << "2) View voting result of all divisions" << endl;
		while (!valid) {
			cout << "Enter your choice:" << endl;
			getline(cin, choice);

			if (choice == "1") {
				viewDivisionVoteResult();
				valid = true;
			}
			else if (choice == "2") {
				viewAllVoteResult();
				valid = true;
			}
			else {
				cout << "Invalid selection, please try again" << endl;
			}
		}
	}
	
}

//Displaying candidate detail for the view vote result
void Voter::printCandidateSummary(string candidateID, string name, string party, int vote, double percentage) {
	cout << "Candidate ID:" << candidateID << endl;
	cout << "Candidate Name:" << name << endl;
	cout << "Party:" << party << endl;
	cout << "Votes:" << vote << endl;
	cout << std::fixed << std::setprecision(2);
	cout << "Percentage:" << percentage << "%" << endl << endl;
}

/*
>>Find all candidate with highest or lowest votes (may have more than 1 candidate)
Summary of input, output and local variables									 Equations:
----------------------------------------------------------------------------	 1.  percentageVote = (candidateVote / totalVotes) * 100
| Variables					      | Description							   | 
----------------------------------------------------------------------------   
| local: candidateVote			  | an integer that is the number of votes |  
|								  | from the text file.					   |    
----------------------------------------------------------------------------   
| local: percentageVote           | a double that is 0.0 initial and will  |   
|								  | be counting the votes in percentage.   |
----------------------------------------------------------------------------
| output: printCandidateSummary   | print the candidates details with      |
|								  | percentage of votes.				   |
----------------------------------------------------------------------------
*/
void Voter::findCandidate(vector<Candidate> candidates, int totalVotes, int vote) {

	for (Candidate candidate : candidates) {
		int candidateVote = candidate.getVotes();
		if (candidateVote == vote) {
			double percentageVote = 0.0;
			if (totalVotes > 0) {
				percentageVote = ((double)candidateVote / (double)totalVotes) * 100;;
			}
			printCandidateSummary(candidate.getCandidateId(), candidate.getName(), candidate.getParty(), candidate.getVotes(), percentageVote);
		}
	}
}

/*
>>Summarise voting result for certain divisions
Summary of input, output and local variables                      
------------------------------------------------------------------------------------------------------------   
| Variables				                        	      | Description					                   |   
------------------------------------------------------------------------------------------------------------   
| output: findCandidate(candidates, totalVotes, maxVote)  | find the candidate that has the maximum        |
|														  | votes from total votes of all the candidates.  |  
------------------------------------------------------------------------------------------------------------   
| output: findCandidate(candidates, totalVotes, minVote)  | find the candidate that has the minimum        |   
|														  | votes from total votes of all the candidates.  |	  
------------------------------------------------------------------------------------------------------------
*/
void Voter::summariseDivisionVoteResult(string divisionPhrase, vector<Candidate> candidates, int totalVotes, int maxVote, int minVote) {
	cout << endl << "Total vote for " << divisionPhrase << ":" << endl << totalVotes << endl;
	cout << endl << "Candidates with highest vote" << ":" << endl;
	findCandidate(candidates, totalVotes, maxVote);
	cout << endl << "Candidates with lowest vote" << ":" << endl;
	findCandidate(candidates, totalVotes, minVote);
}

/*
>>Summarise voting result for all divisions
Summary of input, output and local variables
------------------------------------------------------------------------------------ ------------------------------------------------------------------------------------------------------------
| Variables			         | Description					                       | | Variables				                        	      | Description					                |   
------------------------------------------------------------------------------------ ------------------------------------------------------------------------------------------------------------  
| local: div                 | integer to represent the division where initially 1 | | output: findCandidate(candidates, totalVotes, maxVote)  | find the candidate that has the maximum        |
|							 | for division 1 and loop for 4 times.                | |														   | votes from total votes of all the candidates.  | 
------------------------------------------------------------------------------------ ------------------------------------------------------------------------------------------------------------ 
| local: divisionCandidates  | getting candidates from particular division         | | output: findCandidate(candidates, totalVotes, minVote)  | find the candidate that has the minimum        |  
|                            | according to div.								   | |												   		   | votes from total votes of all the candidates.  |
------------------------------------------------------------------------------------ ------------------------------------------------------------------------------------------------------------
| local: candidateVote       | getting candidates number of votes.			       |
------------------------------------------------------------------------------------
| local: minVote             | integer of initial value of 0 to compare with votes |
|							 | from candidates and the value will be set to the    |
|							 | number of votes from the candidates with the least. |
------------------------------------------------------------------------------------
| local: maxVote			 | integer of initial value of 0 to compare with votes |
|							 | from candidates and the value will be set to the    |
|							 | number of votes from the candidates with the most.  |
------------------------------------------------------------------------------------
| local: totalDivisionVotes  | integer to count the total votes from a division    |
|							 | with initial value of 0.							   |
------------------------------------------------------------------------------------
*/
void Voter::summariseAllVoteResult(int totalVotes) {
	cout << endl << "Total vote for all division:" << endl << totalVotes << endl;
	int div = 1;
	while (div <= 4) 
	{
		vector<Candidate> divisionCandidates = getCandidatesByDivision(div);
		cout << "---------" << "--" << endl;
		cout << "Division " << div << endl;
		cout << "---------" << "--" << endl;

		if (divisionCandidates.empty()) {
			cout << "No candidates in division " << div <<"..." << endl << endl;
		}
		else {
			int minVote = divisionCandidates[0].getVotes();
			int maxVote = 0;
			int totalDivisionVotes = 0;
			for (Candidate candidate : divisionCandidates) {
			
				int candidateVote = candidate.getVotes();
				totalDivisionVotes += candidateVote;

				if (candidateVote < minVote) {
					minVote = candidateVote;
				}
				if (candidateVote > maxVote) {
					maxVote = candidateVote;
				}
			}
			cout << endl << "Total votes:" << endl << totalDivisionVotes << endl;
			cout << endl << "Candidates with highest vote" << ":" << endl;
			findCandidate(divisionCandidates, totalDivisionVotes,maxVote);
			cout << endl << "Candidates with lowest vote" << ":" << endl;
			findCandidate(divisionCandidates, totalDivisionVotes, minVote);
		}
		div++;
	}
}

/*
>>Display voting result for all divisions
Summary of input, output and local variables
--------------------------------------------------------------------------------------------------------
| Variables									     | Description					                       |
--------------------------------------------------------------------------------------------------------
| local: candidateVote						     | getting candidates number of votes.			       |
--------------------------------------------------------------------------------------------------------
| local: minVote						         | integer of initial value of 0 to compare with votes |
|												 | from candidates and the value will be set to the    |
|												 | number of votes from the candidates with the least. |
--------------------------------------------------------------------------------------------------------
| local: maxVote								 | integer of initial value of 0 to compare with votes |
|												 | from candidates and the value will be set to the    |
|												 | number of votes from the candidates with the most.  |
--------------------------------------------------------------------------------------------------------
| local: totalVotes								 | integer to count the total votes from every         |
|												 | division with initial value of 0.		           |
--------------------------------------------------------------------------------------------------------
| output: summariseAllVoteResult(totalVotes)	 | summarise vote results in all division with total   |
|												 | votes.											   |
--------------------------------------------------------------------------------------------------------
*/
void Voter::viewAllVoteResult() {
	vector<Candidate> candidates = getCandidates();
	int totalVotes = 0;
	int minVote = candidates[0].getVotes();
	int maxVote = 0;
	cout << endl << "----------------------" << endl;
	cout << "View All Vote Results" << endl;
	cout << "----------------------" << endl;

	cout << endl << "ID\t" << "Candidate Name\t" << "Votes" << endl;

	for (Candidate candidate : candidates) {
		int candidateVote = candidate.getVotes();
		cout << candidate.getCandidateId() << "\t" << candidate.getName() << "\t" << candidateVote << "\t" << endl;
		totalVotes += candidateVote;
	}
	summariseAllVoteResult(totalVotes);
}

/*
>>Display voting result for certain division
Summary of input, output and local variables
------------------------------------------------------------------------------------------------------------
| Variables											 | Description					                       |
------------------------------------------------------------------------------------------------------------
| local: candidates									 | vector to get candidate details.					   |
------------------------------------------------------------------------------------------------------------
| local: divisionCandidates							 | getting candidates from particular division         |
|													 | according to div.								   |
------------------------------------------------------------------------------------------------------------
| local: totalVotes								     | integer of initial value 0 and will be set to the   |
|													 | total votes recieved from every candidates.         |
------------------------------------------------------------------------------------------------------------
| local: minVote								     | integer of initial value of 0 to compare with votes |
|													 | from candidates and the value will be set to the    |
|													 | number of votes from the candidates with the least. |
------------------------------------------------------------------------------------------------------------
| local: maxVote									 | integer of initial value of 0 to compare with votes |
|													 | from candidates and the value will be set to the    |
|													 | number of votes from the candidates with the most.  |
------------------------------------------------------------------------------------------------------------
| local: division									 | to prompt division in the form of integer.          |
------------------------------------------------------------------------------------------------------------
| local: candidateVotes								 | get number of votes from every candidate.		   |
------------------------------------------------------------------------------------------------------------
| output: summariseDivisionVoteResult(totalVotes)	 | summarise vote results in a division with		   |
|											     	 | division, candidates, total votes, maximum and	   |
|													 | minimum votes.									   |
------------------------------------------------------------------------------------------------------------
*/
void Voter::viewDivisionVoteResult() {
	vector<Candidate> candidates = getCandidates();
	vector<Candidate> divisionCandidates;
	int totalVotes = 0;
	int minVote = candidates[0].getVotes();
	int maxVote = 0;
	int division = promptDivision();
	cout << "------------------------------" << endl;
	cout << "View Vote Results By Division" << endl;
	cout << "------------------------------" << endl;

	divisionCandidates = getCandidatesByDivision(division);
	if (divisionCandidates.empty()) {
		cout << "No candidates in this division..." << endl << endl;
	}

	else {
		cout << endl << "ID\t" << "Candidate Name\t" << "Votes" << endl;
		for (Candidate candidate : divisionCandidates) {
			int candidateVote = candidate.getVotes();
			totalVotes += candidateVote;

			if (candidateVote < minVote) {
				minVote = candidateVote;
			}
			if (candidateVote > maxVote) {
				maxVote = candidateVote;
			}
			cout << candidate.getCandidateId() << "\t" << candidate.getName() << "\t" << candidateVote << "\t" << endl;
		}
		summariseDivisionVoteResult("division " + to_string(division), divisionCandidates, totalVotes, maxVote, minVote);	
	}	
}


/*
>>Get all the candidates in a certain division
Summary of input, output and local variables
------------------------------------------------------------------------------------
| Variables			         | Description					                       |
------------------------------------------------------------------------------------
| local: candidates          | vector to get candidate details.					   |
------------------------------------------------------------------------------------
| local: divisionCandidates  | getting candidates from particular division         |
|                            | according to div.								   |
------------------------------------------------------------------------------------
| output: divisionCandidates | candidates by division is outputted				   |
------------------------------------------------------------------------------------
*/
vector<Candidate> Voter::getCandidatesByDivision(int division) {
	vector<Candidate> candidates = getCandidates();
	vector<Candidate> divisionCandidates = {};
	for (Candidate candidate : candidates) {
		if (candidate.getDivision() == division) {
			divisionCandidates.insert(divisionCandidates.end(), { candidate.getCandidateId(),candidate.getName() ,candidate.getParty(),candidate.getDivision(),candidate.getVotes() });
		}
	}
	return divisionCandidates;
}

//Print candidate details for view candidates
void Voter::printCandidatesDetails(Candidate candidate) {
	cout << "CandidateID:" << candidate.getCandidateId() << endl;
	cout << "Name:" << candidate.getName() << endl;
	cout << "Party:" << candidate.getParty() << endl;
	cout << "Division:" << candidate.getDivision() << endl;
	cout << "Votes:" << candidate.getVotes() << endl << endl;
}

/*
>>Menu options for view candidates details in all division or by specific division or party
Summary of input, output and local variables                          Test Data
-------------------------------------------------------------------   --------------------------------------------------------------------------------------------------
| Variables					      | Description                   |   | Menu Choice | Name         | ID         | Age  | Division  | Status | Description              |
-------------------------------------------------------------------   --------------------------------------------------------------------------------------------------
| input: choice					  | input either 1 or 2 to view   |   | 1, 1        | Lin Yong     | LinYong    | 34   | 2         | Y      | View candidates in all   |
|								  | vote results a division or    |   |             |              |            |      |           |        | division.                |
|					              | division.                     |   --------------------------------------------------------------------------------------------------
-------------------------------------------------------------------   | 1, 2        | Fan Ying Li  | FanYingLi  | 23   | 3         | N   	| View candidates in a	   |
| output: viewCandidates          | go to the function of	   	  |   |   			|			   |			|	   |		   |        | division inputted.	   |
|								  | viewCandidates.               |	  --------------------------------------------------------------------------------------------------
-------------------------------------------------------------------   | 1, 3        | Brenda Wong  | BrendaWong | 45   | 1         | N		| View candidates in a     |
| output: viewCandidatesDivision  | go to the function of         |   |   			|			   |			|	   |		   |        | party inputted.		   |
|								  | viewCandidatesDivision.		  |   --------------------------------------------------------------------------------------------------
-------------------------------------------------------------------
| output: viewCandidatesParty     | go to the function of         |
|								  | viewCandidatesParty.		  |
-------------------------------------------------------------------
| local: valid                    | boolean that is only true when|
|                                 | the choice is 1 or 2          |
-------------------------------------------------------------------
*/
void Voter::viewCandidatesOptions() {
	string choice;
	cout << endl << "----------------" << endl;
	cout << "View Candidates" << endl;
	cout << "----------------" << endl;

	if (getCandidates().empty()) {
		cout << "No candidates yet. Please try again later" << endl << endl;
	}
	else{
		cout << "1) View candidates in all divisions" << endl;
		cout << "2) View candidates in specific divisions" << endl;
		cout << "3) View candidates in specific party" << endl;
		bool valid = false;
		while (!valid) {
			cout << "Enter your choice:" << endl;
			getline(cin, choice);

			if (choice == "1") {
				viewCandidates();
				valid = true;
			}
			else if (choice == "2") {
				viewCandidatesDivision();
				valid = true;
			}
			else if (choice == "3") {
				viewCandidatesParty();
				valid = true;
			}
			else {
				cout << "Invalid selection, please try again" << endl;
			}
		}
	}
}

/*
>>View all candidates in all division
Summary of input, output and local variables
---------------------------------------------------------------------------------------------------
| Variables								    | Description					                      |
---------------------------------------------------------------------------------------------------
| local: found							    | boolean that is only true if the candidate file is  |
|										    | found.                                              |
---------------------------------------------------------------------------------------------------
| local: candidates						    | getting every candidate from every division.        |
---------------------------------------------------------------------------------------------------
| output: printCandidatesDetails(candidate) | every candidates is outputted.					  |
---------------------------------------------------------------------------------------------------
*/
void Voter::viewCandidates() {
	bool found = false;
	cout << endl << "--------------------" << endl;
	cout << "View All Candidates" << endl;
	cout << "--------------------" << endl;
	vector<Candidate> candidates = getCandidates();

	for (Candidate candidate : candidates) {
		printCandidatesDetails(candidate);
		found = true;
	}
	if (!found) {
		cout << "No candidates available..." << endl << endl;
	}
}


/*
>>View candidate by specific division
Summary of input, output and local variables
-----------------------------------------------------------------------------------------------------
| Variables								    | Description					                        |
-----------------------------------------------------------------------------------------------------
| local: found							    | boolean that is only true if the candidate file is    |
|										    | found.                                                |
-----------------------------------------------------------------------------------------------------
| local and input : searchDivision		    | will prompt promptDivision function where user input  |
|										    | can happened to view candidates in a desired division.|
-----------------------------------------------------------------------------------------------------
| output: printCandidatesDetails(candidate) | every candidates of a divivision is outputted.	    |
-----------------------------------------------------------------------------------------------------
| local: candidates						    | getting every candidate details.			            |
-----------------------------------------------------------------------------------------------------
*/
void Voter::viewCandidatesDivision() {
	bool found = false;
	vector<Candidate> candidates = getCandidates();
	int searchDivision = promptDivision();
	cout << endl << "----------------------------" << endl;
	cout << "View Candidates By Division" << endl;
	cout << "----------------------------" << endl;
	
	for (Candidate candidate : candidates) {
		if (candidate.getDivision() == searchDivision) {
			printCandidatesDetails(candidate);
			found = true;
		}
	}

	if (!found) {
		cout << "No candidates available..." << endl << endl;
	}
}

/*
>>View candidate by specific party
Summary of input, output and local variables
-----------------------------------------------------------------------------------------------------
| Variables								    | Description					                        |
-----------------------------------------------------------------------------------------------------
| local: found							    | boolean that is only true if the candidate file is    |
|										    | found.                                                |
-----------------------------------------------------------------------------------------------------
| local and input: searchParty			    | allow user to input the party for the candidates they |
|										    | want to view.											|
-----------------------------------------------------------------------------------------------------
| output: printCandidatesDetails(candidate) | every candidates of a divivision is outputted.	    |
-----------------------------------------------------------------------------------------------------
| local: candidates						    | getting every candidate details.			            |
-----------------------------------------------------------------------------------------------------
*/
void Voter::viewCandidatesParty() {
	string searchParty;
	bool found = false;
	vector<Candidate> candidates = getCandidates();
	cout << "Party name: " << endl;
	getline(cin, searchParty);
	transform(searchParty.begin(), searchParty.end(), searchParty.begin(), ::tolower);

	cout << endl << "-------------------------" << endl;
	cout << "View Candidates By Party" << endl;
	cout << "-------------------------" << endl;

	for (Candidate candidate : candidates) {
		string candidateParty = candidate.getParty();
		transform(candidateParty.begin(), candidateParty.end(), candidateParty.begin(), ::tolower);
		if (candidateParty == searchParty) {
			printCandidatesDetails(candidate);
			found = true;
		}
	}

	if (!found) {
		cout << "No candidates available..." << endl << endl;
	}
}

/*
>>Vote for candidates
Summary of input, output and local variables                          Test Data
---------------------------------------------------------------------   ----------------------------------------------------------------------------------------------------
| Variables					      | Description                     |   | Menu Choice | Name          | ID          | Age | Division  | Status | Description               |
---------------------------------------------------------------------   ----------------------------------------------------------------------------------------------------
| local: voters					  | get voters details.             |   |             | Boon Wen Chin | BoonWenChin | 87  | 1         | Y      | Display candidates in the |
---------------------------------------------------------------------   |             |               |             |     |           |        | same division and vote.   |              |
| local voterID                   | to verify the voterID inputted. |   -----------------------------------------------------------------------------------------------------
---------------------------------------------------------------------   
| local and input: candidateID    | input candidate ID to vote and  |   
|								  | to verify voter division and    |
|								  | candidate division is the same. |
---------------------------------------------------------------------   
| local and input: confirm        | input Y or N to confirm voting  |  
|								  | for the inputted candidate.	    |   
---------------------------------------------------------------------
| local: candidateExists          | boolean that is only true when  |
|								  | the candidate ID is valid.	    |
---------------------------------------------------------------------
| local: candidates				  | getting every candidate details |
|								  | from class.                     |
---------------------------------------------------------------------
| local: loop        			  | boolean that is only true when  |
|                                 | candidateExists is false.       |
---------------------------------------------------------------------
*/
void Voter::vote() {
	cout << endl << "---------------------" << endl;
	cout << "Vote For A Candidate" << endl;
	cout << "---------------------" << endl;
	//Get the voter
	vector<Voter> voters = getVoters();

	if (voters.empty()) {
		cout << "No voters yet. Please try again later" << endl << endl;
	}
	else {
		string voterID, candidateID, confirm;
		Voter myVoter;
		bool candidateExists = false;
		voterID = verifyVoter();

		//Proceed when voter has been verified
		if (voterID != "q") {
			if (!voterID.empty()) {
				for (Voter v : voters) {
					string vID = v.getVoterId();
					transform(vID.begin(), vID.end(), vID.begin(), ::tolower);

					if (vID == voterID)
						myVoter = v;
				}

				//Display all the candidates in the voter's division
				vector<Candidate> candidates = getCandidates();
				cout << endl << "-----------------------------" << endl;
				cout << "Candidates Available To Vote" << endl;
				cout << "-----------------------------" << endl;
				for (Candidate c : candidates) {
					if (c.getDivision() == myVoter.getDivision()) {
						cout << "CandidateID:" << c.getCandidateId() << endl;
						cout << "Name:" << c.getName() << endl;
						cout << "Party:" << c.getParty() << endl << endl;
					}

				}

				//Checks if the voter has already voted or not
				if (myVoter.getStatus() == 'N') {

					while (true) {
						bool loop = true;

						cout << "\nEnter the candidate's ID (Q: Exit):" << endl;
						getline(cin, candidateID);
						transform(candidateID.begin(), candidateID.end(), candidateID.begin(), ::tolower);

						//Exits the voting section
						if (candidateID == "Q" || candidateID == "q") {
							break;
						}

						//Checks if the candidate ID is valid and in the same division as the voter
						for (Candidate c : candidates) {
							string id = c.getCandidateId();
							transform(id.begin(), id.end(), id.begin(), ::tolower);

							if (candidateID == id && c.getDivision() == myVoter.getDivision()) {
								//Gets the voters confirmation on their vote
								while (true) {
									cout << "Are you sure (Y/N): ";
									getline(cin, confirm);

									if (confirm == "Y" || confirm == "y") {
										updateDatabase(c, myVoter);

										//Provide voting feedback to the voter
										cout << "\nThank you for voting " + myVoter.getName() + "." << endl;
										cout << "You have successfully voted for " + c.getCandidateId() + " " + c.getName() + ".\n" << endl;

										loop = false;

										break;
									}
									else if (confirm == "N" || confirm == "n") {
										break;
									}
									else {
										cout << "Invalid selection, please try again." << endl;
									}
								}
								candidateExists = true;
								break;
							}
						}

						//Breaks the loop once the vote succeeds
						if (loop == false)
							break;

						//Displays an error message if the candidate could not be found
						if (candidateExists == false) {
							cout << "The candidate could not be found. Please try again." << endl;
						}
					}
				}
				else {
					cout << "You have already voted..." << endl << endl;
				}
			}
			else {
				cout << "Login failed." << endl;
			}
		}
	}
}

/*
>>Increases the vote count for the candidate and the voters voting status in their respective text files
Summary of input, output and local variables
-----------------------------------------------------------------------------------------------------
| Variables								    | Description					                        |
-----------------------------------------------------------------------------------------------------
| local: voters							    | getting every voters details.						    |
-----------------------------------------------------------------------------------------------------
| local: candidates						    | getting every candidate details.			            |
-----------------------------------------------------------------------------------------------------
*/
void Voter::updateDatabase(Candidate candidate, Voter voter) {
	vector<Candidate> candidates = getCandidates();
	vector<Voter> voters = getVoters();
	ofstream outputStream;

	outputStream.open("candidate.txt", ofstream::out);

	//Increases the vote count of the candidate in the candidate text file
	if (outputStream.is_open()) {
		for (int i = 0; i < candidates.size(); i++) {
			if (candidates[i].getCandidateId() == candidate.getCandidateId())
			{
				Candidate updatedCandidate = candidates[i];
				updatedCandidate.setVotes(updatedCandidate.getVotes() + 1);
				candidates[i] = updatedCandidate;
				break;
			}
		}

		for (Candidate c : candidates) {
			outputStream << c.getCandidateId() + "," + c.getName() + "," << c.getParty() + "," + to_string(c.getDivision()) + "," + to_string(c.getVotes()) << endl;
		}

	}
	else{
		cout << "Error: The candidate text file could not be opened." << endl;
	}

	outputStream.close();
	outputStream.open("voter.txt", ofstream::out);

	//Sets the voters voting status to voted in the voter text file
	if (outputStream.is_open()) {
		for (int i = 0; i < voters.size(); i++) {
			if (voters[i].getVoterId() == voter.getVoterId()) {
				Voter updatedVoter = voters[i];
				updatedVoter.setStatus('Y');
				voters[i] = updatedVoter;
				break;
			}
		}

		for (Voter v : voters) {
			outputStream << v.getVoterId() << "," << v.getName() << "," << v.getAge() << "," << v.getDivision() << "," << v.getStatus() << endl;
		}
		
	}
	else {
		cout << "Error: The voter text file could not be opened." << endl;
	}

	outputStream.close();
}

/*
>>Verifies that the voter ID given is valid and returns the voter ID
Summary of input, output and local variables
-----------------------------------------------------------------------------------------------------
| Variables								    | Description					                        |
-----------------------------------------------------------------------------------------------------
| local & input: id  					    | input the voter ID to verify the ID is valid.		    |
-----------------------------------------------------------------------------------------------------
| local: idExists   					    | boolean that is only true when the voter ID is verify.|
-----------------------------------------------------------------------------------------------------
*/
string Voter::verifyVoter() {
	string id;
	Voter myVoter;
	bool idExists = false;

	while (true) {
		cout << endl << "Voter ID (Q: Exit): " << endl;
		getline(cin, id);
		transform(id.begin(), id.end(), id.begin(), ::tolower);

		//Exits the function
		if (id == "q")
			return "q";

		vector<Voter> voters = getVoters();

		for (Voter v : voters) {
			string voterID = v.getVoterId();
			transform(voterID.begin(), voterID.end(), voterID.begin(), ::tolower);
			
			if (voterID == id) {
				myVoter = v;
				idExists = true;
			}
		}

		//Only returns a value when the Voter ID is found
		if (idExists)
			return id;
		else
			cout << "The voter ID you entered is not registered. Please try again." << endl;
	}
}

/*
>>Get the voters details from the voter text file
Summary of input, output and local variables
---------------------------------------------------------------------------
| Variables					      | Description                           |
---------------------------------------------------------------------------
| local: fileline				  | a text string to output the text file |
---------------------------------------------------------------------------
| local: voterDetails             | vector to get voters details from the |
|								  | the file.                             |
---------------------------------------------------------------------------
| local: voters                   | vector to get voters details from the |
|								  | class.					    	      |
---------------------------------------------------------------------------
*/
vector<Voter> Voter::getVoters() {
	ifstream inputStream;
	string fileLine = "";
	vector<string> voterDetails;
	vector<Voter> voters;

	inputStream.open("voter.txt", ifstream::in);

	while (getline(inputStream, fileLine)) {
		char fileLineArray[200];
		strcpy_s(fileLineArray, fileLine.c_str());

		//Split line by comma
		char* remain = fileLineArray;
		char* token;
		while (token = strtok_s(remain, ",", &remain)) {
			voterDetails.push_back(token);
		}
	}

	inputStream.close();

	if (!voterDetails.empty()) {
		for (int i = 0; i < voterDetails.size(); i += 5) {
			int name = i + 1, age = i + 2, div = i + 3, vote = i + 4;
			char status = voterDetails[vote][0]; //convert string to char
			Voter voter(voterDetails[i], voterDetails[name], stoi(voterDetails[age]), stoi(voterDetails[div]), status);
			voters.push_back(voter);
		}
	}

	return voters;
}

/*
>>This function is the menu options for the register voters
Summary of input, output and local variables                          Test Data
--------------------------------------------------------------------   --------------------------------------------------------------------------------------------------
| Variables					      | Description                    |   | Menu Choice | Name         | ID         | Age  | Division  | Status | Description              |
--------------------------------------------------------------------   --------------------------------------------------------------------------------------------------
| local & input: choice		      | prompt promptVoterName and     |   | 2           | Amy Xu       | AmyXu      | 20   | 4         | N      | Registration done by     |
|								  | user can input name.           |   |             |              |            |      |           |        | filling details.         |   
--------------------------------------------------------------------   --------------------------------------------------------------------------------------------------
| local: voterID                  | to generate voter ID.	       | 
--------------------------------------------------------------------
| local & input: division         | prompt promptDivision and user |
|								  | input division.  		       |
--------------------------------------------------------------------
| local & input: age              | prompt promptVoterAge and user |
|                                 | input age.                     |
--------------------------------------------------------------------
| local: status                   | status is set to N for newly   |
|                                 | registered voter.              |
--------------------------------------------------------------------
| output: inputToFile             | output voter details into file.|
--------------------------------------------------------------------
*/
void Voter::registerVoter() {
	string name,voterID;
	int division, age;
	char status;
	cout << endl << "--------------------" << endl;
	cout << "Register As A Voter" << endl;
	cout << "--------------------" << endl;
	cout << "Welcome!" << endl;
	cout << "This section is for voter registration." << endl;
	cout << "Please fill each field correctly." << endl;
	cout << endl;

	name = promptVoterName();
	bool nameExists = validateVoterName(name); // check if voter name already exists in text file

	if (!nameExists) {
		age = promptVoterAge();

		if (age >= 19)
		{
			division = promptDivision();
			status = 'N';
			voterID = generateVoterID(name);
			inputToFile(voterID, name, status, division, age);
		}
		else
		{
			cout << "You are not eligible to vote...Voter must be 19 years old and above" << endl << endl;
		}
	}
	else {
		cout << "Voter's name is already registered." << endl << endl;
	}
}

/*
>>This function is for the user to input their name in the form of string
Summary of input, output and local variables
----------------------------------------------------------------------------
| Variables					      | Description                            |
----------------------------------------------------------------------------
| local & input: name			  | input where the user input their name. |
----------------------------------------------------------------------------
| local: valid                    | boolean where it is only true when the |
|								  | input is alpha and space.              |
----------------------------------------------------------------------------
| local: letter                   | character where the input is verified  |
|								  | as letter and space.			       |
----------------------------------------------------------------------------
*/
string Voter::promptVoterName() {
	string name;
	bool valid = false;

	while (!valid) {
		cout << endl << "Name of voter:" << endl;
		getline(cin, name);
		for (unsigned int i = 0; i < name.length(); i++) {
			char letter = name[i];

			if (isalpha(letter) || isspace(letter)){
				valid = true;
			}
			else{
				cout << "Invalid input...Voter name can only have alphas" << endl;
				valid = false;
				break;
			}
		}

	}
	return name;
}

/*
>>This function is for the user to input their age to check eligibilty for voting
Summary of input, output and local variables
-----------------------------------------------------------------------------
| Variables					      | Description                             |
-----------------------------------------------------------------------------
| local: age		         	  | integer where the age is kept after     |
|								  | transform from string.					|
-----------------------------------------------------------------------------
| local: valid                    | boolean where it is only true when the  |
|								  | age in integer.			                |
-----------------------------------------------------------------------------
| output: age		              | output age that is integer form.        |
-----------------------------------------------------------------------------
| local & input: ageString        | input where user input their age as     |
|								  | string.      			                |
-----------------------------------------------------------------------------
*/
int Voter:: promptVoterAge() {
	int age;
	bool valid = false;

	while (!valid) {
		string ageString;
		cout << endl << "Enter Voter's Age:" << endl;
		getline(cin, ageString);

		try {
			age = stoi(ageString);
			valid = true;
		}
		catch (exception e) {
			cout << "Invalid input...Please try again" << endl;
		}
	}
	return age;
}

/*
>>This function is for the user to input their division in the form of string
Summary of input, output and local variables
------------------------------------------------------------------------------------
| Variables					      | Description                                    |
------------------------------------------------------------------------------------
| local: division		          | integer where the division is kept after	   |
|								  | transform from string.						   |
------------------------------------------------------------------------------------
| local: valid                    | boolean where it is only true when the         |
|								  | division in integer and only input of 1  to 4. |
------------------------------------------------------------------------------------
| input: divisionString		      | user input their division as string form.      |
------------------------------------------------------------------------------------
| output: division				  | division is outputted in the form of integer.  |
------------------------------------------------------------------------------------
*/
int Voter:: promptDivision() {
	int division;
	bool valid = false;
	string divisionString;
	while (!valid) {
		
		cout << endl << "Division:" << endl;
		getline(cin, divisionString);
		if (divisionString == "1" || divisionString == "2" || divisionString == "3" || divisionString == "4") {
			division = stoi(divisionString);
			valid = true;
		}
		else {
			cout << "Please enter the correct division (1~4)." << endl;
		}
	}
	cout << endl;
	return division;
}

//This function generate the voter ID
string Voter:: generateVoterID(string name) {
	name.erase(remove(name.begin(), name.end(), ' '), name.end());
	return name;
}

//This function is to convert the candidates information into.txt file storing into database
void Voter::inputToFile(string& voterID, string& name, char& status, int& division, int& age) {
	string outputFilename = "voter.txt";
	string voterDetails = voterID + "," + name + "," + to_string(age) + "," + to_string(division) + "," + status;
	ofstream outputStream;
	outputStream.open(outputFilename, ofstream::app);

	if (outputStream.is_open()) {
		outputStream << voterDetails << endl;
		cout << "Successful registration..." << endl << endl;
	}
	else {
		cerr << "File cannot be opened" << endl;
	}
	outputStream.close();
}

/*
>>This function is to check if the voter's name is already exists in the database
Summary of input, output and local variables
---------------------------------------------------------------------------------------
| Variables					      | Description                                       |
---------------------------------------------------------------------------------------
| local: voters  		          | getting voters details from class.			      |
---------------------------------------------------------------------------------------
| local: voterName                | get voter name to verify whether the name exists. |
---------------------------------------------------------------------------------------
| local & output: nameExits		  | boolean where it is only true is the voter name   |
|								  | does not exist and output it.					  |
---------------------------------------------------------------------------------------
*/
bool Voter::validateVoterName(string name) {
	vector<Voter> voters = getVoters();

	bool nameExists = false;
	transform(name.begin(), name.end(), name.begin(), ::tolower);
	
	for (Voter voter:voters) {
		string voterName = voter.getName();
		transform(voterName.begin(), voterName.end(), voterName.begin(), ::tolower);
		if (voterName == name) {
			nameExists = true;
			break;
		}
	}

	return nameExists;
}

//This function prints out the description when program quit	
void Voter::quit() {
	cout << "Thank you for using this program. Goodbye!" << endl;
}
