#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> original;
vector<int> index;

string convertCharVectorToString(vector<char> &characters) 
{
	string text;

	for (int k = 0; k < characters.size(); k++)
	{
		text.push_back(characters.at(k));
	}

	return text;
}

vector<char> convertToCharVector(string &line) 
{
	vector<char> characters;

	for (int i = 0; i < line.length(); i++)
	{
		characters.push_back(line.at(i));
	}

	return characters;
}

void insertionSort(vector<char> &characters) 
{
	char temp;
	int i, j = 0;
	int lowerBound = 0;
	int upperBound = characters.size() - 1;

	for (i = lowerBound; i <= upperBound; i++)
	{
		temp = characters.at(i);

		for (j = i - 1; j >= lowerBound; j--)
		{
			if (characters.at(j) <= temp)
			{
				break;
			}

			characters.at(j + 1) = characters.at(j);
		}

		characters.at(j + 1) = temp;
	}
}

void merge(vector<char> &left, vector<char> &right, vector<char> &data)
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

void mergeSort(vector<char> &characters)
{
	// If size is less than or equal to 1, vector is already sorted.
	if (characters.size() <= 1)
	{
		return;
	}

	// Find the midpoint of the vector
	vector<int>::size_type mid = characters.size() / 2;

	// Initialize 2 vectors that will hold the left and right halves of the shifted vector
	vector<char> left;
	vector<char> right;

	// Populate the left and right half vectors
	for (vector<int>::size_type j = 0; j < mid; j++)
	{
		left.push_back(characters[j]);
	}
	for (vector<int>::size_type j = 0; j < (characters.size()) - mid; j++)
	{
		right.push_back(characters[mid + j]);
	}

	// Split the left and ride sides until each vector is size of 1 element, and then go to merge function to sort
	mergeSort(left);
	mergeSort(right);
	merge(left, right, characters);
}

/*	This function parses the vector that has all of the lines and puts the indexes of each encoded line into a vector. */
vector<int> indexer(vector<string> &lines, vector<int> &indexVector)
{
	for (int i = 0; i < lines.size(); i++)
	{
		if (lines.at(i) != "")
		{
			if (lines.at(i).find(" ") == string::npos)
			{
				indexVector.push_back(stoi(lines.at(i)));
			}
		}
	}

	return indexVector;
}

/* This function separates the encoded lines from their indexes. */
vector<string> encodedSeparator(vector<string> &data, vector<string> &linesVector)
{
	int k = 0;

	for (int i = 0; i < data.size(); i++)
	{
			bool has_only_digits = (data.at(i).find_first_not_of("0123456789") == std::string::npos);

			if (data.at(i).find(to_string(index.at(k))) == string::npos)
			{
				linesVector.push_back(data.at(i));
			}
			else if (data.at(i).find(to_string(index.at(k))) != string::npos && data.at(i).length() != 0 && !has_only_digits)
			{
				linesVector.push_back(data.at(i));
			}
			else 
			{
				if(k < index.size() - 1)
				{
					k++;
				}
				else if (k == index.size() - 1) 
				{
					linesVector.push_back(data.at(i + 1));
					break;
				}
				else 
				{
					break;
				}
			}
	}

	return linesVector;
}

/* This function declusterizes the encoded line and recovers our last column string */
string declusterize(string &line)
{
	vector<char> chopped;
	vector<char> unspaced;
	vector<char> unclustered;

	for (int i = 0; i < line.length(); i++)
	{
		chopped.push_back(line.at(i));
	}

	for (int i = 0; i < chopped.size(); i++)
	{
		if (chopped.at(i) == ' ')
		{
			if (i == chopped.size() - 1)
			{
				unspaced.push_back(chopped.at(i));
				break;
			}
			if (chopped.at(i + 1) == ' ' && chopped.at(i - 1) == ' ')
			{
				unspaced.push_back(chopped.at(i));
			}
		}
		else
		{
			unspaced.push_back(chopped.at(i));
		}
	}

	for (int i = 0; i < unspaced.size(); i = i + 2)
	{
		if (unspaced.at(i) != '1')
		{
			int j = i + 1;

			for (int k = 0; k < ((int)unspaced.at(i) - 48); k++)
			{
				unclustered.push_back(unspaced.at(j));
			}
		}
		else
		{
			unclustered.push_back(unspaced.at(i + 1));
		}
	}

	line.clear();

	for (int i = 0; i < unclustered.size(); i++)
	{
		line.push_back(unclustered.at(i));
	}

	return line;
}

