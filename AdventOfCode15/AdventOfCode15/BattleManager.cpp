#include "pch.h"
#include "BattleManager.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>

BattleManager::BattleManager(std::string filename, int elfPower/* = 3*/): m_elfPower(elfPower), m_elfHasDied(false)
{
	LoadCave(filename);
	FindFighters();
}


BattleManager::~BattleManager()
{
}

bool BattleManager::RunCombat()
{
	for (auto& it : m_fighters)
	{
		if (it->IsAlive())
		{
			std::deque<Location> path = FindShortestPath(it);
			if (path.size() > 1)
				it->m_location = path.front();
			FindTarget(it);
		}
	}
	int elfCount = 0;
	int goblinCount = 0;
	std::vector<std::shared_ptr<Fighter>> f;
	for (auto& it : m_fighters)
	{
		if (it->IsAlive())
		{
			f.push_back(it);
			if (it->m_side == ELF)
				elfCount++;
			else
				goblinCount++;
		}
	}
	if (elfCount != m_numStartingElves)
		m_elfHasDied = true;

	m_fighters.clear();
	m_fighters.assign(f.begin(), f.end());
	SortFighters();
	return elfCount == 0 || goblinCount == 0;
}

int BattleManager::GetHPTotal()
{
	int total = 0;
	for (auto f : m_fighters)
	{
		// Double check they're alive
		if (f->IsAlive())
			total += f->GetHP();
	}
	return total;
}

void BattleManager::PrintBoard()
{
	std::vector<std::string> caveCopy(m_cave);
	for (auto f : m_fighters)
	{
		char marker;
		if (f->m_side == ELF)
			marker = 'E';
		else
			marker = 'G';
		caveCopy[f->m_location.y][f->m_location.x] = marker;
	}

	int i = 0;
	for (int row = 0; row < caveCopy.size(); row++)
	{
		std::cout << caveCopy[row];
		while (i < m_fighters.size() && m_fighters[i]->m_location.y == row)
		{
			std::cout << "\t" << (m_fighters[i]->m_side == ELF ? "E" : "G") << "(" << m_fighters[i]->GetHP() << ")";
			i++;
		}
		std::cout << std::endl;
	}
}

void BattleManager::PrintTurnOrder()
{
	std::cout << "Start ";
	for (auto f : m_fighters)
	{
		std::cout << "-> " << (f->m_side == ELF ? "E" : "G") << "(" << f->m_location.x << "," << f->m_location.y << ")";
	}
	std::cout << std::endl;
}

void BattleManager::LoadCave(std::string trackFile)
{
	std::ifstream fin(trackFile);

	std::string line;
	while (getline(fin, line))
	{
		int col;
		while ((col = line.find_first_of('.')) != std::string::npos)
			line[col] = FLOOR;
		while ((col = line.find_first_of('#')) != std::string::npos)
			line[col] = WALL;
		m_cave.push_back(line);
	}
}

void BattleManager::FindFighters()
{
	m_numStartingElves = 0;
	for (int row = 0; row < m_cave.size(); row++)
	{
		int col;
		while ((col = m_cave[row].find_first_of('E')) != std::string::npos)
		{
			Location loc;
			loc.x = col;
			loc.y = row;
			std::shared_ptr<Fighter> elf = std::make_shared<Fighter>(loc, m_elfPower);
			elf->m_side = ELF;
			m_fighters.push_back(elf);
			m_cave[row][col] = FLOOR;
			m_numStartingElves++;
		}
		while ((col = m_cave[row].find_first_of('G')) != std::string::npos)
		{
			Location loc;
			loc.x = col;
			loc.y = row;
			std::shared_ptr<Fighter> goblin = std::make_shared<Fighter>(loc);;
			goblin->m_side = GOBLIN;
			m_fighters.push_back(goblin);
			m_cave[row][col] = FLOOR;
		}
	}
	SortFighters();
}

