/*
	Bryce Monaco
	CS 477
	Homework 3 Extra Creddit

	Compile with: g++ HW3_ExtraCredit.cpp -o EC -std=c++11

	This file implements and tests a partitioning algorithm meant for data sets
	with multiple duplicate keys.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void DuplicatePartition (vector<char>& sentKeys);
void Swap (char& j, char& k);
void PrintVector (vector<char> sentVector);

int main ()
{	
	//The values given in the question
	char temp[] = {'A', 'B', 'R', 'A', 'C', 'A', 'C', 'A', 'B', 'R', 'A', 'B', 'C', 'D', 'C'};
	int tempSize = 15;
	vector<char> keys;
	keys.assign (temp, temp + tempSize);

	cout << "Before partitioning, the array is: ";
	PrintVector(keys);
	cout << endl;

	DuplicatePartition(keys);

	cout << endl << "After partitioning, the array is: ";
	PrintVector(keys);

	return 0;

}

void DuplicatePartition (vector<char>& sentKeys)
{
	int keysSize = sentKeys.size();

	char pivot = sentKeys[keysSize - 1]; //Set the right-most value to be the pivot

	int leftIndex = 0; //The first element
	int rightIndex = keysSize - 2; //The last element before the pivot

	int leftBounds = 0;
	int rightBounds = keysSize - 2;

	while (!(leftBounds >= rightBounds))
	{
		//Index of each respective value
		int leftValue;
		int rightValue;

		//Scan from the left to find a value greater than or equal to pivot
		for (int i = leftBounds; i < (rightBounds + 1); i++)
		{
			if (sentKeys[i] >= pivot)
			{
				leftValue = i;

				break;
			}
		}

		//Scan from the right to find a value less than or equal to pivot
		for (int i = rightBounds; i > (leftBounds - 1); i--)
		{
			if (sentKeys[i] <= pivot)
			{
				rightValue = i;

				break;
			}
		}

		cout << "Swapping '" << sentKeys[leftValue] << "' and '" << sentKeys[rightValue] << "'" << endl;

		//Swap the values, if either value equal pivot then, after swap, move them to
		//...the left or right end of their new partition
		Swap(sentKeys[leftValue], sentKeys[rightValue]);

		if (sentKeys[leftValue] == pivot) //If the value that was moved from the right equals pivot
		{
			cout << "The new left value is equal to the pivot, swapping with '" << sentKeys[leftIndex] << "'" << endl;

			Swap(sentKeys[leftValue], sentKeys[leftIndex]);

			leftIndex++;

		}

		if (sentKeys[rightValue] == pivot) //If the value that was moved from the left equals pivot
		{
			cout << "The new right value is equal to the pivot, swapping with '" << sentKeys[rightIndex] << "'" << endl;

			Swap(sentKeys[rightValue], sentKeys[rightIndex]);

			rightIndex--;

		}

		leftBounds++;
		rightBounds--;

		cout << "The array is now: ";
		PrintVector(sentKeys);
		cout << endl;

	}

	//Make sure the value at rightBounds is the first value in the greater partition
	while (sentKeys[rightBounds] < pivot)
	{
		rightBounds++;

	}


	//Move pivot to the middle of the two partitions
	Swap(sentKeys[keysSize - 1], sentKeys[rightBounds]);

	rightBounds++;
	leftBounds++;

	//Move the equal values on the right to the center
	while (rightIndex < keysSize)
	{
		if (sentKeys[rightIndex] == pivot)
		{
			Swap(sentKeys[rightBounds], sentKeys[rightIndex]);

			rightBounds++;

		}

		rightIndex++;

	}

	//Move the equal values on the left to the center
	while (leftIndex >= 0)
	{
		if (sentKeys[leftIndex] == pivot)
		{
			Swap(sentKeys[leftBounds], sentKeys[leftIndex]);

			leftBounds--;

		}

		leftIndex--;

	}

	return;

}

void Swap (char& j, char& k)
{
	char temp = j;
	j = k;
	k = temp;

	return;

}

void PrintVector (vector<char> sentVector)
{
	for (int i = 0; i < sentVector.size(); i++)
	{
		cout << sentVector[i];

	}

	cout << endl;

	return;

}