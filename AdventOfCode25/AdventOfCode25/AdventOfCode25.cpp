// AdventOfCode25.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
#include <memory>

#include "Constelation.h"

using namespace std;

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode25\\input.txt";
	ifstream fin(filename);

	list<shared_ptr<Constelation>> cons;

	string line;
	while (getline(fin, line))
	{
		stringstream sstrm(line);
		Pos4D pos;
		char c;
		sstrm >> pos.x >> c >> pos.y >> c >> pos.z >> c >> pos.t;

		deque<shared_ptr<Constelation>> matches;
		for (auto con : cons)
		{
			if (con->WithinRange(pos))
			{
				matches.push_back(con);
			}
		}

		if (matches.size() == 0)
		{
			shared_ptr<Constelation> con = make_shared<Constelation>();
			con->AddToConstelation(pos);
			cons.push_back(con);
		}
		else
		{
			shared_ptr<Constelation> con = matches.front();
			matches.pop_front();
			cons.remove(con);
			con->AddToConstelation(pos);

			while (matches.size() > 0)
			{
				shared_ptr<Constelation> con2 = matches.front();
				matches.pop_front();
				cons.remove(con2);
				*con += *con2;
			}

			cons.push_back(con);
		}
	}

	cout << cons.size() << endl;
}
