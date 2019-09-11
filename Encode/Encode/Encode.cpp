#include <iostream>
#include <string>
#include <vector>
using namespace std;

char input[] = "";

/*This function is designed to take the last character in each sorted line, and append it to a new string. 
	This new string will then be compressed into character clusters. 
For example:

If original string before it was shifted and sorted was: 

	Mississippi

Then the new string with all the last characters of the sorted strings will be: 
	
	ipssMpissii

When we clusterize, it will compress to this:

	0
	1i1p2s1M1p1i2s2i

Where the integers in the string represent how many of that character there is in that spot, aka clusters of those characters.

The 0 that we see in that example keeps track of what index in the sorted strings vector that the original string is seen.
*/
void clusterize(vector<string> &sortedLines, string original) 
{
	string lastColumn = "";
	string clusterized;
	int originalIndex = 0;

	// This will give us a string for the last column in the sorted vector
	for  (int i = 0; i < sortedLines.size(); i++)
	{
		lastColumn.push_back(sortedLines.at(i).back());
	}

	// This will actually check for clustered characters in the lastColumn string
	for (int i = 0; i < lastColumn.length(); i++)
	{
		int clusterCount = 1;
		
		for (int j = i + 1; j < lastColumn.length(); j++)
		{
			if (lastColumn.at(i) == lastColumn.at(j))
			{
				clusterCount++;
				i++;
			}
			else 
			{
				break;
			}
		}

		clusterized += to_string(clusterCount) + lastColumn.at(i);
	}

	// This checks for which index the original string is stored in our sorted vector
	for (int p = 0; p < sortedLines.size(); p++)
	{
		if (sortedLines.at(p) == original) 
		{
			originalIndex = p;
			break;
		}
	}

	clusterized = to_string(originalIndex) + "\n" + clusterized;

	cout << endl << clusterized << endl;
}

/* This function gets passed in the reference to the vector of shifted strings that we create with cyclicShifter function,
	and then it sorts the strings within the vector lexicographically. 

We pass in &shiftedLines, so that it can sort the vector that has already been made, instead of sorting a copy of the vector.*/
vector<string> insertionSort(vector<string> &shiftedLines) 
{
	string temp;
	int i, j = 0;
	int lowerBound = 0;
	int upperBound = shiftedLines.size() - 1;

	for (i = lowerBound; i <= upperBound; i++)
	{
		temp = shiftedLines.at(i);

		for (j = i - 1; j >= lowerBound; j--)
		{
			if (shiftedLines.at(j) <= temp) 
			{
				break;
			}

			shiftedLines.at(j + 1) = shiftedLines.at(j);
		}

		shiftedLines.at(j + 1) = temp;
	}

	return shiftedLines;
}

/*This function was created to cyclically shift the string to the left by 1 character, by n number of times, where n = length of string. */
vector<string> cyclicShifter(char line[], int length) 
{
	vector<string> shiftedLines;

	if (length <= 1)
	{
		shiftedLines.emplace_back(line);
		
		return shiftedLines;
	}
	else
	{
		shiftedLines.emplace_back(line);

		for (int i = 0; i < length - 1; i++)
		{
			char first = line[0];

			for (int j = 0; j < length - 1; j++)
			{
				line[j] = line[j + 1];
			}

			line[length - 1] = first;

			shiftedLines.emplace_back(line);
		}
	}

	return shiftedLines;
}

int main()
{
	vector<string> shiftedLines;
	vector<string> sortedLines;
	string original;
	
	cout << "Enter string to be sorted: ";
	cin >> input;

	original = input;
	
	int length = strlen(input);
	shiftedLines = cyclicShifter(input, length);

	cout << shiftedLines.size() << endl;

	for (int i = 0; i < shiftedLines.size(); i++)
	{
		string toPrint = "";

		toPrint = shiftedLines.at(i);

		cout << toPrint << endl;
	}

	cout << endl;

	sortedLines = insertionSort(shiftedLines);

	for (int i = 0; i < sortedLines.size(); i++)
	{
		string toPrint = "";

		toPrint = sortedLines.at(i);

		cout << toPrint << endl;
	}

	cout << endl;

	clusterize(sortedLines, original);

	return 0;
}