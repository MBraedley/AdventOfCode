// AdventOfCode21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Interpreter.h"

using namespace std;

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode21\\input.txt";

	ifstream fin(filename);
	string line;

	getline(fin, line);

	int ip = atoi(line.substr(3).c_str());


	vector<string> program;
	while (getline(fin, line))
	{
		program.push_back(line);
	}

	int fewest = INT32_MAX;
	int mostest = 0;

	Interpreter interp(ip, false);
	vector<int> reg = { 0, 0, 0, 0, 0, 0 };
	reg[0] = 0;
	interp.SetRegisters(reg);
//	interp.SetMaxRepeat(fewest * 2);

	interp.RunProgram(program);
	cout << interp.NormalExit();
/*	int count = interp.GetInstructionCount();
	if (count < fewest && interp.NormalExit())
	{
		fewest = count;
		cout << i << ": " << count << endl;
	}
	if (count > mostest && interp.NormalExit())
	{
		mostest = count;
		cout << i << ": " << count << endl;
	}*/
}
