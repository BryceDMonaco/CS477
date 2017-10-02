/*
	Bryce Monaco
	CS 477
	Homework 3

	Compile with: g++ HW3.cpp -o HW3 -std=c++11

	This file implements and tests a Bubble Sort algorithm which does a left-to-right
	pass like normal and then also does a right-to-left pass in the same loop.
*/

#include <iostream>
#include <string>

using namespace std;

//Note: All functions are overloaded with an int and a char version
void SpecialBubbleSort (int* sentData, int sentLength);
void SpecialBubbleSort (char* sentData, int sentLength);

void Swap (int* firstVal, int* secondVal);
void Swap (char* firstVal, char* secondVal);

void PrintArray (int* sentData, int sentLength);
void PrintArray (char* sentData, int sentLength);


int main ()
{
	int values [] = {6, 5, 2, 8, 3, 1}; //Using the example values
	//int values[] = {8, 6, 5, 3, 2, 1}; //Worst case testing
	int valuesLength = 6;
	int* valuesPtr = values;

	char word [] = {'E', 'A', 'S', 'Y', 'Q', 'U', 'E', 'S', 'T', 'I', 'O', 'N'};
	int wordLength = 12;
	char* wordPtr = word;

	SpecialBubbleSort (word, wordLength);

	cout << endl << endl; //Make some space

	SpecialBubbleSort (values, valuesLength);


	return 0;

}

/*
	Note '|' shows scope of unsorted values

	Start:	   |6 5 2 8 3 1|			LB: -1	UB: 6
				6 i5 2 8 3 1  6- 1 = 5
				5 6 2i 8 3 1  6- 2 = 4
				5 2 6 8i 3 1  6- 3 = 3
				5 2 6 8 3i 1  6- 4 = 2
				5 2 6 3 8 1i  6- 5 = 1

	LtR:	   |5 2 6 3 1|8 (Loop 1) 	LB: -1 	UB: 5
				5 2 6 i3 1	3- -1 = 4
				5 2 i6 1 3  2- -1 = 3
				5 i2 1 6 3  1- -1 = 2
				i5 1 2 6 3  0- -1 = 1
				1 5 2 6 3 

	RtL:		1|5 2 6 3|8				LB: 0	UB: 5

	LtR:		1|2 5 3|6 8 (Loop 2)	LB: 0	UB: 4
	RtL:		1 2|3 5|6 8				LB: 1	UB: 4

	LtR:		1 2|3|5 6 8 (Loop 3)	LB: 1	UB: 3
	RtL:		1 2 3 5 6 8				LB: 2	UB: 3

	Start:	   |6 5 2 8 3 1 4|			LB: -1 	UB: 7

	LtR:	   |5 2 6 3 1 4|8			LB: -1 	UB: 6
	RtL:		1|5 2 6 3 4|8			LB: 0	UB: 6

	LtR:		1|2 5 3 4|6 8			LB: 0	UB: 5
	RtL:		1 2|3 5 4|6 8			LB: 1	UB: 5

	LtR:		1 2|3 4|5 6 8			LB: 1	UB: 4
	RtL:		1 2 3|4|5 6 8			LB: 2	UB: 4

*/

//Int Version
void SpecialBubbleSort (int* sentData, int sentLength)
{
	cout << "Starting Bubble Sort, Array Before Start: \t";
	PrintArray (sentData, sentLength);
	cout << endl;

	bool sorted = false;

	int lowerBound = -1; //-1 so that the 0th value is the first looked at
	int upperBound = sentLength; //This lets it go all the way to the last value

	int comparisons = 0;

	for (int pass = 0; (upperBound - lowerBound) > 2; pass++)
	{
		int* focusedValue = sentData + (lowerBound + 1); //start LtR on the left-most unsorted value

		//Do LtR Pass
		for (int i = (lowerBound + 2); (upperBound - i) >= 1; i++)
		{
			int* rightValue = focusedValue + 1; //The value to the right of the focused value

			if (*focusedValue > *rightValue)
			{
				Swap (focusedValue, rightValue);

			}

			comparisons++;

			focusedValue++;

		}

		upperBound--;

		cout << "Array After Left to Right Pass: \t\t";
		PrintArray (sentData, sentLength);
		cout << endl;

		/*
			====================================================================================
						Break just to help make the two passes easier to read/find
			====================================================================================
		*/

		focusedValue = sentData + (upperBound - 1); //start RtL on the right-most unsorted value

		//Do RtL Pass
		for (int i = (upperBound - 2); (i - lowerBound) >= 1; i++)
		{
			int* leftValue = focusedValue - 1; //The value to the left of the focused value

			if (*focusedValue < *leftValue)
			{
				Swap (focusedValue, leftValue);

			}

			comparisons++;

			if (leftValue == sentData) //To prevent out of bounds
			{
				break;

			} else
			{
				focusedValue--;

			}

		}

		lowerBound++;

		cout << "Array After Right to Left Pass: \t\t";
		PrintArray (sentData, sentLength);
		cout << endl;

		//cout << "UB: " << upperBound << "LB: " << lowerBound << endl;

	}

	cout << endl << "Final Form of the Array: \t\t\t";
	PrintArray (sentData, sentLength);
	cout << endl;

	cout << comparisons << " Comparisons Made" << endl;


}

