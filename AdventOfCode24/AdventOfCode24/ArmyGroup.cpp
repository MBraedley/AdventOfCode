#include "pch.h"
#include "ArmyGroup.h"
#include <sstream>

using namespace std;

ArmyGroup::ArmyGroup()
{
}

ArmyGroup::ArmyGroup(Side s, int boost) : m_side(s)
{
	m_boost = m_side == Immune ? boost : 0;
}


ArmyGroup::~ArmyGroup()
{
}

void ArmyGroup::ParseLine(std::string line)
{
	stringstream sstrm(line);
	string temp, weak, immune;
	
	sstrm >> m_count >> temp >> temp >> temp >> m_unitHP >> temp >> temp;
	if (line.find_first_of('(') != line.npos)
	{
		char c = '\0';
		while (c != ')')
			sstrm >> c;
	}

	sstrm >> temp >> temp >> temp >> temp >> temp >> m_unitAttack >> m_attackType >> temp >> temp >> temp >> m_initiative;

	size_t weakPos = line.find("weak to");
	if (weakPos != line.npos)
	{
		stringstream weakStrm(line.substr(weakPos));
		weakStrm >> temp >> temp;
		char end;
		do
		{
			weakStrm >> weak;
			end = weak.back();
			weak.erase(weak.size() - 1);
			m_weaknesses.insert(weak);
		} while (end == ',');
	}

	size_t immunePos = line.find("immune to");
	if (immunePos != line.npos)
	{
		stringstream immuneStrm(line.substr(immunePos));
		immuneStrm >> temp >> temp;
		char end;
		do
		{
			immuneStrm >> immune;
			end = immune.back();
			immune.erase(immune.size() - 1);
			m_immunities.insert(immune);
		} while (end == ',');
	}
}

void ArmyGroup::Attack(std::shared_ptr<ArmyGroup> target)
{
	int damageMulti = 1;
	if (target->m_weaknesses.find(this->m_attackType) != target->m_weaknesses.end())
		damageMulti = 2;
	int casualties = this->GetEffectivePower() * damageMulti / target->m_unitHP;

	target->m_count -= casualties;
}

std::list<std::shared_ptr<ArmyGroup>> ArmyGroup::GetAttackOrder(std::set<std::shared_ptr<ArmyGroup>>& immune, std::set<std::shared_ptr<ArmyGroup>> infection)
{
	std::list<std::shared_ptr<ArmyGroup>> order;

	for (auto ag : immune)
	{
		auto it = order.begin();
		while (it != order.end() && ag->GetEffectivePower() < (*it)->GetEffectivePower())
		{
			it++;
		}
		while (it != order.end() && ag->GetEffectivePower() == (*it)->GetEffectivePower() && ag->GetInitiative() < (*it)->GetInitiative())
		{
			it++;
		}
		order.insert(it, ag);
	}

	for (auto ag : infection)
	{
		auto it = order.begin();
		while (it != order.end() && ag->GetEffectivePower() < (*it)->GetEffectivePower())
		{
			it++;
		}
		while (it != order.end() && ag->GetEffectivePower() == (*it)->GetEffectivePower() && ag->GetInitiative() < (*it)->GetInitiative())
		{
			it++;
		}
		order.insert(it, ag);
	}

	return order;
}

std::shared_ptr<ArmyGroup> ArmyGroup::FindTarget(std::set<std::shared_ptr<ArmyGroup>>& enemy)
{
	shared_ptr<ArmyGroup> target = nullptr;

	bool targetWeak = false;
	for (auto ag : enemy)
	{
		if (ag->m_immunities.find(this->m_attackType) != ag->m_immunities.end())
			continue;

		if (ag->m_weaknesses.find(this->m_attackType) != ag->m_weaknesses.end())
		{
			if (target == nullptr || !targetWeak)
				target = ag;
			else if (target->GetEffectivePower() < ag->GetEffectivePower())
				target = ag;
			else if (target->GetEffectivePower() == ag->GetEffectivePower() && target->GetInitiative() < ag->GetInitiative())
				target = ag;
			targetWeak = true;
		}
		else if (!targetWeak)
		{
			if (target == nullptr)
				target = ag;
			else if (target->GetEffectivePower() < ag->GetEffectivePower())
				target = ag;
			else if (target->GetEffectivePower() == ag->GetEffectivePower() && target->GetInitiative() < ag->GetInitiative())
				target = ag;
		}
	}

	if (target != nullptr)
		enemy.erase(target);

	return target;
}
