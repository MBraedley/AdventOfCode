// AdventOfCode11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Eigen/Core>

int main()
{
	int serialNum = 9435;

	Eigen::MatrixXi grid(300, 300);

	for (int col = 0; col < grid.cols(); col++)
	{
		for (int row = 0; row < grid.rows(); row++)
		{
			int rackID = col + 10;
			int powerLvl = rackID * row;
			powerLvl += serialNum;
			powerLvl *= rackID;
			powerLvl = (powerLvl / 100) % 10 - 5;
			grid(row, col) = powerLvl;
		}
	}

	int maxPower = 0;
	int powerRow;
	int powerCol;
	int powerSize;
	for (int size = 0; size < 300; size++)
	{
		for (int col = 0; col < grid.cols() - size + 1; col++)
		{
			for (int row = 0; row < grid.rows() - size + 1; row++)
			{
				int localPower = grid.block(row, col, size, size).sum();
				if (localPower > maxPower)
				{
					maxPower = localPower;
					powerRow = row;
					powerCol = col;
					powerSize = size;
				}
			}
		}
	}
	std::cout << powerCol << "," << powerRow << "," << powerSize << std::endl;
}
