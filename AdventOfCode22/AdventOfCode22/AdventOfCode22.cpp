// AdventOfCode22.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <sstream>
#include <deque>
#include <queue>

using namespace std;

typedef pair<int, int> coords;

enum Tools : int
{
	Torch = 0,
	Climb,
	None
};

enum CaveType : int
{
	Rocky = 0,
	Wet,
	Narrow
};

int main()
{
	// Input:
	//int depth = 510;
	//coords target(10, 10);

	int depth = 10647;
	coords target(7,770);

	vector<int> layer(target.first + 100, 0);
	vector<vector<int>> caveErrosion(target.second + 100, layer);
	vector<vector<int>> caveTypes(target.second + 100, layer);

	int riskLevel = 0;

	for (int y = 0; y < caveErrosion.size(); y++)
	{
		for (int x = 0; x < caveErrosion[y].size(); x++)
		{
			int geoIndex;
			if ((x == 0 && y == 0) || (x == target.first && y == target.second))
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

			if (x <= target.first && y <= target.second)
				riskLevel += caveTypes[y][x];
		}
	}
	// Part 1:
	cout << riskLevel << endl;

	map<pair<coords, Tools>, int> dist;

	priority_queue<pair<int, pair<coords, Tools>>, vector<pair<int, pair<coords, Tools>>>, greater<pair<int, pair<coords, Tools>>>> dijk;

	dijk.push({ 0, {{0, 0}, Torch} });
	dist[{ {0, 0}, Torch}] = 0;

	while (!dijk.empty())
	{
		auto current = dijk.top();
		dijk.pop();

		int currentDist = current.first;
		int x = current.second.first.first;
		int y = current.second.first.second;
		Tools tool = current.second.second;

		if (currentDist > dist[current.second])
			continue;

		if (current.second == make_pair(target, Torch))
		{
			// We've reached our target
			cout << dist[current.second] << endl;
			return 0;
		}

		vector<coords> nextLoc = { {x - 1, y}, {x + 1, y} , {x, y - 1}, {x, y + 1} };
		for (coords next : nextLoc)
		{
			if (next.first < 0 || next.second < 0 || next.second >= caveTypes.size() || next.first >= caveTypes[next.second].size())
				continue;

			if (tool == Torch)
			{
				if ((CaveType)caveTypes[next.second][next.first] == Wet)
					continue;
			}
			else if (tool == Climb)
			{
				if ((CaveType)caveTypes[next.second][next.first] == Narrow)
					continue;
			}
			else //if (tool == None)
			{
				if ((CaveType)caveTypes[next.second][next.first] == Rocky)
					continue;
			}

			pair<coords, Tools> nextNode = { next, tool };

			if (dist.count(nextNode) == 0 || dist[nextNode] > dist[current.second] + 1)
			{
				dist[nextNode] = dist[current.second] + 1;
				dijk.push({ dist[current.second] + 1, nextNode });
			}
		}

		for (int i = Torch; i <= None; i++)
		{
			if ((Tools)i == tool)
				continue;

			if ((CaveType)caveTypes[y][x] == Rocky)
			{
				if ((Tools)i == None)
					continue;
			}
			else if ((CaveType)caveTypes[y][x] == Wet)
			{
				if ((Tools)i == Torch)
					continue;
			}
			else //if ((CaveType)caveTypes[y][x] == Narrow)
			{
				if ((Tools)i == Climb)
					continue;
			}
			pair<coords, Tools> nextNode = { {x, y}, (Tools)i };

			if (dist.count(nextNode) == 0 || dist[nextNode] > dist[current.second] + 7)
			{
				dist[nextNode] = dist[current.second] + 7;
				dijk.push({ dist[current.second] + 7, nextNode });
			}
		}
	}
}
