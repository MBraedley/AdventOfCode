// AdventOfCode19.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode19\\input.txt";

	ifstream fin(filename);
	string line;

	getline(fin, line);

	int ip = atoi(line.substr(3).c_str());

	Interpreter interp(ip);

	vector<int> regs = { 17427456, 10551315, 9, 10551315, 0, 10551314 };
	interp.SetRegisters(regs);
	//interp.RunOperation(Interpreter::seti, 1, 0, 0);
	vector<string> program;
	while (getline(fin, line))
	{
		program.push_back(line);
	}

	interp.RunProgram(program);

	vector<int> registers = interp.GetRegisters();

	for (int value : registers)
		cout << value << " ";

	cout << endl;
}
