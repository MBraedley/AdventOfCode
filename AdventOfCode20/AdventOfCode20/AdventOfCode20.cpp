// AdventOfCode20.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <sstream>
#include <stack>
#include <cassert>
#include <map>
#include <unordered_map>
#include <complex>

using namespace std;

struct Node
{
	string value;
	vector<vector<shared_ptr<Node>>> children;
};

int GetLength(shared_ptr<Node> node);
void Method1(std::string &filename);
int GetOptionLength(vector<shared_ptr<Node>>& nodes)
{
	int maxLength = 0;
	for (auto node : nodes)
	{
		int length = GetLength(node);
		if (length == 0)
			return 0;

		if (length > maxLength)
			maxLength = length;
	}
	return maxLength;
}

int GetLength(shared_ptr<Node> node)
{
	int length = node->value.size();
	for (auto& options : node->children)
	{
		length += GetOptionLength(options);
	}
	return length;
}

void PrintOut(ofstream& fout, shared_ptr<Node> node)
{
	fout << node->value;
	for (auto set : node->children)
	{
		fout << "(";
		for (auto child : set)
		{
			PrintOut(fout, child);
			if (child != set.back())
				fout << "|";
		}
		fout << ")";
	}
}

void Method1(std::string &filename)
{
	ifstream fin(filename);

	shared_ptr<Node> head = make_shared<Node>();

	stack<shared_ptr<Node>> nStack;
	nStack.push(head);

	char c;
	while (fin >> c)
	{
		if (c == '^')
			continue;
		if (c == '$')
			break;

		if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		{
			nStack.top()->value.push_back(c);
		}
		else if (c == '(')
		{
			shared_ptr<Node> n = make_shared<Node>();
			vector<shared_ptr<Node>> v;
			v.push_back(n);
			nStack.top()->children.push_back(v);
			nStack.push(n);
		}
		else if (c == ')')
		{
			nStack.pop();
			assert(nStack.size() > 0);
		}
		else if (c == '|')
		{
			nStack.pop();
			assert(nStack.size() > 0);
			shared_ptr<Node> n = make_shared<Node>();
			nStack.top()->children.back().push_back(n);
			nStack.push(n);
		}
	}

	cout << nStack.size() << endl;

	ofstream fout("output.txt");
	fout << "^";
	PrintOut(fout, head);
	fout << "$";

	cout << GetLength(head) << endl;
}

map<char, complex<int>> dir;

bool traverse(ifstream& fin, unordered_map<string, int>& theMap, complex<int>& pos, int& depth)
{
	complex<int> initialPos = pos;
	int initialDepth = depth;
	char c;
	while (fin >> c)
	{
		auto it = dir.find(c);
		if (it != dir.end())
		{
			pos += it->second;
			stringstream sstrm;
			sstrm << pos;
			auto mapIt = theMap.find(sstrm.str());
			if (mapIt == theMap.end())
			{
				depth++;
				theMap.insert(make_pair(sstrm.str(), depth));
			}
			else
				depth = mapIt->second;
		}
		else if (c == '|')
		{
			pos = initialPos;
			depth = initialDepth;
		}
		else if (c == '(')
		{
			if (traverse(fin, theMap, pos, depth))
				cout << "Reached the end prematurely." << endl;
		}
		else if (c == ')')
		{
			return false;
		}
		else if (c == '$')
		{
			cout << "Reached the end" << endl;
			return true;
		}
		else
		{
			cout << "Something went wrong: " << c << endl;
		}
	}
}

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode20\\input.txt";
//	Method1(filename);

	ifstream fin(filename);

	dir.insert(make_pair('N', 1i));
	dir.insert(make_pair('S', -1i));
	dir.insert(make_pair('E', 1));
	dir.insert(make_pair('W', -1));

	unordered_map<string, int> theMap;
	complex<int> pos(0, 0);
	int depth = 0;

	if (!traverse(fin, theMap, pos, depth))
		cout << "Bad traversal" << endl;

	int maxDepth = depth;
	for (auto it : theMap)
	{
		if (it.second > maxDepth)
			maxDepth = it.second;
	}

	cout << depth << " " << maxDepth << endl;
}
