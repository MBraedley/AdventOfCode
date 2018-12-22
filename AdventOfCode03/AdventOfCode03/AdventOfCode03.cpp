// AdventOfCode03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


int getInt(string str)
{
	stringstream sstrm(str);
	int value;
	sstrm >> value;
	return value;
}

int main()
{
	map<string, set<int>> blanket;
	set<int> validClaims;

	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode03\\input.txt";

	ifstream fin(filename);
	string claim;
	while (getline(fin, claim))
	{
		int claimID = getInt(claim.substr(1, claim.find_first_of('@')));
		claim = claim.substr(claim.find_first_of('@') + 1);
		int x = getInt(claim.substr(0, claim.find_first_of(',')));
		claim = claim.substr(claim.find_first_of(',') + 1);
		int y = getInt(claim.substr(0, claim.find_first_of(':')));
		claim = claim.substr(claim.find_first_of(':') + 1);
		int width = getInt(claim.substr(0, claim.find_first_of('x')));
		claim = claim.substr(claim.find_first_of('x') + 1);
		int height = getInt(claim);

		validClaims.insert(claimID);

		for (int i = x; i < x + width; i++)
		{
			for (int j = y; j < y + height; j++)
			{
				stringstream coords;
				coords << i << "," << j;
				auto it = blanket.find(coords.str());
				if (it != blanket.end())
				{
					it->second.insert(claimID);
					for (int claimIt : it->second)
						validClaims.erase(claimIt);
				}
				else
				{
					set<int> square;
					square.insert(claimID);
					blanket.insert(make_pair(coords.str(), square));
				}
			}
		}
	}

	int multiclaim = 0;
	for (auto it : blanket)
	{
		if (it.second.size() > 1)
			multiclaim++;
	}

	for (int it : validClaims)
		cout << it << endl;
}
