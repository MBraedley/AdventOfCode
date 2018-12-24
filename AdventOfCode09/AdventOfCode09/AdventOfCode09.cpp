// AdventOfCode09.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <memory>
#include <vector>
#include <set>

using namespace std;

struct Marble
{
	shared_ptr<Marble> ccw;
	long long value;
	shared_ptr<Marble> cw;
};

long long placeMarble(long long value, shared_ptr<Marble>& currentMarble)
{
	if (value % 23 == 0)
	{
		long long score = value;
		shared_ptr<Marble> remove = currentMarble->ccw->ccw->ccw->ccw->ccw->ccw->ccw;
		currentMarble = remove->cw;
		remove->ccw->cw = remove->cw;
		remove->cw->ccw = remove->ccw;
		remove->ccw = nullptr;
		remove->cw = nullptr;
		score += remove->value;
		return score;
	}
	else
	{
		shared_ptr<Marble> pmCcw = currentMarble->cw;
		shared_ptr<Marble> pmCw = pmCcw->cw;
		currentMarble = make_shared<Marble>();
		currentMarble->value = value;
		currentMarble->ccw = pmCcw;
		currentMarble->cw = pmCw;
		pmCcw->cw = currentMarble;
		pmCw->ccw = currentMarble;
		return 0;
	}
}

void printCircle(shared_ptr<Marble> currentMarble)
{
	auto marble = currentMarble;
	do
	{
		cout << marble->value << " ";
		marble = marble->cw;
	} while (marble != currentMarble);
	cout << endl;
}

int main()
{
	//input: 424 players; last marble is worth 71482 points
	int numPlayers = 424;
	long long lastMarbleValue = 7148200;

	shared_ptr<Marble> currentMarble = make_shared<Marble>();
	currentMarble->ccw = currentMarble;
	currentMarble->value = 0;
	currentMarble->cw = currentMarble;

	vector<long long> scores(numPlayers, 0);

//	printCircle(currentMarble);
	for (long long marbleValue = 1; marbleValue <= lastMarbleValue; marbleValue++)
	{
		int currentPlayer = (marbleValue - 1) % numPlayers;
		scores[currentPlayer] += placeMarble(marbleValue, currentMarble);
//		printCircle(currentMarble);
	}

	long long bestScore = 0;
	for (long long score : scores)
	{
		if (score > bestScore)
			bestScore = score;
	}

	cout << bestScore << endl;
}
