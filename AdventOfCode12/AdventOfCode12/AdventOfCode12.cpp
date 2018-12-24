// AdventOfCode12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <map>
#include <string>

using namespace std;

void printPlants(const deque<pair<long long, bool>>& plants, int generation, int padding = 0)
{
	cout << generation << ":\t";
	for (int i = 0; i < padding; i++)
		cout << " ";
	for (auto plant : plants)
		cout << (plant.second ? "#" : ".");

	cout << endl;
}

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode12\\input.txt";

	ifstream fin(filename);
	string initialConditions;
	getline(fin, initialConditions);
	initialConditions = initialConditions.substr(15);
	deque<pair<long long, bool>> plants;

	int potNumber = 0;
	for (char c : initialConditions)
		plants.push_back(make_pair(potNumber++, c == '#'));

	map<vector<bool>, bool> rules;

	string ruleLine;
	getline(fin, ruleLine);	//get the empty line

	while (getline(fin, ruleLine))
	{
		vector<bool> conditions(5);
		for (int i = 0; i < 5; i++)
			conditions[i] = ruleLine[i] == '#';

		bool result = ruleLine.back() == '#';
		rules.insert(make_pair(conditions, result));
	}

//	printPlants(plants, 0, 40);

	long long numGens = 50000000000;
	for (long long gen = 0; gen < numGens; gen++)
	{
		if ((gen * 100) % numGens == 0)
			cout << (gen * 100) / numGens << "%\r";
		// Push 4 new pots on each end of the deque, but 2 from each end won't be used in the next generation
		plants.push_front(make_pair(plants.front().first - 1, false));
		plants.push_front(make_pair(plants.front().first - 1, false));
		plants.push_front(make_pair(plants.front().first - 1, false));
		plants.push_front(make_pair(plants.front().first - 1, false));
		plants.push_back(make_pair(plants.back().first + 1, false));
		plants.push_back(make_pair(plants.back().first + 1, false));
		plants.push_back(make_pair(plants.back().first + 1, false));
		plants.push_back(make_pair(plants.back().first + 1, false));

		deque<pair<long long, bool>> nextGen;
		for (int i = 2; i < plants.size() - 2; i++)
		{
			vector<bool> lookingAt(5);
			lookingAt[0] = plants[i - 2].second;
			lookingAt[1] = plants[i - 1].second;
			lookingAt[2] = plants[i].second;
			lookingAt[3] = plants[i + 1].second;
			lookingAt[4] = plants[i + 2].second;
			auto rule = rules.find(lookingAt);
			if (rule == rules.end())
			{
				cout << "Something went wrong";
				return -1;
			}
			nextGen.push_back(make_pair(plants[i].first, rule->second));
		}

		plants = nextGen;
//		printPlants(plants, gen + 1, 38 - gen * 2);
	}

	long long count = 0;
	for (auto plant : plants)
		if (plant.second)
			count += plant.first;

	cout << count << endl;
}
