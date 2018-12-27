// AdventOfCode16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include "Interpreter.h"

using namespace std;

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode16\\input.txt";

	set<int> opVals;
	for (int i = 0; i <= 15; i++)
		opVals.insert(i);

	map<Interpreter::Opcodes, set<int>> opcodeMaybeMap;

	for (int op = 0; op < Interpreter::Opcodes::LAST; op++)
	{
		opcodeMaybeMap.insert(make_pair((Interpreter::Opcodes)op, opVals));
	}

	ifstream fin(filename);

	Interpreter interp;

	int sampleCount = 0;

	string before, input, after, empty;
	while (getline(fin, before), getline(fin, input), getline(fin, after), getline(fin, empty))
	{
		vector<int> beforeState;
		beforeState.push_back(atoi(before.substr(9, 1).c_str()));
		beforeState.push_back(atoi(before.substr(12, 1).c_str()));
		beforeState.push_back(atoi(before.substr(15, 1).c_str()));
		beforeState.push_back(atoi(before.substr(18, 1).c_str()));

		stringstream instructions(input);
		int opcode, a, b, c;
		instructions >> opcode >> a >> b >> c;

		vector<int> afterState;
		afterState.push_back(atoi(after.substr(9, 1).c_str()));
		afterState.push_back(atoi(after.substr(12, 1).c_str()));
		afterState.push_back(atoi(after.substr(15, 1).c_str()));
		afterState.push_back(atoi(after.substr(18, 1).c_str()));

		int validSeq = 0;
		for (auto& it : opcodeMaybeMap)
		{
			interp.SetRegisters(beforeState);
			interp.RunOperation(it.first, a, b, c);
			if (interp.GetRegisters() == afterState)
				validSeq++;
			else
				it.second.erase(opcode);
		}

		if (validSeq >= 3)
			sampleCount++;
	}

	cout << sampleCount << endl;

	for (auto& it : opcodeMaybeMap)
	{
		cout << (int)it.first << ": (" << it.second.size() << ")\t" << endl;
	}

	bool opcodesSet = false;
	map<int, Interpreter::Opcodes> opcodeReallyMap;

	while (opcodeMaybeMap.size() > 0)
	{
		for (auto& it : opcodeMaybeMap)
		{
			if (it.second.size() == 1)
			{
				int opNum = *it.second.begin();
				opcodeReallyMap.insert(make_pair(opNum, it.first));
				for (auto& it2 : opcodeMaybeMap)
					it2.second.erase(opNum);
				opcodeMaybeMap.erase(it.first);
				break;
			}
		}
	}

	string filename2 = "C:\\Dev\\AdventOfCode\\AdventOfCode16\\input2.txt";
	ifstream fin2(filename2);

	vector<int> reset(4, 0);
	interp.SetRegisters(reset);
	while (getline(fin2, input))
	{
		stringstream  sstrm(input);

		int opcode, a, b, c;
		sstrm >> opcode >> a >> b >> c;
		interp.RunOperation(opcodeReallyMap.find(opcode)->second, a, b, c);
	}

	vector<int> result = interp.GetRegisters();
	for (int val : result)
		cout << val << "\t";

	cout << endl;
}
