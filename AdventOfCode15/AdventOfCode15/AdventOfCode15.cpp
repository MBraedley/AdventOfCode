// AdventOfCode15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <set>
#include <vector>

#include "BattleManager.h"

int main(int argc, char *argv[])
{
	if (argc <= 1)
		return -1;

	std::string filename(argv[1]);

	// Part 1
	BattleManager bm(filename);
	bm.PrintBoard();
	int rounds = 0;
	while (!bm.RunCombat())
	{
//		bm.PrintBoard();
//		bm.PrintTurnOrder();
		rounds++;
//		std::cout << rounds << std::endl << std::endl;
	}

	bm.PrintBoard();

	std::cout << "Combat took " << rounds << " full rounds." << std::endl;
	std::cout << rounds * bm.GetHPTotal() << std::endl;

	// Part 2
	bool elfDied = true;
	int elfPower = 4;
	while (elfDied)
	{
		BattleManager bm2(filename, elfPower);
		rounds = 0;
		while (!bm2.RunCombat())
		{
			rounds++;
		}
		bm2.PrintBoard();
		std::cout << "Combat took " << rounds << " full rounds." << std::endl;
		std::cout << rounds * bm2.GetHPTotal() << std::endl;
		elfDied = bm2.DeadElf();
		elfPower++;
	}
}