std::deque<Location> BattleManager::FindShortestPath(std::shared_ptr<Fighter> attacker)
{
	std::vector<std::string> caveCopy(m_cave);
	for (auto f : m_fighters)
	{
		if (f->IsAlive())
		{
			char marker;
			if (f->m_side == attacker->m_side)
				marker = WALL;	// Fighters on the same side are obstacles.
			else
				marker = TARGET;
			caveCopy[f->m_location.y][f->m_location.x] = marker;
		}
	}

	char fillVal = 1;
	caveCopy[attacker->m_location.y][attacker->m_location.x] = fillVal;

	Location targetLoc;
	targetLoc.x = -1;
	targetLoc.y = -1;
	bool doneFill = false;
	while (!doneFill)
	{
		doneFill = true;
		for (int row = 0; row < caveCopy.size(); row++)
		{
			int col = -1;
			while ((col = caveCopy[row].find_first_of(TARGET, col + 1)) != std::string::npos)
			{
				if (caveCopy[row - 1][col] == fillVal || caveCopy[row + 1][col] == fillVal || caveCopy[row][col - 1] == fillVal || caveCopy[row][col + 1] == fillVal)
				{
					targetLoc.x = col;
					targetLoc.y = row;
					return FindShortestPath(caveCopy, targetLoc);
				}
			}
			col = -1;
			while ((col = caveCopy[row].find_first_of(fillVal, col + 1)) != std::string::npos)
			{
				if (caveCopy[row - 1][col] == FLOOR)
				{
					caveCopy[row - 1][col] = fillVal + 1;
					doneFill = false;
				}
				if (caveCopy[row + 1][col] == FLOOR)
				{
					caveCopy[row + 1][col] = fillVal + 1;
					doneFill = false;
				}
				if (caveCopy[row][col - 1] == FLOOR)
				{
					caveCopy[row][col - 1] = fillVal + 1;
					doneFill = false;
				}
				if (caveCopy[row][col + 1] == FLOOR)
				{
					caveCopy[row][col + 1] = fillVal + 1;
					doneFill = false;
				}
			}
		}
		fillVal++;
	}
	std::deque<Location> empty;
	return empty;
}

std::deque<Location> BattleManager::FindShortestPath(std::vector<std::string>& filledCave, Location targetLoc)
{
	std::deque<Location> path;
	FindShortestPath(path, filledCave, targetLoc);
	return path;
}

void BattleManager::FindShortestPath(std::deque<Location>& path, std::vector<std::string>& filledCave, Location loc)
{
	path.push_front(loc);
	int up = filledCave[loc.y - 1][loc.x];
	int down = filledCave[loc.y + 1][loc.x];
	int left = filledCave[loc.y][loc.x - 1];
	int right = filledCave[loc.y][loc.x + 1];

	int value;
	Location newLoc = loc;
	if (down < up && down < left && down < right)
	{
		value = down;
		newLoc.y++;
	}
	else if (right < left && right < up)
	{
		value = right;
		newLoc.x++;
	}
	else if (left < up)
	{
		value = left;
		newLoc.x--;
	}
	else
	{
		value = up;
		newLoc.y--;
	}
	if (value > 1)
		FindShortestPath(path, filledCave, newLoc);
}

void BattleManager::Move(std::shared_ptr<Fighter> attacker, Location loc)
{
	attacker->m_location = loc;
}

void BattleManager::FindTarget(std::shared_ptr<Fighter> attacker)
{
	Location attackerLoc = attacker->m_location;

	Fighter up(attackerLoc);
	up.m_location.y--;

	Fighter left(attackerLoc);
	left.m_location.x--;

	Fighter right(attackerLoc);
	right.m_location.x++;

	Fighter down(attackerLoc);
	down.m_location.y++;

	std::vector<std::shared_ptr<Fighter>> sortedFighters;
	sortedFighters.assign(m_fighters.begin(), m_fighters.end());
	SortFighters(sortedFighters);

	int hp = INT32_MAX;
	std::shared_ptr<Fighter> target;
	for (std::shared_ptr<Fighter> f : sortedFighters)
	{
		if ((*f == up || *f == left || *f == right || *f == down) && f->m_side != attacker->m_side && f->IsAlive() && f->GetHP() < hp)
		{
			target = f;
			hp = f->GetHP();
		}
	}

	if (target)
		attacker->Attack(target);
}

void BattleManager::SortFighters()
{
	SortFighters(m_fighters);
}

void BattleManager::SortFighters(std::vector<std::shared_ptr<Fighter>>& list)
{
	for (int i = 0; i < list.size() - 1; i++)
	{
		for (int j = 0; j < list.size() - 1; j++)
		{
			if (*list[j + 1] < *list[j])
				std::swap(list[j + 1], list[j]);
		}
	}
}
