// AdventOfCode23.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>

using namespace std;

struct Pos3D
{
	int x;
	int y;
	int z;
};

struct Transmitter
{
	Pos3D pos;
	int range;
};

Transmitter parseLine(string line)
{
	Transmitter t;
	stringstream sstrm(line.substr(5));
	string temp;
	char c;
	int x, y, z, r;
	sstrm  >> x >> c >> y >> c >> z >> temp >> c >> c >> r;
	t.pos.x = x;
	t.pos.y = y;
	t.pos.z = z;
	t.range = r;
	return t;
}

int ManhattanDist(Pos3D a, Pos3D b)
{
	return abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z);
}

bool WithinRange(Transmitter from, Pos3D to)
{
	int distance = ManhattanDist(from.pos, to);
	return distance <= from.range;
}

bool WithinRange(Transmitter from, Transmitter to)
{
	int distance = ManhattanDist(from.pos, to.pos);
	return distance <= from.range;
}

void getBest(int xMin, int xMax, int yMin, int yMax, int zMin, int zMax, int scale, std::list<Transmitter> &txers, const Pos3D &home, int &txCount, int &distanceFromHome, Pos3D &bestPos)
{
	for (int x = xMin / scale; x <= xMax / scale; x++)
	{
		for (int y = yMin / scale; y <= yMax / scale; y++)
		{
			for (int z = zMin / scale; z <= zMax / scale; z++)
			{
				int posCount = 0;
				Pos3D testPos = { x * scale, y * scale, z * scale };
				for (auto t : txers)
				{
					if (WithinRange(t, testPos))
						posCount++;
				}
				int testDistance = ManhattanDist(testPos, home);
				if ((posCount > txCount) || (posCount == txCount && testDistance < distanceFromHome))
				{
					bestPos = testPos;
					txCount = posCount;
					distanceFromHome = testDistance;
				}
			}
		}
	}
}

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode23\\input.txt";

	list<Transmitter> txers;

	ifstream fin(filename);
	string line;
	while (getline(fin, line))
	{
		txers.push_back(parseLine(line));
	}

	Transmitter bestTx;
	int longestRange = 0;
	int xMin = INT32_MAX;
	int yMin = INT32_MAX;
	int zMin = INT32_MAX;
	int xMax = INT32_MIN;
	int yMax = INT32_MIN;
	int zMax = INT32_MIN;

	for (auto t : txers)
	{
		if (t.range > longestRange)
		{
			bestTx = t;
			longestRange = t.range;
		}
		xMin = min(xMin, t.pos.x);
		yMin = min(yMin, t.pos.y);
		zMin = min(zMin, t.pos.z);
		xMax = max(xMax, t.pos.x);
		yMax = max(yMax, t.pos.y);
		zMax = max(zMax, t.pos.z);
	}

	int count = 0;
	for (auto t : txers)
	{
		if (WithinRange(bestTx, t))
			count++;
	}

	cout << count << endl;

	Pos3D home;
	home.x = 0;
	home.y = 0;
	home.z = 0;

	Pos3D bestPos;
	int distanceFromHome = INT32_MAX;
	int txCount = 0;
	for (int scale = 100000000; scale >= 1; scale /= 10)
	{
		getBest(xMin - scale/2, xMax + scale/2, yMin - scale/2, yMax + scale/2, zMin - scale/2, zMax + scale/2, scale, txers, home, txCount, distanceFromHome, bestPos);
		xMin = bestPos.x - scale;
		xMax = bestPos.x + scale;
		yMin = bestPos.y - scale;
		yMax = bestPos.y + scale;
		zMin = bestPos.z - scale;
		zMax = bestPos.z + scale;
	}

	cout << distanceFromHome;
}
