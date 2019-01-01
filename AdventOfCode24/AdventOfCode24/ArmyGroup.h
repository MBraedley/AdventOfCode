#pragma once
#include <set>
#include <list>
#include <memory>

class ArmyGroup
{
public:
	enum Side
	{
		Immune,
		Infection
	};

	ArmyGroup();
	ArmyGroup(Side s, int boost);
	~ArmyGroup();

	void ParseLine(std::string line);

	int GetEffectivePower() { return (m_unitAttack + m_boost) * m_count; }
	int GetInitiative() { return m_initiative; }

	void Attack(std::shared_ptr<ArmyGroup> target);

	void SetSide(Side s) { m_side = s; }
	bool IsImmune() { return m_side == Immune; }
	bool IsInfection() { return m_side == Infection; }

	bool IsAlive() { return m_count > 0; }

	int GetRemainingUnits() { return m_count; }

	static std::list<std::shared_ptr<ArmyGroup>> GetAttackOrder(std::set<std::shared_ptr<ArmyGroup>>& immune, std::set<std::shared_ptr<ArmyGroup>> infection);
	
	std::shared_ptr<ArmyGroup> FindTarget(std::set<std::shared_ptr<ArmyGroup>>& enemy);

private:
	std::set<std::string> m_immunities;
	std::set<std::string> m_weaknesses;
	std::string m_attackType;

	int m_count;
	int m_initiative;
	int m_unitHP;
	int m_unitAttack;
	int m_boost;

	Side m_side;
};

