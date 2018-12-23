// AdventOfCode2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

bool oneCharOff(string a, string b, int& diffPos)
{
	if (a.size() != b.size())
		return false;

	int diffCount = 0;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != b[i])
		{
			diffCount++;
			diffPos = i;
		}

		if (diffCount >= 2)
			return false;
	}

	return diffCount == 1;
}

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode02\\input2.txt";
	//int twosCount = 0;
	//int threesCount = 0;

	set<string> candidates;

	ifstream fin(filename);
	string boxName;
	while (getline(fin, boxName))
	{
		multiset<char> s;
		for (char c : boxName)
		{
			s.insert(c);
		}
		bool hasDouble = false;
		bool hasTriple = false;

		for (auto it : s)
		{
			if (s.count(it) == 2)
				hasDouble = true;
			if (s.count(it) == 3)
				hasTriple = true;
		}

		//if (hasDouble)
		//	twosCount++;
		//if (hasTriple)
		//	threesCount++;

		if (hasDouble || hasTriple)
		{
			for (auto str : candidates)
			{
				int pos;
				if (oneCharOff(boxName, str, pos))
				{
					cout << boxName << endl << str << endl;
					cout << boxName.substr(0, pos) << " " << boxName.substr(pos + 1) << endl;
					return 0;
				}
			}
			candidates.insert(boxName);
		}
	}

//	cout << twosCount * threesCount;
}