/* This function generates the Next column and also sorts the last column to generate the first column.
	This is using insertion sort */
vector<int> generateNext(vector<int> &next, string &sorted, string &line)
{
	string last = line;

	for (int p = 0; p < sorted.length(); p++)
	{
		for (int q = 0; q < last.length(); q++)
		{
			if (sorted.at(p) == last.at(q))
			{
				next.push_back(q);
				last.at(q) = NULL;
			}
		}
	}

	return next;
}

string recoverString(int &index, string &line, vector<int> &next)
{
	string result = "";

	if(line.size() > 0)
	{
		int x = next.at(index);

		for (int i = 0; i < line.length(); i++)
		{
			result.push_back(line.at(x));
			x = next.at(x);
		}
	}

	return result;
}

int main(int argc, char *argv[])
{
	string argument;
	string line;
	string output;
	vector<string> lines;

	for (int i = 1; i < argc; i++)
	{
		argument += argv[i];
		argument += "\n";
	}

	/* This will check that the amount of arguments is at least equal to 2, and checks if the second argument is equal to either of the keywords.
			If neither conditions are met, the program closes and a quick error message is displayed in console.

		It's also possible to use keyboard input if an input string is not specified.
			For example, the input: "decode.exe insertion" with no file redirects will allow the user to input their own strings.

			In order to end the input of strings, the user will need to type Ctrl+Z (Windows) or Ctrl+D (Unix) and then hit return.

			The program will then do work on those strings and then output the results to console instead of a file.
	*/
	if (argc == 2 && (argument.find("insertion") != string::npos || argument.find("merge") != string::npos))
	{
		while (getline(cin, line))
		{
			original.push_back(line);
		}
	}
	else
	{
		cout << "ERROR: Incorrect syntax for using this program. Please use keyword \"insertion\" or \"merge\"," << endl;
		cout << "\tand specify and input and output file using <*input.txt* and >*output.txt* respectively." << endl;
		cout << "An example would be: \"decode.exe insertion <input.txt >output.txt\" without quotations." << endl;

		return 0;
	}
	
	index = indexer(original, index);
	lines = encodedSeparator(original, lines);
	
	// This conditional statement just checks to see if there are any arguments passed besides just the program name
	if (argc > 1)
	{
		for (int i = 0; i < lines.size(); i++)
		{
			// This will check to see if the substring "insertion" or "merge" exists in argument, and is basically an operations selector.
			// NOTE: This is case sensitive, so "INSERTION" for example would cause the program to exit.
			if (argument.find("insertion") != string::npos)
			{
				vector<int> next;
				vector<char> converted;
				string sorted;

				lines.at(i) = declusterize(lines.at(i));

				converted = convertToCharVector(lines.at(i));

				insertionSort(converted);

				sorted = convertCharVectorToString(converted);

				next = generateNext(next, sorted, lines.at(i));

				output += recoverString(index.at(i), lines.at(i), next) + "\n";
			}
			else if (argument.find("merge") != string::npos)
			{
				vector<int> next;
				vector<char> converted;
				string sorted;

				lines.at(i) = declusterize(lines.at(i));

				converted = convertToCharVector(lines.at(i));

				mergeSort(converted);

				sorted = convertCharVectorToString(converted);

				next = generateNext(next, sorted, lines.at(i));

				output += recoverString(index.at(i), lines.at(i), next) + "\n";
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