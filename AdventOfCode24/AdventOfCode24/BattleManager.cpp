#include "pch.h"
#include "BattleManager.h"
#include <list>
#include <map>

using namespace std;

BattleManager::BattleManager()
{
}


BattleManager::~BattleManager()
{
}

bool BattleManager::RunCombat()
{
	list<shared_ptr<ArmyGroup>> attackOrder = ArmyGroup::GetAttackOrder(m_immuneSystem, m_infection);

	set<shared_ptr<ArmyGroup>> availableImmuneTargets = m_immuneSystem;
	set<shared_ptr<ArmyGroup>> availableInfectionTargets = m_infection;

	map<int, pair<shared_ptr<ArmyGroup>, shared_ptr<ArmyGroup>>> attackPairing;
	
	// Choose targets
	for (auto ag : attackOrder)
	{
		auto target = ag->FindTarget(ag->IsInfection() ? availableImmuneTargets : availableInfectionTargets);
		if (target != nullptr)
		{
			attackPairing.insert(make_pair(ag->GetInitiative(), make_pair(ag, target)));
		}
	}

	// Attack
	for (auto agP = attackPairing.rbegin(); agP != attackPairing.rend(); agP++)
	{
		if (agP->second.first->IsAlive())
		{
			agP->second.first->Attack(agP->second.second);
		}
	}

	// Clear the dead
	for (auto ag : attackOrder)
	{
		if (!ag->IsAlive())
		{
			m_immuneSystem.erase(ag);
			m_infection.erase(ag);
		}
	}

	return m_immuneSystem.size() > 0 && m_infection.size() > 0;
}

void BattleManager::AddArmyGroup(std::shared_ptr<ArmyGroup> ag)
{
	if (ag->IsImmune())
		m_immuneSystem.insert(ag);
	else
		m_infection.insert(ag);
}

int BattleManager::GetRemainingUnits(ArmyGroup::Side s)
{
	int count = 0;
	if (s == ArmyGroup::Immune)
	{
		for (auto ag : m_immuneSystem)
			count += ag->GetRemainingUnits();
	}
	else
	{
		for (auto ag : m_infection)
			count += ag->GetRemainingUnits();
	}
	return count;
}
