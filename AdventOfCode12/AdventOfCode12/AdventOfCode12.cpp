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

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode12\\input.txt";

	ifstream fin(filename);
	string initialConditions;
	getline(fin, initialConditions);
	initialConditions = initialConditions.substr(15);
	string plants = initialConditions;

	map<string, char> rules;

	string ruleLine;
	getline(fin, ruleLine);	//get the empty line

	while (getline(fin, ruleLine))
	{
		string conditions = ruleLine.substr(0, 5);

		rules.insert(make_pair(conditions, ruleLine.back()));
	}

	long long zeroIndex = 0;

	cout << "0:\t?\t" << zeroIndex << "\t" << plants << endl;
	long long numGens = 1000;
	for (long long gen = 0; gen < numGens; gen++)
	{
		zeroIndex++;
//		if ((gen * 100) % numGens == 0)
//			cout << (gen * 100) / numGens << "%\r";
		int firstPlant = plants.find_first_of('#');
		zeroIndex -= firstPlant;
		int lastPlant = plants.find_last_of('#');

		plants = "..." + plants.substr(firstPlant, lastPlant - firstPlant + 2) + "...";
		
		string nextGen;
		for (int i = 0; i < plants.size() - 4; i++)
		{
			auto rule = rules.find(plants.substr(i, 5));
			if (rule == rules.end())
			{
				cout << "Something went wrong" << endl;
				return -1;
			}
			nextGen.push_back(rule->second);
		}

		plants = nextGen;

		long long count = 0;
		for (long long i = 0; i < plants.size(); i++)
			if (plants[i] == '#')
				count += i - zeroIndex;
		cout << gen + 1 << ":\t" << count << "\t" << zeroIndex << "\t" << plants << endl;
	}

	string steadyState = "..##.#....##.#....##.#....##.#....##.#....##.#.....##.#........##.#....##.#.....###.#....###.#....###.#....###.#....##.#....##.#....##.#....##.#....###.#....##.#....##.#.";
	numGens = 50000000000;
	zeroIndex = numGens * -1 + 72;

	long long count = 0;
	for (long long i = 0; i < steadyState.size(); i++)
		if (steadyState[i] == '#')
			count += i - zeroIndex;

	cout << count << endl;
}
