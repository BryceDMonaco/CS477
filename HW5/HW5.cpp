/*
	Bryce Monaco
	CS 477
	Homework 5

	Compile with: g++ HW5.cpp -o HW5 -std=c++11

	Note: Functions for each part have their respective part after their names (ex. SelectBestScheduleB is for part B)
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Global Vars
//These values are used for parts b, c, and d
int lowJobs[] = {10, 1, 10, 10};
int highJobs[] = {5, 50, 5, 1};

vector<char> choicesB;
char* choicesMade;

void PrintChoicesB (); //This is hardcoded to print four choices!!!
int SelectBestScheduleB (int weekNumber, char previousChoice, int currentSum);

int main ()
{
	int numberOfWeeks = 4;
	choicesMade = new char[numberOfWeeks];

	cout << "Best total revenue is $" << SelectBestScheduleB (numberOfWeeks - 1, 'X', 0) << endl;

	PrintChoicesB ();

	return 0;

}

void PrintChoicesB ()
{
	cout << "Part B output: " << endl << endl;

	cout << "Week: ";
	for (int i = 0; i < 4; i++)
	{
		cout << '\t' << i + 1;

	}

	cout << endl;

	for (int i = 0; i <= 4; i++)
	{
		cout << "--------";

	}

	cout << endl;

	cout << "High: ";
	for (int i = 0; i < 4; i++)
	{
		cout << '\t' << highJobs[i];

	}

	cout << endl << "Low: ";
	for (int i = 0; i < 4; i++)
	{
		cout << '\t' << lowJobs[i];

	}

	cout << endl;

	for (int i = 0; i <= 4; i++)
	{
		cout << "--------";

	}

	cout << endl << "Choice: ";
	for (int i = 0; i < 4; i++)
	{
		cout << choicesMade[i] << '\t';

	}

	cout << endl;

	for (int i = 0; i <= 4; i++)
	{
		cout << "--------";

	}

	cout << endl << "Key: 'X' = Take the week off, 'H' = High job, 'L' = Low job" << endl;


	return;

}

//This works from week i all the way back to week 0
int SelectBestScheduleB (int weekNumber, char previousChoice, int currentSum)
{
	if (weekNumber == -1)
	{
		return currentSum; //Reached the end

	} else
	{
		if (previousChoice == 'H')
		{
			choicesMade[weekNumber] = 'X';
			return SelectBestScheduleB (weekNumber - 1, 'X', currentSum); //Must take a break for this week

		} else
		{
			if (lowJobs[weekNumber] >= highJobs[weekNumber])
			{
				choicesMade[weekNumber] = 'L';
				return SelectBestScheduleB (weekNumber - 1, 'L', currentSum + lowJobs[weekNumber]); //The low stress job has higher revenue and is always part of the optimal solution

			} else if (highJobs[weekNumber] > lowJobs[weekNumber])
			{

				int lowForkSum = SelectBestScheduleB (weekNumber - 1, 'L', currentSum + lowJobs[weekNumber]);
				int highForkSum = SelectBestScheduleB (weekNumber - 1, 'H', currentSum + highJobs[weekNumber]);

				if (lowForkSum >= highForkSum)
				{
					choicesMade[weekNumber] = 'L';
					return lowForkSum;

				} else
				{
					choicesMade[weekNumber] = 'H';
					return highForkSum;

				}

			}

		}

	}

}