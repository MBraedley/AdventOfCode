// AdventOfCode24.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

#include "ArmyGroup.h"
#include "BattleManager.h"

using namespace std;

int main()
{
	int boost = 1000;
	int isRemaining;

	do
	{
		string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode24\\input.txt";
		ifstream fin(filename);

		ArmyGroup::Side s = ArmyGroup::Immune;
		BattleManager bm;

		string line;
		getline(fin, line);
		while (getline(fin, line))
		{
			if (line.empty())
			{
				getline(fin, line);
				s = ArmyGroup::Infection;
				continue;
			}
			shared_ptr<ArmyGroup> ag = make_shared<ArmyGroup>(s, boost);
			ag->ParseLine(line);
			bm.AddArmyGroup(ag);
		}

		while (bm.RunCombat())
		{
//			cout << "Immune: " << bm.GetRemainingUnits(ArmyGroup::Immune) << "  Infection: " << bm.GetRemainingUnits(ArmyGroup::Infection) << endl;
		}

		isRemaining = bm.GetRemainingUnits(ArmyGroup::Immune);
		cout << "Immune: " << isRemaining << "  Infection: " << bm.GetRemainingUnits(ArmyGroup::Infection) << "  Boost: " << boost << endl;

		boost--;
	} while (isRemaining > 0);

}
