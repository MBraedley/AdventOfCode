// AdventOfCode06.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode06\\input.txt";

	int left = INT32_MAX;
	int right = INT32_MIN;
	int top = INT32_MAX;
	int bottom = INT32_MIN;

	vector<pair<int, int>> coords;
	int x, y;
	string comma;

	ifstream fin(filename);

	while (fin >> x >> comma >> y)
	{
		if (x < left)
			left = x;

		if (x > right)
			right = x;

		if (y < top)
			top = y;

		if (y > bottom)
			bottom = y;

		coords.push_back(make_pair(x, y));

	}

	set<int> infiniteIds;
	int width = right - left + 1;
	int height = bottom - top + 1;

	vector<int> col(height, -1);
	vector<vector<int>> grid(width, col);

	// Fill the grid
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int clossestID = -1;
			int shortestDistance = INT32_MAX;

			for (int id = 0; id < coords.size(); id++)
			{
				x = coords[id].first - left;
				y = coords[id].second - top;

				int distance = abs(x - i) + abs(y - j);
				if (distance < shortestDistance)
				{
					shortestDistance = distance;
					clossestID = id;
				}
				else if (distance == shortestDistance)
					clossestID = -1;
			}

			if (i == 0 || j == 0 || i == width - 1 || j == height - 1)
				infiniteIds.insert(clossestID);

			grid[i][j] = clossestID;
		}
	}

	vector<int> sizes(coords.size(), 0);
	int biggestArea = 0;
	int biggestAreaID = -1;
	// Check the grid
	for (int id = 0; id < coords.size(); id++)
	{
		if (infiniteIds.find(id) == infiniteIds.end())
		{
			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					if (grid[i][j] == id)
						sizes[id]++;
				}
			}
		}

		if (sizes[id] > biggestArea)
		{
			biggestArea = sizes[id];
			biggestAreaID = id;
		}
	}

	cout << biggestAreaID << ": " << biggestArea << endl;
}

