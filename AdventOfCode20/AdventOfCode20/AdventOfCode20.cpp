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

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode20\\test5.txt";
	Method1(filename);
}
