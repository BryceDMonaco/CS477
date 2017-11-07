/*
	Bryce Monaco
	CS 477
	Homework 5

	Compile with: g++ HW5.cpp -o HW5 -std=c++11

	Note: Functions for specific parts ONLY have their respective part after their names (ex. PrintChoicesB is for part B)
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Global Vars
//These values are used for parts b, c, and d
int lowJobs[] = {10, 1, 10, 10};
int highJobs[] = {5, 50, 5, 1};

int numberOfWeeks = 4;

//Global Vars for Part B
char* choicesMade; 	//Choices are stored in order, even though they are evaluated in reverse order
					//The Selection algorithm goes back and appends itself after it evaluates a split in the "decision tree" when a high job is chosen

void PrintChoicesB ();
void PrintChoicesC ();
void PrintScheduleD (int totalRevenue);

//Note: 	SelectBestSchedule is the algorithm for parts B, C, and D. It already stores the choices
//			that it made in choicesMade. Part C and D
int SelectBestSchedule (int weekNumber, char previousChoice, int currentSum, char* theseChoicesMade);
void UpdateChoices (char* forkChoices, char* rootChoices, int forkWeekNumber);

int main ()
{
	choicesMade = new char[numberOfWeeks]; //Used to store choices for part b
	int totalRevenue = SelectBestSchedule (numberOfWeeks - 1, 'X', 0, choicesMade);

	//Part B
	cout << "Best total revenue is $" << totalRevenue << endl;

	PrintChoicesB ();

	//Part C
	cout << endl;

	PrintChoicesC ();

	//Part D
	cout << endl;

	PrintScheduleD (totalRevenue);

	return 0;

}

void PrintChoicesB ()
{
	cout << "Part B output: " << endl << endl;

	cout << "Week: ";
	for (int i = 0; i < numberOfWeeks; i++)
	{
		cout << '\t' << i + 1;

	}

	cout << endl;

	for (int i = 0; i <= numberOfWeeks; i++)
	{
		cout << "--------";

	}

	cout << endl;

	cout << "High: ";
	for (int i = 0; i < numberOfWeeks; i++)
	{
		if (choicesMade[i] == 'H')
		{
			cout << '\t' << "(" << highJobs[i] << ")";

		} else
		{
			cout << '\t' << highJobs[i];

		}

	}

	cout << endl << "Low: ";
	for (int i = 0; i < numberOfWeeks; i++)
	{
		if (choicesMade[i] == 'L')
		{
			cout << '\t' << "(" << lowJobs[i] << ")";

		} else
		{
			cout << '\t' << lowJobs[i];

		}

	}

	cout << endl;

	for (int i = 0; i <= numberOfWeeks; i++)
	{
		cout << "--------";

	}

	cout << endl << "Note:\tThe choice for a week is surrounded with '()'," << endl;
	cout << "\tif a week has no choices then that means that \n\tweek is to be taken off." << endl;


	return;

}

void PrintChoicesC ()
{
	cout << "Part C output: " << endl << endl;

	cout << "Week: ";
	for (int i = 0; i < numberOfWeeks; i++)
	{
		cout << '\t' << i + 1;

	}

	cout << endl;

	for (int i = 0; i <= numberOfWeeks; i++)
	{
		cout << "--------";

	}

	cout << endl;

	cout << "High: ";
	for (int i = 0; i < numberOfWeeks; i++)
	{
		cout << '\t' << highJobs[i];

	}

	cout << endl << "Low: ";
	for (int i = 0; i < numberOfWeeks; i++)
	{
		cout << '\t' << lowJobs[i];

	}

	cout << endl;

	for (int i = 0; i <= numberOfWeeks; i++)
	{
		cout << "--------";

	}

	cout << endl << "Choice: ";
	for (int i = 0; i < numberOfWeeks; i++)
	{
		cout << choicesMade[i] << '\t';

	}

	cout << endl;

	for (int i = 0; i <= numberOfWeeks; i++)
	{
		cout << "--------";

	}

	cout << endl << "Key: 'X' = Take the week off, 'H' = High job, 'L' = Low job" << endl;


	return;

}

void PrintScheduleD (int sentValue)
{
	cout << "Part D Output: " << endl << endl;

	cout << "Best Schedule: (Generated Using Stored Choices):" << endl;

	for (int i = 0; i < numberOfWeeks; i++)
	{
		char choice = choicesMade[i];

		cout << "\tWeek " << i + 1 << ": ";

		if (choice == 'L')
		{
			cout << "Low-Stress Job (Revenue: $" << lowJobs[i] << ")" << endl;

		} else if (choice == 'H')
		{
			cout << "High-Stress Job (Revenue: $" << highJobs[i] << ")" << endl;

		} else if (choice == 'X')
		{
			cout << "Take the week off" << endl;

		}

	}

	cout << "Total Revenue: $" << sentValue << endl;

	cout << endl << "Table of Stored Choices: ";

	for (int i = 0; i < numberOfWeeks; i++)
	{
		cout << choicesMade[i] << '\t';

	}

	cout << endl << "Note:\tThe only extra information needed was the total revenue";
	cout << "\n\twhich was computed recursively as the subproblems were solved.";
	cout << "\n\tThese values are not important to reconstruct the solution so they are discarded." << endl;

	return; 

}

//This works from week i all the way back to week 0
int SelectBestSchedule (int weekNumber, char previousChoice, int currentSum, char* theseChoicesMade)
{
	if (weekNumber == -1)
	{
		return currentSum; //Reached the end

	} else
	{
		if (previousChoice == 'H')
		{
			theseChoicesMade[weekNumber] = 'X';
			return SelectBestSchedule (weekNumber - 1, 'X', currentSum, theseChoicesMade); //Must take a break for this week

		} else
		{
			if (lowJobs[weekNumber] >= highJobs[weekNumber])
			{
				theseChoicesMade[weekNumber] = 'L';
				return SelectBestSchedule (weekNumber - 1, 'L', currentSum + lowJobs[weekNumber], theseChoicesMade); //The low stress job has higher revenue and is always part of the optimal solution

			} else if (highJobs[weekNumber] > lowJobs[weekNumber])
			{
				char* lowForkChoicesMade = new char[numberOfWeeks];
				char* highForkChoicesMade = new char[numberOfWeeks];

				int lowForkSum = SelectBestSchedule (weekNumber - 1, 'L', currentSum + lowJobs[weekNumber], lowForkChoicesMade);
				int highForkSum = SelectBestSchedule (weekNumber - 1, 'H', currentSum + highJobs[weekNumber], highForkChoicesMade);

				if (lowForkSum >= highForkSum)
				{
					UpdateChoices (lowForkChoicesMade, theseChoicesMade, weekNumber - 1);

					theseChoicesMade[weekNumber] = 'L';
					return lowForkSum;

				} else
				{
					UpdateChoices (highForkChoicesMade, theseChoicesMade, weekNumber - 1);

					theseChoicesMade[weekNumber] = 'H';
					return highForkSum;

				}

			}

		}

	}

}

void UpdateChoices (char* forkChoices, char* rootChoices, int forkWeekNumber)
{
	for (int i = 0; i <= forkWeekNumber; i++)
	{
		*(rootChoices + i) = *(forkChoices + i);

	}

	return;

}