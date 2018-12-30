// AdventOfCode22.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <complex>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <sstream>
#include <deque>

using namespace std;

enum Tools
{
	None = 0,
	Climb,
	Torch
};

enum CaveType : int
{
	Rocky = 0,
	Wet,
	Narrow
};

set<Tools> rockyTools;
set<Tools> wetTools;
set<Tools> narrowTools;

map<CaveType, set<Tools>> availableToolMap;

vector<complex<int>> dirs;

string complex2str(complex<int> in)
{
	stringstream sstrm;
	sstrm << in;
	return sstrm.str();
}

struct SearchInfo
{
	Tools tool;
	int time;
	complex<int> pos;
};

void TraverseCave(const vector<vector<int>>& caveTypes, unordered_map<string, int>& posTimes, const complex<int>& currentPos, const Tools& currentTool, int currentTime, const complex<int>& targetPos, deque<SearchInfo>& next)
{
	if (currentPos.imag() < 0 || currentPos.real() < 0 || currentPos.imag() >= caveTypes.size() || currentPos.real() >= caveTypes[currentPos.imag()].size())
		return;
	string posStr = complex2str(currentPos);
	auto it = posTimes.find(posStr);
	if (it == posTimes.end())
	{
		posTimes.insert(make_pair(posStr, currentTime));
	}
	else
	{
		if (it->second < currentTime)	//We've been here before, but faster
			return;
		else
			it->second = currentTime;
	}

	if (currentPos == targetPos)
		return;

	int currentType = caveTypes[currentPos.imag()][currentPos.real()];
	set<Tools> currentValidTools = availableToolMap[(CaveType)currentType];

	currentTime++;
	for (complex<int> dir : dirs)
	{
		complex<int> nextPos = currentPos + dir;
		if (nextPos.real() >= 0 && nextPos.imag() >= 0 && nextPos.real() < caveTypes[0].size() && nextPos.imag() < caveTypes.size())
		{
			int nextType = caveTypes[nextPos.imag()][nextPos.real()];
			set<Tools> availableTools = availableToolMap[(CaveType)nextType];

			if (availableTools.find(currentTool) != availableTools.end())
			{
				TraverseCave(caveTypes, posTimes, nextPos, currentTool, currentTime, targetPos, next);
			}
			else if (posTimes.find(complex2str(nextPos)) == posTimes.end())
			{
				for (Tools tool : currentValidTools)
				{
					if (tool != currentTool)
					{
						SearchInfo nextSearch;
						nextSearch.pos = nextPos;
						nextSearch.time = currentTime + 7;
						nextSearch.tool = tool;
						next.push_back(nextSearch);
					}
				}
			}
		}
	}
}

int main()
{
	// Input:
	int depth = 510;
	complex<int> target(10, 10);

	vector<int> layer(target.real() + 10, 0);
	vector<vector<int>> caveErrosion(target.imag() + 10, layer);
	vector<vector<int>> caveTypes(target.imag() + 10, layer);

	int riskLevel = 0;

	for (int y = 0; y < caveErrosion.size(); y++)
	{
		for (int x = 0; x < caveErrosion[y].size(); x++)
		{
			int geoIndex;
			if ((x == 0 && y == 0) || (x == target.real() && y == target.imag()))
			{
				geoIndex = 0;
			}
			else if (y == 0)
			{
				geoIndex = x * 16807;
			}
			else if (x == 0)
			{
				geoIndex = y * 48271;
			}
			else
			{
				geoIndex = caveErrosion[y - 1][x] * caveErrosion[y][x - 1];
			}
			caveErrosion[y][x] = (geoIndex + depth) % 20183;	//this is errosion level, not region type
			caveTypes[y][x] = caveErrosion[y][x] % 3;

			if (x <= target.real() && y <= target.imag())
				riskLevel += caveTypes[y][x];
		}
	}
	// Part 1:
	cout << riskLevel << endl;

	rockyTools.insert(Climb);
	rockyTools.insert(Torch);
	wetTools.insert(None);
	wetTools.insert(Climb);
	narrowTools.insert(None);
	narrowTools.insert(Torch);

	availableToolMap.insert(make_pair(Rocky, rockyTools));
	availableToolMap.insert(make_pair(Wet, wetTools));
	availableToolMap.insert(make_pair(Narrow, narrowTools));

	dirs.push_back(1);
	dirs.push_back(-1);
	dirs.push_back(1i);
	dirs.push_back(-1i);

	unordered_map<string, int> posTimes;
	complex<int> pos(0, 0);
	stringstream sstrm;
	sstrm << pos;
	posTimes.insert(make_pair(complex2str(pos), 0));
	int currentTime = 0;
	Tools currentTool = Torch;

	deque<SearchInfo> nextPositions;
	SearchInfo first;
	first.pos = pos;
	first.time = 0;
	first.tool = Torch;
	nextPositions.push_back(first);

	while (!nextPositions.empty())
	{
		SearchInfo next = nextPositions.front();
		nextPositions.pop_front();
		TraverseCave(caveTypes, posTimes, next.pos, next.tool, next.time, target, nextPositions);
	}

//	TraverseCave(caveTypes, posTimes, pos, Torch, 0, target);

	cout << posTimes.find(complex2str(target))->second << endl;
}
