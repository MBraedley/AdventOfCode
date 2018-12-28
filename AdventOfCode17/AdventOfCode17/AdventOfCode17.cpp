// AdventOfCode17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

void PrintArea(vector<string>& area)
{
	for (auto row : area)
	{
		cout << row << endl;
//		if (row.find_first_of('|') == string::npos && row.find_first_of('~') == string::npos)
//			break;
	}

	cout << endl << endl;
}

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode17\\input.txt";

	ifstream fin(filename);

	string line;
	vector<string> inputs;
	while (getline(fin, line))
		inputs.push_back(line);

	int minX = INT32_MAX;
	int minY = INT32_MAX;
	int maxX = 0;
	int maxY = 0;

	// First, determine the extents
	for (string row : inputs)
	{
		if (row.find_first_of('x') == 0)
		{
			int x = atoi(row.substr(2, row.find_first_of(',') - 2).c_str());
			string yStr = row.substr(row.find_first_of('y'));
			int yMin = atoi(yStr.substr(2, yStr.find_first_of('.') - 2).c_str());
			int yMax = atoi(yStr.substr(yStr.find_last_of('.') + 1).c_str());
			if (x < minX)
				minX = x;
			if (x > maxX)
				maxX = x;
			if (yMin < minY)
				minY = yMin;
			if (yMax > maxY)
				maxY = yMax;
		}
		else
		{
			int y = atoi(row.substr(2, row.find_first_of(',') - 2).c_str());
			string xStr = row.substr(row.find_first_of('x'));
			int xMin = atoi(xStr.substr(2, xStr.find_first_of('.') - 2).c_str());
			int xMax = atoi(xStr.substr(xStr.find_last_of('.') + 1).c_str());
			if (y < minY)
				minY = y;
			if (y > maxY)
				maxY = y;
			if (xMin < minX)
				minX = xMin;
			if (xMax > maxX)
				maxX = xMax;
		}
	}

	// Extend the x range by 1 in each direction to allow for spillage
	minX--;
	maxX++;

	string layer(maxX - minX + 1, '.');
	vector<string> area(maxY - minY + 1, layer);
	vector<string> last = area;

	for (string row : inputs)
	{
		if (row.find_first_of('x') == 0)
		{
			int x = atoi(row.substr(2, row.find_first_of(',') - 2).c_str());
			string yStr = row.substr(row.find_first_of('y'));
			int yMin = atoi(yStr.substr(2, yStr.find_first_of('.') - 2).c_str());
			int yMax = atoi(yStr.substr(yStr.find_last_of('.') + 1).c_str());
			for (int y = yMin; y <= yMax; y++)
			{
				area[y - minY][x - minX] = '#';
			}
		}
		else
		{
			int y = atoi(row.substr(2, row.find_first_of(',') - 2).c_str());
			string xStr = row.substr(row.find_first_of('x'));
			int xMin = atoi(xStr.substr(2, xStr.find_first_of('.') - 2).c_str());
			int xMax = atoi(xStr.substr(xStr.find_last_of('.') + 1).c_str());
			for (int x = xMin; x <= xMax; x++)
			{
				area[y - minY][x - minX] = '#';
			}
		}
	}

	area[0][500 - minX] = '|';

	while (area != last)
	{
		last = area;
		for (int row = 1; row < area.size(); row++)
		{
			if (area[row - 1].find_first_of('|') == string::npos && area[row - 1].find_first_of('~') == string::npos)
				break;
			for (int col = 0; col < area[row].size(); col++)
			{																// catch edge case where the clay only leaves 1m of space
				if (area[row][col] == '.' && (area[row - 1][col] == '|' || area[row - 1][col] == '~'))
					area[row][col] = '|';

				if ((area[row][col] == '#' || area[row][col] == '~') && area[row - 1][col] == '|')
				{
					// Always go 1 if you can
					if (area[row - 1][col - 1] == '.')
					{
						area[row - 1][col - 1] = '|';
						int offset = 2;
						while (col - offset > 0 && (area[row][col - offset] == '#' || area[row][col - offset] == '~') && area[row - 1][col - offset] == '.')
							area[row - 1][col - offset++] = '|';
					}
					if (area[row - 1][col + 1] == '.')
					{
						area[row - 1][col + 1] = '|';
						// not necessary, as the inner loop will take care of this
//						int offset = 2;
//						while (col + offset < area[row].size() && (area[row][col + offset] == '#' || area[row][col + offset] == '~') && area[row - 1][col + offset] == '.')
//							area[row - 1][col + offset++] = '|';
					}

				}
			}
			regex re("#\\|+#");
			cmatch m;
			regex_search(area[row].c_str(), m, re);
			for (auto ma : m)
			{
				string orig(ma);
				string rep = orig;
				rep.replace(1, rep.size() - 2, rep.size() - 2, '~');

				area[row].replace(area[row].find(orig), rep.size(), rep);
			}
		}

//		PrintArea(area);
	}

	PrintArea(area);

	int flowCount = 0;
	int standingCount = 0;

	for (auto row : area)
	{
		for (char c : row)
		{
			if (c == '|')
				flowCount++;
			if (c == '~')
				standingCount++;
		}
	}

	cout << flowCount << " " << standingCount << " " << flowCount + standingCount << endl;
}
