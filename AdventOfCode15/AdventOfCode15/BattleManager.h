#pragma once
#include <string>
#include <vector>
#include <set>
#include <map>
#include <deque>

#include "Fighter.h"

class BattleManager
{
public:
	BattleManager(std::string filename, int elfPower = 3);
	~BattleManager();

	bool RunCombat();

	int GetHPTotal();

	void PrintBoard();
	void PrintTurnOrder();

	bool DeadElf() { return m_elfHasDied; }

private:
	static const int WALL = 127;
	static const int FLOOR = 126;
	static const int TARGET = 125;
	void LoadCave(std::string trackFile);
	void FindFighters();

	std::deque<Location> FindShortestPath(std::shared_ptr<Fighter> attacker);
	std::deque<Location> FindShortestPath(std::vector<std::string>& filledCave, Location targetLoc);
	void FindShortestPath(std::deque<Location>& path, std::vector<std::string>& filledCave, Location loc);
	void Move(std::shared_ptr<Fighter> attacker, Location loc);
	void FindTarget(std::shared_ptr<Fighter> attacker);

	void SortFighters();
	void SortFighters(std::vector<std::shared_ptr<Fighter>>& list);

	std::vector<std::shared_ptr<Fighter>> m_fighters;

	std::vector<std::string> m_cave;

	int m_elfPower;
	int m_numStartingElves;
	bool m_elfHasDied;
};

