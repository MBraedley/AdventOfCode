#pragma once
#include <memory>
#include <set>
#include <deque>

#include "ArmyGroup.h"

class BattleManager
{
public:
	BattleManager();
	~BattleManager();

	bool RunCombat();

	void AddArmyGroup(std::shared_ptr<ArmyGroup> ag);

	int GetRemainingUnits(ArmyGroup::Side s);

private:
	std::set<std::shared_ptr<ArmyGroup>> m_immuneSystem;
	std::set<std::shared_ptr<ArmyGroup>> m_infection;
};

