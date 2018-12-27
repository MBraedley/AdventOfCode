#pragma once
#include <memory>

struct Location
{
	int x;
	int y;
};

enum Type
{
	ELF,
	GOBLIN
};

class Fighter
{
public:
	Fighter(Location loc, int ap = 3);
	~Fighter();

	Location m_location;
	Type m_side;

	int GetHP() { return m_hp; }
	void TakeHit(int attack) { m_hp -= attack; }
	int GetAttack() { return m_attack; }
	void Attack(std::shared_ptr<Fighter> target) { target->TakeHit(m_attack); }

	bool IsAlive() { return m_hp > 0; }

	friend bool operator< (const Fighter& lhs, const Fighter& rhs)
	{
		if (lhs.m_location.y != rhs.m_location.y)
			return lhs.m_location.y < rhs.m_location.y;
		return lhs.m_location.x < rhs.m_location.x;
	}
	friend bool operator> (const Fighter& lhs, const Fighter& rhs) { return rhs < lhs; }
	friend bool operator<=(const Fighter& lhs, const Fighter& rhs) { return !(lhs > rhs); }
	friend bool operator>=(const Fighter& lhs, const Fighter& rhs) { return !(lhs < rhs); }
	friend bool operator==(const Fighter& lhs, const Fighter& rhs) { return lhs.m_location.x == rhs.m_location.x && lhs.m_location.y == rhs.m_location.y; }
	friend bool operator!=(const Fighter& lhs, const Fighter& rhs) { return !(lhs == rhs); }

private:
	int m_hp;
	int m_attack;
};

