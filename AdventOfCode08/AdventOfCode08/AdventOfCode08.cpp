// AdventOfCode08.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

struct MetaTree
{
	vector<shared_ptr<MetaTree>> children;
	vector<int> metadata;
};

shared_ptr<MetaTree> getNode(ifstream& fin, int& sum)
{
	int childrenCount;
	int metaCount;
	if (fin >> childrenCount >> metaCount)
	{
		shared_ptr<MetaTree> mt = make_shared<MetaTree>();
		for (int i = 0; i < childrenCount; i++)
		{
			auto childMT = getNode(fin, sum);
			if (childMT == nullptr)
			{
				cout << "Something went wrong" << endl;
				return nullptr;
			}
			mt->children.push_back(childMT);
		}

		for (int j = 0; j < metaCount; j++)
		{
			int data;
			if (fin >> data)
			{
				sum += data;
				mt->metadata.push_back(data);
			}
			else
			{
				cout << "Couldn't read metadata" << endl;
				return nullptr;
			}
		}
		return mt;
	}
	else
	{
		cout << "Couldn't read counts" << endl;
		return nullptr;
	}
}

int getValue(shared_ptr<MetaTree> node)
{
	int value = 0;
	if (node->children.empty())
	{
		for (int data : node->metadata)
			value += data;
	}
	else
	{
		for (int data : node->metadata)
		{
			if (data <= node->children.size())
				value += getValue(node->children[data - 1]);
		}
	}
	return value;
}

int main()
{
	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode08\\input.txt";

	ifstream fin(filename);

	int sum = 0;
	auto root = getNode(fin, sum);

	if (root == nullptr)
		return -1;

	cout << getValue(root) << endl;
}
