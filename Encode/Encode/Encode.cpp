/*	Name: Phillip Pham
	Course: CSE310, Section: 84794
	Instructor: Dr. Violet R. Syrotiuk

	Program Title: encode
		Description: This is a program that will encode an input of strings, line by line, by cyclically shifting characters
			to the left once, for an N amount of times. N is equal to the amount of characters in the string. Those resulting N
			strings will then be sorted lexicographically using insertion or merge sort, depending on what the user selects.
			Once the strings are sorted, the last character in each sorted string, in order, is appended to a new string
			which represents the last column. The characters are then clusterized to form the encoded string. The original
			string is also kept track of, and appended to the final clusterized string.

	Test cases have been provided in the project PDF and on Canvas, and are located in the debug folder.

	These articles have been referenced in helping make this program:
		http://www.cplusplus.com/reference/string/string/
		http://www.cplusplus.com/reference/vector/vector/
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> originalText;

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
string clusterize(vector<string> &sortedLines, string original) 
{
	string lastColumn = "";
	string clusterized;
	int originalIndex = 0;
	int count = 0;

	if (sortedLines.at(count) != "") 
	{
		// This will give us a string for the last column in the sorted vector
		for (int i = 0; i < sortedLines.size(); i++)
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

			clusterized += to_string(clusterCount) + " " + lastColumn.at(i) + " ";
		}

		// Gets rid of that last space at the end of the encoded string
		clusterized = clusterized.substr(0, clusterized.length() - 1);

		// This checks for which index the original string is stored in our sorted vector
		for (int p = 0; p < sortedLines.size(); p++)
		{
			if (sortedLines.at(p) == original)
			{
				originalIndex = p;
				break;
			}
		}

		clusterized = to_string(originalIndex) + "\n" + clusterized + "\n";

		count++;
	}
	else 
	{
		clusterized = to_string(originalIndex) + "\n\n";
	}

	return clusterized;
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

/* Takes all the split subvectors of size 1 from the recursive function mergeSort() and does the merging/sorting here.

	By using pass by reference, the vector that was originally passed into function mergeSort() is actually being modified,
	with the only auxiliary vectors being the left and right vectors that are also passed in.
*/
void merge(vector<string> &left, vector<string> &right, vector<string> &data)
{
	// Create integer variables that represent the amount of elements in the left and right halves respectively
	vector<int>::size_type numLeft = left.size();
	vector<int>::size_type numRight = right.size();

	// Initialize the iterators
	vector<int>::size_type i = 0, j = 0, k = 0;

	// Loops to compare which element in the left or right vector is larger, and then swaps to the corresponding spot
	// in the original vector noted by the iterator i
	while (j < numLeft && k < numRight)
	{
		if (left[j] < right[k])
		{
			data[i] = left[j];
			j++;
		}
		else
		{
			data[i] = right[k];
			k++;
		}

		i++;
	}

	// These loops fill in the resulting vector with any remaining elements
	while (j < numLeft)
	{
		data[i] = left[j];
		j++;
		i++;
	}
	while (k < numRight)
	{
		data[i] = right[k];
		k++;
		i++;
	}
}

/* This is the divide and conquer sorting algorithm that splits a vector as many times as it needs until each subvector is a size of 1 element.
	It will recursively call itself to keep splitting the vectors, and once each vector is a size of 1, it finally reaches the merge() function call,
	Which takes those split vectors of size 1 and merges them all together in sorted order.

	We only need to pass in the shiftedLines vector which was created by the cyclicShifter() function.

	For some reason, I was getting issues using int type for my iterators, so I had to use vector<int>::size_type instead.
*/
void mergeSort(vector<string> &shiftedLines)
{
	// If size is less than or equal to 1, vector is already sorted.
	if (shiftedLines.size() <= 1)
	{
		return;
	}

	// Find the midpoint of the vector
	vector<int>::size_type mid = shiftedLines.size() / 2;

	// Initialize 2 vectors that will hold the left and right halves of the shifted vector
	vector<string> left;
	vector<string> right;

	// Populate the left and right half vectors
	for (vector<int>::size_type j = 0; j < mid; j++)
	{
		left.push_back(shiftedLines[j]);
	}
	for (vector<int>::size_type j = 0; j < (shiftedLines.size()) - mid; j++)
	{
		right.push_back(shiftedLines[mid + j]);
	}

	// Split the left and ride sides until each vector is size of 1 element, and then go to merge function to sort
	mergeSort(left);
	mergeSort(right);
	merge(left, right, shiftedLines);
}

/*This function was created to cyclically shift the string to the left by 1 character, by n number of times, where n = length of string. */
vector<string> cyclicShifter(string line, int length) 
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

int main(int argc, char* argv[])
{
	string argument;
	string line;
	string output;

	for (int i = 1; i < argc; i++)
	{
		argument += argv[i];
		argument += "\n";
	}

	/* This will check that the amount of arguments is at least equal to 2, and checks if the second argument is equal to either of the keywords.
			If neither conditions are met, the program closes and a quick error message is displayed in console.

		It's also possible to use keyboard input if an input string is not specified.
			For example, the input: "encode.exe insertion" with no file redirects will allow the user to input their own strings.

			In order to end the input of strings, the user will need to type Ctrl+Z (Windows) or Ctrl+D (Unix) and then hit return.

			The program will then do work on those strings and then output the results to console instead of a file.
	*/
	if (argc == 2 && (argument.find("insertion") != string::npos || argument.find("merge") != string::npos))
	{
		while (getline(cin, line))
		{
			originalText.push_back(line);
		}
	}
	else 
	{
		cout << "ERROR: Incorrect syntax for using this program. Please use keyword \"insertion\" or \"merge\"," << endl;
		cout << "\tand specify and input and output file using <*input.txt* and >*output.txt* respectively." << endl;
		cout << "An example would be: \"encode.exe insertion <input.txt >output.txt\" without quotations." << endl;

		return 0;
	}

	// This conditional statement just checks to see if there are any arguments passed besides just the program name
	if (argc > 1)
	{
		for (int i = 0; i < originalText.size(); i++)
		{
			vector<string> manipulatedStrings;
			int length = originalText.at(i).length();

			// This will check to see if the substring "insertion" or "merge" exists in argument, and is basically an operations selector.
			// NOTE: This is case sensitive, so "INSERTION" for example would cause the program to exit.
			if (argument.find("insertion") != string::npos)
			{
				manipulatedStrings = cyclicShifter(originalText.at(i), length);
				manipulatedStrings = insertionSort(manipulatedStrings);
				output += clusterize(manipulatedStrings, originalText.at(i));
			}
			else if (argument.find("merge") != string::npos)
			{
				manipulatedStrings = cyclicShifter(originalText.at(i), length);
				mergeSort(manipulatedStrings);
				output += clusterize(manipulatedStrings, originalText.at(i));
			}
			else
			{
				// The program will exit if insertion or merge not detected in input
				return 0;
			}
		}
	}

	// This will output to either a file specified at Command Line, or will just output into Command Line if no file specified.
	// I.E. "<encoded-output.txt"
	cout << output;

	return 0;
}