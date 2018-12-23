// AdventOfCode05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

constexpr int upperLowerDiff = 'a' - 'A';

bool findAndRemove(string& poly, int recursionCount = 0)
{
	if (recursionCount > 50  || poly.empty())
		return true;

	for (int i = 0; i < poly.size() - 1; i ++)
	{
		if (abs(poly[i] - poly[i+1]) == upperLowerDiff)
		{
			string poly2 = poly.substr(i + 2);
			string poly1 = poly.substr(0, i);
			findAndRemove(poly2, recursionCount + 1);
			
			poly = poly1 + poly2;
			return true;
		}
	}
	return false;
}

string removeProblems(const string& poly, char c)
{
	string newPoly;
	for (char s : poly)
	{
		if (s != c && s != c + upperLowerDiff)
			newPoly.push_back(s);
	}
	return newPoly;
}

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode05\\input.txt";

	ifstream fin(filename);
	string line;
	getline(fin, line);

	while (findAndRemove(line));

	int bestPoly = line.size();
	for (char c = 'A'; c <= 'Z'; c++)
	{
		string newLine = removeProblems(line, c);
		while (findAndRemove(newLine));

		if (newLine.size() < bestPoly)
			bestPoly = newLine.size();
	}
	
	cout << bestPoly << endl;
}
