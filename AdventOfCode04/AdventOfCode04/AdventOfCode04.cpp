// AdventOfCode04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

#include "date/date.h"

using namespace std;

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode04\\input.txt";

	map<chrono::time_point<chrono::system_clock, chrono::minutes>, string> orderedActions;
	map<int, pair<vector<int>, int>> asleepTimes;

	ifstream fin(filename);
	string line;
	while (getline(fin, line))
	{
		stringstream dateStrm(line.substr(1, 16));
		string action = line.substr(19);

		chrono::time_point<chrono::system_clock, chrono::minutes> tp;

		dateStrm >> date::parse("%F %R", tp);
		orderedActions.insert(make_pair(tp, action));
	}

	int currentGuard;
	int sleepMinute;

	for (auto timedAction : orderedActions)
	{
		string str = timedAction.second;
		if (str.compare(0, 5, "Guard") == 0)
		{
			stringstream sstrm(str.substr(7));
			sstrm >> currentGuard;
			auto guardTimes = asleepTimes.find(currentGuard);
			if (guardTimes == asleepTimes.end())
			{
				vector<int> sleepy(60, 0);
				asleepTimes.insert(make_pair(currentGuard, make_pair(sleepy, 0)));
			}
		}
		else if (str.compare(0, 5, "falls") == 0)
		{
			auto dp = date::floor<date::days>(timedAction.first);
			auto time = date::make_time(timedAction.first - dp);
			sleepMinute = time.minutes().count();
		}
		else
		{
			auto dp = date::floor<date::days>(timedAction.first);
			auto time = date::make_time(timedAction.first - dp);
			int awakeMinute = time.minutes().count();

			auto guardTimes = asleepTimes.find(currentGuard);
			if (guardTimes == asleepTimes.end())
			{
				cout << "Something went wrong" << endl;
				return -1;
			}

			for (int i = sleepMinute; i < awakeMinute; i++)
			{
				(guardTimes->second.first[i])++;
				(guardTimes->second.second)++;
			}
		}
	}

	int longestSleepingGuard = 0;
	int timeAsleep = 0;
	int biggestMinute = -1;
	int mostestMinute = -1;

	for (auto guardTimes : asleepTimes)
	{
		for (int m = 0; m < guardTimes.second.first.size(); m++)
		{
			if (guardTimes.second.first[m] > biggestMinute)
			{
				biggestMinute = guardTimes.second.first[m];
				mostestMinute = m;
				longestSleepingGuard = guardTimes.first;
			}
		}
	}

/*	auto sleeper = asleepTimes.find(longestSleepingGuard);
	for (int m = 0; m < sleeper->second.first.size(); m++)
	{
		if (sleeper->second.first[m] > biggestMinute)
		{
			biggestMinute = sleeper->second.first[m];
			mostestMinute = m;
		}
	}*/

	cout << longestSleepingGuard << " * " << mostestMinute << " = " << longestSleepingGuard * mostestMinute << endl;
}

