// AdventOfCode07.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Job
{
	Job(char id) : jobID(id), earliestTimeslot(0) {};
	set<char> parentIds;
	char jobID;
	set<char> childrenIds;
	int earliestTimeslot;
};

int main()
{
	map<char, shared_ptr<Job>> allJobs;
	set<char> jobsWithoutParents;

	// Some setup
	for (char jobID = 'A'; jobID <= 'Z'; jobID++)
	{
		jobsWithoutParents.insert(jobID);
		shared_ptr<Job> theJob = make_shared<Job>(jobID);
		allJobs.insert(make_pair(jobID, theJob));
	}

	string filename = "C:\\Dev\\AdventOfCode\\AdventOfCode07\\input.txt";

	ifstream fin(filename);
	string line;
	while (getline(fin, line))
	{
		char parentId = line[5];
		char childId = line[36];

		auto parent = allJobs.find(parentId);
		auto child = allJobs.find(childId);

		if (parent == allJobs.end() || child == allJobs.end())
		{
			cout << "Something went wrong" << endl;
			return -1;
		}

		parent->second->childrenIds.insert(childId);
		child->second->parentIds.insert(parentId);

		jobsWithoutParents.erase(childId);
	}

	if (jobsWithoutParents.empty())
	{
		cout << "Something went wrong" << endl;
		return -2;
	}

	string jobOrder;

	vector<int> availableTimes(5, 0);

	while (!jobsWithoutParents.empty())
	{
		int nextWorkerTime = INT32_MAX;
		int workerID;

		for (int i = 0; i < availableTimes.size(); i++)
		{
			if (availableTimes[i] < nextWorkerTime)
			{
				workerID = i;
				nextWorkerTime = availableTimes[i];
			}
		}

		auto nextJob = jobsWithoutParents.begin();
		while (nextJob != jobsWithoutParents.end() && !(allJobs.find(*nextJob)->second->parentIds.empty()))
		{
			nextJob++;
		}

		if (nextJob == jobsWithoutParents.end())
		{
			cout << "Something went wrong" << endl;
			return -3;
		}

		jobOrder.push_back(*nextJob);

		auto jobIt = allJobs.find(*nextJob);

		int endtime = 61 + *nextJob - 'A' + jobIt->second->earliestTimeslot;
		availableTimes[workerID] = endtime;

		for (char c : jobIt->second->childrenIds)
		{
			auto it = allJobs.find(c);
			it->second->parentIds.erase(*nextJob);
			if (it->second->earliestTimeslot < endtime)
				it->second->earliestTimeslot = endtime;
			jobsWithoutParents.insert(c);
		}

		jobsWithoutParents.erase(*nextJob);
	}

	cout << jobOrder << endl;

	for (auto i : availableTimes)
		cout << i << "\t";

	cout << endl;
}
