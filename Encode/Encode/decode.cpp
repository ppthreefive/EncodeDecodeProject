/*	Name: Phillip Pham
	Course: CSE310, Section: 84794
	Instructor: Dr. Violet R. Syrotiuk
	Program Title: decode
		Description: This program's purpose is to take the encoded text file that we get from out encode program, and decode it back to its original text.
			This is done by grabbing the original index number, unclustering the last column, sorting it to get the first column, generating the next column,
			and then finally recovering the original text (encoded line by encoded line) using the pseudocode algorithm given to us in the project PDF.
	The test cases used are the encoded texts generated by the encode program, which will be required to be used before using decode.
		The encoded texts are encoded versions of the text cases provided in the project PDF and on Canvas.
	These articles have been referenced in helping make this program:
		http://www.cplusplus.com/reference/string/string/
		http://www.cplusplus.com/reference/vector/vector/
		https://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> original;
vector<int> index;

/* This function is just there to help convert a vector<char> to a string type. */
string convertCharVectorToString(vector<char> &characters)
{
	string text;

	for (int k = 0; k < characters.size(); k++)
	{
		text.push_back(characters.at(k));
	}

	return text;
}

/* This function is just there to help convert a string to a vector<char> type. */
vector<char> convertToCharVector(string &line)
{
	vector<char> characters;

	for (int i = 0; i < line.length(); i++)
	{
		characters.push_back(line.at(i));
	}

	return characters;
}

/* This is the same insertionSort function from the encoding part of the project, only modified to work with vector<char> instead of vector<string>.
	This is to help find the first column, which should be sorted.
*/
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

/* This is the same merge function from the encoding part of the project, only modified to work with vector<char> instead of vector<string>.
	This is to help find the first column, which should be sorted.
*/
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

/* This is the same merge function from the encoding part of the project, only modified to work with vector<char> instead of vector<string>.
	This is to help find the first column, which should be sorted.
*/
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
				//indexVector.push_back(stoi(lines.at(i)));
				indexVector.push_back(atoi(lines.at(i).c_str()));
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
		/* I discovered this neat trick to figure out if a string is an int from this link
			https://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int

			This helps determine if the line being read is in fact just an index number, or if it is part of a larger encoded string,
			therefore, any non numerical character that is read will cause the has_only_digits flag to be false.
			find_first_not_of() being the function that does the comparing.
		*/
		bool has_only_digits = (data.at(i).find_first_not_of("0123456789") == string::npos);

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
			if (k < index.size() - 1)
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

/* This function declusterizes the encoded line and recovers our last column string.
	The implementation looks kind of messy, but it was necessary to do it this way to parse the line in order to remove the spaces,
	and then uncluster the entire string. There are many loops in this implementation sadly.
*/
string declusterize(string &line)
{
	vector<char> chopped;
	vector<char> unspaced;
	vector<char> unclustered;

	// Copies the string to a vector<char> type
	for (int i = 0; i < line.length(); i++)
	{
		chopped.push_back(line.at(i));
	}

	// Turns the chopped vector into an unspaced vector (gets rid of the extra unneeded spaces, not the spaces that are a part of the decoded text)
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

	/* This big loop finally unclusters the unspaced vector, notice that there are multiple iterators here to compare different elements
		of the same string. It is complicated because we also need to ensure that the characters to be unclustered are not part of the cluster number.
		Sounds kind of confusing, but basically if we have: 171a
		We need to make sure it gets turned into: 7a, and not into 171 a's, and other crazy results.
	*/

	for (int i = 0; i < unspaced.size(); i = i + 2)
	{
		if (unspaced.at(i) != '1')
		{
			int j = i + 1;

			if (unspaced.at(i) == '2' && isdigit(unspaced.at(j)) || unspaced.at(i) == '3' && isdigit(unspaced.at(j))
				|| unspaced.at(i) == '4' && isdigit(unspaced.at(j)) || unspaced.at(i) == '5' && isdigit(unspaced.at(j))
				|| unspaced.at(i) == '6' && isdigit(unspaced.at(j)) || unspaced.at(i) == '7' && isdigit(unspaced.at(j))
				|| unspaced.at(i) == '8' && isdigit(unspaced.at(j)) || unspaced.at(i) == '9' && isdigit(unspaced.at(j)))
			{
				if ((i + 2) < unspaced.size())
				{
					if (!isdigit(unspaced.at(i + 2)))
					{
						int n = i + 2;
							
						string nums;

						nums += unspaced.at(i);
						nums += unspaced.at(j);

						//int t = stoi(nums);

						int t = atoi(nums.c_str());

						for (int k = 0; k < t; k++)
						{
							unclustered.push_back(unspaced.at(n));
						}

						i = i + 1;
					}

				}
			}
			else if (isdigit(unspaced.at(j)))
			{
				for (int k = 0; k < ((int)unspaced.at(i) - 48); k++)
				{
					unclustered.push_back(unspaced.at(j));
				}
			}
			else
			{
				string nums;

				nums += unspaced.at(i);

				if(isdigit(unspaced.at(j)))
				{
					nums += unspaced.at(j);
				}

				//int t = stoi(nums);

				int t = atoi(nums.c_str());

				for (int k = 0; k < t; k++)
				{
					unclustered.push_back(unspaced.at(j));
				}

				//i = i + 1;
			}
		}
		else if (unspaced.at(i) == '1' && (i + 2) > unspaced.size() - 1)
		{
			unclustered.push_back(unspaced.at(i + 1));
		}
		else if (unspaced.at(i) == '1' && isdigit(unspaced.at(i + 1)) && !isdigit(unspaced.at(i + 2)))
		{
			if ((i + 2) < unspaced.size())
			{
				if (!isdigit(unspaced.at(i + 2)))
				{
					int n = i + 1;

					string nums;

					nums += unspaced.at(i);
					nums += unspaced.at(n);

					//int t = stoi(nums);

					int t = atoi(nums.c_str());

					for (int k = 0; k < t; k++)
					{
						unclustered.push_back(unspaced.at(n + 1));
					}

					i = i + 1;
				}

			}
		}
		else
		{
			unclustered.push_back(unspaced.at(i + 1));
		}
	}

	// We clear the line here because we want to change it to the new unclustered string, after we convert the vector<char> back to a string.
	line.clear();

	for (int i = 0; i < unclustered.size(); i++)
	{
		line.push_back(unclustered.at(i));
	}

	return line;
}

/* This function generates the Next column and also sorts the last column to generate the first column.
	This was created using psuedocode provided in the PDF document for the project.
*/
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

/* This function finally decodes the encoded string once provided the index number, encoded string, and the next column.
	This was created using psuedocode provided in the PDF document for the project.
*/
string recoverString(int &index, string &line, vector<int> &next)
{
	string result = "";

	if (line.size() > 0)
	{
		if(index < line.length())
		{
			vector<int>::size_type x = next.at(index);

			for (vector<int>::size_type i = 0; i < line.length(); i++)
			{
				result.push_back(line.at(x));
				x = next.at(x);
			}
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

				//output += recoverString(index.at(i), lines.at(i), next) + "\n";

				cout << recoverString(index.at(i), lines.at(i), next) << endl;
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

				//output += recoverString(index.at(i), lines.at(i), next) + "\n";

				cout << recoverString(index.at(i), lines.at(i), next) << endl;
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
	//cout << output;

	return 0;
}