void SpecialBubbleSort (char* sentData, int sentLength)
{
	cout << "Starting Bubble Sort, Array Before Start: \t";
	PrintArray (sentData, sentLength);
	cout << endl;

	bool sorted = false;

	int lowerBound = -1; //-1 so that the 0th value is the first looked at
	int upperBound = sentLength; //This lets it go all the way to the last value

	int comparisons = 0;

	for (int pass = 0; (upperBound - lowerBound) > 2; pass++)
	{
		bool isChange = false; 	//used to see if through a pass the array is changed at all because
								//the array might be sorted even though the bounds have not met

		char* focusedValue = sentData + (lowerBound + 1); //start LtR on the left-most unsorted value

		//Do LtR Pass
		for (int i = (lowerBound + 2); (upperBound - i) >= 1; i++)
		{
			char* rightValue = focusedValue + 1; //The value to the right of the focused value

			if (*focusedValue > *rightValue)
			{
				Swap (focusedValue, rightValue);

				isChange = true;

			}

			comparisons++;

			focusedValue++;

		}

		upperBound--;

		cout << "Array After Left to Right Pass: \t\t";
		PrintArray (sentData, sentLength);
		cout << endl;

		/*
			====================================================================================
						Break just to help make the two passes easier to read/find
			====================================================================================
		*/

		focusedValue = sentData + (upperBound - 1); //start RtL on the right-most unsorted value

		//Do RtL Pass
		for (int i = (upperBound - 2); (i - lowerBound) >= 1; i++)
		{
			char* leftValue = focusedValue - 1; //The value to the left of the focused value

			if (*focusedValue < *leftValue)
			{
				Swap (focusedValue, leftValue);

				isChange = true;

			}

			comparisons++;

			if (leftValue == sentData) //To prevent out of bounds
			{
				break;

			} else
			{
				focusedValue--;

			}

		}

		lowerBound++;

		cout << "Array After Right to Left Pass: \t\t";
		PrintArray (sentData, sentLength);
		cout << endl;

		/* Some debug outputs:
		cout << "UB: " << upperBound << "LB: " << lowerBound << endl;
		if (!isChange)
		{
			cout << "Note: At this point the array is already sorted, but the bounds have not met." << endl;

		}
		*/

	}

	cout << endl << "Final Form of the Array: \t\t\t";
	PrintArray (sentData, sentLength);
	cout << endl;

	cout << comparisons << " Comparisons Made" << endl;


}

void Swap (int* firstVal, int* secondVal)
{
	int temp = *secondVal;

	*secondVal = *firstVal;
	*firstVal = temp;

	return;

}

void Swap (char* firstVal, char* secondVal)
{
	char temp = *secondVal;

	*secondVal = *firstVal;
	*firstVal = temp;

	return;

}

void PrintArray (int* sentData, int sentLength)
{
	cout << "[";

	for (int i = 0; i < sentLength; i++)
	{
		if ((i + 1) == sentLength) //At last value
		{
			cout << *(sentData + i);

		} else
		{
			cout << *(sentData + i) << ", ";

		}

	}

	cout << "]";

	return;

}

void PrintArray (char* sentData, int sentLength)
{
	cout << "[";

	for (int i = 0; i < sentLength; i++)
	{
		if ((i + 1) == sentLength) //At last value
		{
			cout << *(sentData + i);

		} else
		{
			cout << *(sentData + i) << ", ";

		}

	}

	cout << "]";

	return;

}