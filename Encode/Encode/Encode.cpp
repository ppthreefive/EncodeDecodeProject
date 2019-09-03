#include <iostream>
#include <string>
using namespace std;

string insertionSort(string line) 
{
	char temp;
	int i, j = 0;
	int lowerBound = 0;
	int upperBound = line.length() - 1;

	for (i = lowerBound; i <= upperBound; i++)
	{
		temp = line.at(i);

		for (j = i - 1; j >= lowerBound; j--)
		{
			if (line.at(j) <= temp) 
			{
				break;
			}

			line.at(j + 1) = line.at(j);
		}

		line.at(j + 1) = temp;
	}

	return line;
}

int main()
{
	string input;

	cout << "Enter string to be sorted: ";
	cin >> input;
	cout << insertionSort(input);

	return 0;
}