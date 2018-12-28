// AdventOfCode18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

#include "Acre.h"

using namespace std;

void PrintWoodLot(vector<vector<Acre>>& lot)
{
	for (auto row : lot)
	{
		for (auto acre : row)
		{
			switch (acre.GetType())
			{
			case Acre::Trees:
				cout << "|";
				break;
			case Acre::Lumberyard:
				cout << "#";
				break;
			case Acre::Open:
				cout << ".";
			default:
				break;
			}
		}
		cout << endl;
	}
}

string LotToString(vector<vector<Acre>>& lot)
{
	stringstream sstrm;
	for (auto row : lot)
	{
		for (auto acre : row)
		{
			switch (acre.GetType())
			{
			case Acre::Trees:
				sstrm << "|";
				break;
			case Acre::Lumberyard:
				sstrm << "#";
				break;
			case Acre::Open:
				sstrm << ".";
			default:
				break;
			}
		}
		sstrm << endl;
	}
	return sstrm.str();
}

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode18\\input.txt";

	ifstream fin(filename);

	std::vector<string> preMap;
	string line;
	while (getline(fin, line))
	{
		preMap.push_back(line);
	}

	vector<Acre> treeRow(preMap[0].size() + 2);
	vector<vector<Acre>> lot(preMap.size() + 2, treeRow);

	for (int row = 0; row < preMap.size(); row++)
	{
		for (int col = 0; col < preMap[row].size(); col++)
		{
			switch (preMap[row][col])
			{
			case '#':
				lot[row + 1][col + 1].SetNextType(Acre::Lumberyard);
				break;
			case '|':
				lot[row + 1][col + 1].SetNextType(Acre::Trees);
				break;
			case '.':
				lot[row + 1][col + 1].SetNextType(Acre::Open);
			default:
				break;
			}
			lot[row + 1][col + 1].Step();
		}
	}

	unsigned int numRounds = 1000;
	unordered_map<string, unsigned int> scoreRecord;

	for (unsigned int cRound = 0; cRound < numRounds; cRound++)
	{
//		if (cRound % 10000 == 0)
//			cout << cRound << endl;
		for (int row = 1; row < lot.size() - 1; row++)
		{
			for (int col = 1; col < lot[row].size() - 1; col++)
			{
				int treeCount = 0;
				int lumberCount = 0;
				int openCount = 0;

				for (int i = row - 1; i <= row + 1; i++)
				{
					for (int j = col - 1; j <= col + 1; j++)
					{
						Acre::Type type = lot[i][j].GetType();
						if (type == Acre::Trees)
							treeCount++;
						else if (type == Acre::Lumberyard)
							lumberCount++;
						else if (type == Acre::Open)
							openCount++;
					}
				}

				Acre::Type type = lot[row][col].GetType();
				if (type == Acre::Trees)
				{
					if (lumberCount >= 3)
						lot[row][col].SetNextType(Acre::Lumberyard);
				}
				else if (type == Acre::Lumberyard)
				{
					lumberCount--;
					if (lumberCount < 1 || treeCount < 1)
						lot[row][col].SetNextType(Acre::Open);
				}
				else if (type == Acre::Open)
				{
					if (treeCount >= 3)
						lot[row][col].SetNextType(Acre::Trees);
				}
			}
		}

		int treeCount = 0;
		int lumberCount = 0;
		for (int row = 1; row < lot.size() - 1; row++)
		{
			for (int col = 1; col < lot[row].size() - 1; col++)
			{
				lot[row][col].Step();
				Acre::Type type = lot[row][col].GetType();
				if (type == Acre::Trees)
					treeCount++;
				else if (type == Acre::Lumberyard)
					lumberCount++;
			}
		}

		int score = treeCount * lumberCount;
		string lotStr = LotToString(lot);
		auto it = scoreRecord.find(lotStr);
		if (it != scoreRecord.end())
		{
			cout << "Match Found: " << it->second << " " << cRound << " " << score << endl;
			//PrintWoodLot(lot);
			//return 0;
		}
		scoreRecord.insert(make_pair(lotStr, cRound));

//		cout << treeCount << " " << lumberCount << endl;
	}

	unsigned long long treeCount = 0;
	unsigned long long lumberCount = 0;
	for (int row = 1; row < lot.size() - 1; row++)
	{
		for (int col = 1; col < lot[row].size() - 1; col++)
		{
			Acre::Type type = lot[row][col].GetType();
			if (type == Acre::Trees)
				treeCount++;
			else if (type == Acre::Lumberyard)
				lumberCount++;
		}
	}

	cout << treeCount * lumberCount << endl;
}
