// AdventOfCode13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "TrackManager.h"
#include "Minecart.h"

int main()
{
	std::string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode13\\input.txt";
	
	TrackManager tm(filename);

	while (tm.MoveCarts());

	Location loc = tm.GetLast();
	std::cout << loc.x << "," << loc.y << std::endl;
}
