// AdventOfCode10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

#include "FloatingLight.h"

using namespace std;

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode10\\input.txt";
	ifstream fin(filename);

	vector<FloatingLight> lights;

	string line;
	while (getline(fin, line))
	{
		int x = atoi(line.substr(10, 6).c_str());
		int y = atoi(line.substr(18, 6).c_str());
		int velX = atoi(line.substr(36, 2).c_str());
		int velY = atoi(line.substr(40, 2).c_str());

		FloatingLight light(x, y, velX, velY);
		light.step(10000);
		lights.push_back(light);
	}

	int seconds = 10000;

	do
	{
		int left = INT32_MAX;
		int right = INT32_MIN;
		int top = INT32_MAX;
		int bottom = INT32_MIN;
		for (auto light : lights)
		{
			if (light.m_x < left)
				left = light.m_x;
			if (light.m_x > right)
				right = light.m_x;

			if (light.m_y < top)
				top = light.m_y;
			if (light.m_y > bottom)
				bottom = light.m_y;
		}

		if (right - left < 100 && bottom - top < 50)
		{
			vector<bool> row(right - left + 1, false);
			vector<vector<bool>> grid(bottom - top + 1, row);

			for (auto light : lights)
			{
				grid[light.m_y - top][light.m_x - left] = true;
			}

			for (auto row : grid)
			{
				for (bool col : row)
				{
					if (col)
						cout << "*";
					else
						cout << " ";
				}
				cout << endl;
			}
			cout << seconds << "---------------------------------------------------------------------------------------------------------" << endl << endl;
			char c;
			cin >> c;
		}
		else
			cout << "Auto stepping (" << right - left << "x" << bottom - top << ")" << endl;

		for (auto& light : lights)
		{
			light.step();
		}
		seconds++;

	} while (true);
}
