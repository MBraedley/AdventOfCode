// AdventOFCode14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <deque>
#include "AdventOFCode14.h"

using namespace std;

void printRecipies(std::deque<char> &recipies, int elf1, int elf2)
{

	for (int i = 0; i < recipies.size(); i++)
	{
		if (i == elf1)
			cout << "(";
		if (i == elf2)
			cout << "[";
		else if (i != elf1)
			cout << " ";
		cout << (int)(recipies[i]);
		if (i == elf2)
			cout << "]";
		if (i == elf1)
			cout << ")";
		else if (i != elf2)
			cout << " ";
	}
	cout << endl;
}

bool checkTarget(deque<char> &recipies, deque<char> &target)
{
	if (recipies.size() < target.size())
		return false;

	for (deque<char>::reverse_iterator tIt = target.rbegin(), rIt = recipies.rbegin(); tIt != target.rend(); tIt++, rIt++)
	{
		if (*tIt != *rIt)
			return false;
	}
	return true;
}

int main()
{
	deque<char> recipes;
	unsigned long long elf1 = 0;
	unsigned long long elf2 = 1;

	recipes.push_back(3);
	recipes.push_back(7);

	int targetVal = 409551;

	deque<char> target;
	do
	{
		target.push_front(targetVal % 10);
	} while (targetVal /= 10);

	bool targetMet = false;

//	printRecipies(recipies, elf1, elf2);

	while (!targetMet)
	{
		unsigned long long elf1Recipe = recipes[elf1];
		unsigned long long elf2Recipe = recipes[elf2];
		int combined = elf1Recipe + elf2Recipe;

		if (combined < 10)
			recipes.push_back(combined);
		else
		{
			recipes.push_back(combined / 10);
			if (checkTarget(recipes, target))
				break;
			recipes.push_back(combined % 10);
		}

		size_t rSize = recipes.size();
//		cout << "Elf 1 is at " << elf1 << " working on " << elf1Recipe << ". Elf 2 is at " << elf2 << " and is working on " << elf2Recipe << ". They combine to make " << combined << ". There are now " << rSize << " recipes." << endl;

		elf1 = (++elf1 + elf1Recipe) % rSize;
		elf2 = (++elf2 + elf2Recipe) % rSize;

		targetMet = checkTarget(recipes, target);
//		printRecipies(recipies, elf1, elf2);
	}

	cout << recipes.size() - target.size() << endl;
}
