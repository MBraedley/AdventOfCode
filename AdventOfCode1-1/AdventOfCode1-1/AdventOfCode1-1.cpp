// AdventOfCode1-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode1-1\\input1-1.txt";
	fstream fin(filename);

	int frequencey = 0;
	set<int> pastFrequencies;
	pastFrequencies.insert(frequencey);
	int shift;
	while (true)
	{
		while (fin >> shift)
		{
			frequencey += shift;
			if (pastFrequencies.find(frequencey) != pastFrequencies.end())
			{
				cout << frequencey;
				return 0;
			}
			pastFrequencies.insert(frequencey);
		}
		cout << frequencey << endl;
		fin.close();
		fin.open(filename);
	}

}
