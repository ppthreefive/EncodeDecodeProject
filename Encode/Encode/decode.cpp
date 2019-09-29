#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> original;
vector<int> index;

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
	for (int i = 0; i < data.size(); i++)
	{
		if (data.at(i) != "")
		{
			if (data.at(i).find(" ") != string::npos)
			{
				linesVector.push_back(data.at(i));
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
vector<int> generateNext(string &line, vector<int> &next) 
{
	vector<char> characters;
	string sorted;
	string last = line;

	for (int i = 0; i < line.length(); i++)
	{
		characters.push_back(line.at(i));
	}

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

	for (int k = 0; k < characters.size(); k++)
	{
		sorted.push_back(characters.at(k));
	}

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
	string result;
	
	int x = next.at(index);

	for (int i = 0; i < line.length(); i++)
	{
		result.push_back(line.at(x));
		x = next.at(x);
	}

	return result;
}

int main(int argc, char* argv[])
{
	string input;
	vector<string> lines;

	while (getline(cin, input)) 
	{
		original.push_back(input);
	}

	index = indexer(original, index);
	lines = encodedSeparator(original, lines);

	for (int i = 0; i < lines.size(); i++)
	{
		vector<int> next;

		lines.at(i) = declusterize(lines.at(i));
	
		next = generateNext(lines.at(i), next);

		//cout << lines.at(i);
	
		cout << recoverString(index.at(i), lines.at(i), next) << endl;
	}

	return 0;
}